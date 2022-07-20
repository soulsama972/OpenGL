#pragma once


#include"test.h"
#include"model.h"
#include"textrue.h"
#include"camera.h"

class TestDrawModel : public Test
{
public:
	TestDrawModel();
	~TestDrawModel();
	void OnRender() override;
	void OnImGuiRender() override;
	void OnUpdate(float deltaTime) override;
	void processInput(float deltaTime);

	void MouseEvent(float x, float y, MouseButton mType, MouseState mState) override;

private:
	Model model;
	Shader* shader;
	glm::mat4 proj;
	Camera camera;
	Timer timer;
	float zoom;
};