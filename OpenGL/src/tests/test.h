#pragma once

#include"mesh.h"
#include"input.h"
#include"mouse.h"
#include"event.h"
#include"timer.h"
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

//glm
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"


class Test : public Event
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

