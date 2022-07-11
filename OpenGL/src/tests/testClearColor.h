#pragma once

#include"test.h"


class TestClearColor : public Test
{
public:
	TestClearColor();

	void OnRender() override;
	void OnImGuiRender() override;

private:
	float m_clearColor[4];

};