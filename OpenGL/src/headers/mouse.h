#pragma once
#include"event.h"
#include"glm/glm.hpp"


class Mouse
{
public:
	Mouse() = default;
	static float GetWheelDiffrent();
	static glm::vec2 GetMousePos();
	
	static bool IsRightClicked(bool doubleClick = false);
	static bool IsLeftClicked(bool doubleClick = false);
	static bool IsMiddleCLicked(bool doubleClick = false);
	static bool IsMouseOutSideOfWindow();

	static void InsertCallBack(void* pThis);
	static void InsertCallBack(MouseEventCallBack mCallBack);
	
	static void RemoveCallBack(void* pThis);
	static void RemoveCallBack(MouseEventCallBack mCallBack);

private:
	static bool WrapIsClicked(uchar value, bool doubleClick);
};


