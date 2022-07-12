#pragma once

#include"shader.h"
#include"textrue.h"
#include"renderer.h"
#include"vertexArray.h"
#include"indexBuffer.h"
#include"vertexBuffer.h"
#include"vertexBufferLayout.h"


// imgui
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
class Test
{
public:
	Test(): isBegin(false) {}
	virtual ~Test() {};
	virtual void OnUpdate(float deltaTime) {};
	virtual void OnRender() {};
	virtual void OnImGuiRender() {};

	inline void ImGuiBegin() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}
	inline void ImGuiEnd() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

protected:

	Renderer renderer;

private:
	bool isBegin;
};

