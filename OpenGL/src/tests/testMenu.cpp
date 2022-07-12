#include "testMenu.h"

TestMenu::TestMenu(Test*& currentTest) :currentTest(currentTest)
{
}

void TestMenu::OnImGuiRender()
{
	for (auto& test: tests)
	{
		if (ImGui::Button(test.first.c_str()))
			currentTest = test.second();
	}
}

void TestMenu::ExitToMenu()
{
	if (ImGui::Button("Exit to Menu"))
	{
		if(currentTest != this)
			delete currentTest;
		currentTest = (Test*)this;
	}
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
}
