#pragma once
#include"typing.h"
#include"input.h"
#include"timer.h"
// gl
#include<GL/glew.h>
#include<GLFW/glfw3.h>

// imgui
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"



class Window 
{
public:
	Window();
	Window(uint screenWidth, uint screenHeight, const std::string& title);
	~Window();

	void Init(uint screenWidth, uint screenHeight, const std::string& title);
	
	void SetTitle(const std::string& title) const;
	
	bool IsDestoryed() const;
	
	void Present() const;
	
	Input input;
	Timer timer;

private:
	GLFWwindow* window;
	uint screenWidth;
	uint screenHeight;

};


