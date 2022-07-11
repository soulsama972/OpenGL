#include "testClearColor.h"
#include "renderer.h"
TestClearColor::TestClearColor() : m_clearColor{ 0.0f, 0.5f, 0.5f, 1.0f }
{
}

void TestClearColor::OnRender()
{
	renderer.Clear(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
}

void TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_clearColor);
}


