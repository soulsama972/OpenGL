#pragma once

#include"renderer.h"
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

