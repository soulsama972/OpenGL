#include "mouse.h"
#include"GLFW/glfw3.h"
#include<vector>
#include<chrono>

struct CallBack
{
	MouseEventCallBack mCallBack;
	void* pthis;
};


uchar flags = 0;
float currentZoom = 0.0f;
glm::vec2 positon = { 0,0 };
std::vector< CallBack> info;


float Mouse::GetWheelDiffrent()
{
	return currentZoom;
}

glm::vec2 Mouse::GetMousePos()
{
	return positon;
}

bool Mouse::IsRightClicked(bool doubleClick)
{
	return WrapIsClicked(flags  & 3, doubleClick);
}

bool Mouse::IsLeftClicked(bool doubleClick)
{
	return WrapIsClicked(((flags >> 2) & 3), doubleClick);
}

bool Mouse::IsMiddleCLicked(bool doubleClick)
{
	return WrapIsClicked(((flags >> 4) & 3), doubleClick);
}

bool Mouse::IsMouseOutSideOfWindow()
{
	return flags >> 6;
}

bool Mouse::WrapIsClicked(uchar value, bool doubleClick) 
{
	return doubleClick ? value == MouseState::DoubleClicked ? true : false : value == MouseState::Clicked;
}

void Mouse::InsertCallBack(void* pThis)
{
	info.push_back({ 0, pThis });
}

void Mouse::InsertCallBack(MouseEventCallBack mCallBack)
{
	info.push_back({ mCallBack, 0 });
}

void Mouse::RemoveCallBack(MouseEventCallBack mCallBack)
{
	for (auto begin = info.begin(); begin != info.end(); begin++)
	{
		if (begin->mCallBack == mCallBack)
		{
			info.erase(begin);
			break;
		}
	}
}

void Mouse::RemoveCallBack(void* pThis)
{
	for (auto begin = info.begin(); begin != info.end(); begin++)
	{
		if (begin->pthis == pThis)
		{
			info.erase(begin);
			break;
		}
	}
}

void UpdateCallBacks(float x, float y, MouseButton mType, MouseState mState)
{
	for (auto& Callback : info)
	{
		if (Callback.pthis)
			(*(Event*)(Callback.pthis).* & Event::MouseEvent)(x,y,mType,mState);
		else
			Callback.mCallBack(x, y, mType, mState);
	}
}

void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
{
	currentZoom = static_cast<float>(yOffset);
	UpdateCallBacks(static_cast<float>(xOffset), static_cast<float>(yOffset),MouseButton::Undefined, MouseState::Wheel);
}

void MouseInsideCallBack(GLFWwindow* window, int entered)
{
	flags &= ~(1 << 6);
	flags |= entered << 6;
	UpdateCallBacks(0.0f, 0.0f, MouseButton::Undefined,Mouse::IsMouseOutSideOfWindow() ? MouseState::Leave : MouseState::Enter);
}

void MouseMoveCallBack(GLFWwindow* window, double xOffset, double yOffset)
{
	positon = glm::vec2(xOffset, yOffset);
	UpdateCallBacks(static_cast<float>(xOffset), static_cast<float>(yOffset), MouseButton::Undefined, MouseState::Move);
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	double delta = 0.0f;
	bool dClick = false;
	if (action == 1)
	{
		static auto before = std::chrono::system_clock::now();
		auto now = std::chrono::system_clock::now();
		delta = std::chrono::duration <double, std::milli>(now - before).count();
		before = now;
	}

	if (delta > 1.0 && delta < 200.0) // double click
		dClick = true;

	flags &= ~(3 << (2 * button));
	flags |= (action + dClick) << (2 * button);
	
	UpdateCallBacks(0.0f, 0.0f, MouseButton::Undefined, MouseState(dClick + action));
}


