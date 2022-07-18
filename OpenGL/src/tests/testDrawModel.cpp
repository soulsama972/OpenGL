#include "testDrawModel.h"

float delta = 0.1f;

TestDrawModel::TestDrawModel()
{
    shader = new Shader("res/shaders/testDrawModel.shader");
	std::string baseDir = "./res/models/gun";
	model.Init(baseDir + "/Gun.obj", baseDir);

	proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);

	renderer.EnableZBuffer();
}

TestDrawModel::~TestDrawModel()
{
	delete shader;
	renderer.DisableZBuffer();
}

void TestDrawModel::OnRender()
{
	shader->Bind();
	glm::mat4 m = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//m = glm::rotate(m, glm::radians(static_cast<float>(glfwGetTime()) * 33), glm::vec3(0.0f, 1.0f, 1.0f));

	shader->SetUniformMat4f("u_MVP", proj * camera.GetViewMatrix() * m);
	model.Draw();
}

void TestDrawModel::OnImGuiRender()
{
	//ImGui::SliderFloat("yaw", &xPos, -360.0f, 360.0f);
	//ImGui::SliderFloat("pitch", &yPos, -360.0f, 360.0f);
}

void TestDrawModel::OnUpdate(float deltaTime)
{
	processInput(deltaTime);
	//camera.Yaw = xPos;
	//camera.Pitch = yPos;
	camera.updateCameraVectors();
}

void TestDrawModel::processInput(float deltaTime)
{
	if (Input::IsKeyPress(KeyType::KEY_W))
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	
	if (Input::IsKeyPress(KeyType::KEY_S))
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

	
	if (Input::IsKeyPress(KeyType::KEY_A))
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);

	
	if (Input::IsKeyPress(KeyType::KEY_D))
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	
}

