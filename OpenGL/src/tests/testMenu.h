#pragma once
#include"test.h"
#include<functional>
class TestMenu : public Test
{
public:
	TestMenu(Test*& currentTest);
	void OnImGuiRender() override;
	template<typename T>
	void RegisterTest(const std::string& name)
	{
		tests.push_back(std::make_pair(name, []() {return new T(); }));
	}
	void ExitToMenu();
private:
	Test*& currentTest;
	std::vector<std::pair<std::string, std::function<Test* ()>>> tests;
};

