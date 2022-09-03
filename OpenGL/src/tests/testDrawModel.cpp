#include "testDrawModel.h"
#include"window.h"
extern Window window;
glm::vec3 testUp = { 0,0,0 };
TestDrawModel::TestDrawModel() :zoom(45.0f)
{
    shader = new Shader("res/shaders/testDrawModel.shader");
	std::string baseDir = "./res/models/gun";
	model.Init(baseDir + "/gun.obj", baseDir);
	
	proj = glm::perspective(glm::radians(zoom), 4.0f/3.0f, 0.1f, 1000.0f);
	//proj = glm::ortho(0.0f,1920.0f,0.0f,1080.0f, 0.1f, 1000.0f);

	renderer.EnableZBuffer();
	timer.Init();

	Input::InsertCallBack(this);
	Mouse::InsertCallBack(this);
	
	camera.pos = { 0, 0, 0 };
	camera.updateCameraVectors();
	
}

TestDrawModel::~TestDrawModel()
{
	delete shader;
	renderer.DisableZBuffer();
	Input::RemoveCallBack(this);
	Mouse::RemoveCallBack(this);
}

void TestDrawModel::OnRender()
{
	shader->Bind();
	auto s = glm::scale(glm::mat4(1.0f), { 1, 1,1 });
	auto t = glm::translate(glm::mat4(1.0f), { 0, 0,0 });
	//auto r = glm::rotate(glm::mat4(1.0f),90.f, { 0.0f, 1zz.0f, 0.0f });
	auto r = glm::mat4(1.0f);
	glm::mat4 m = t * r * s;
	shader->SetUniformMat4f("u_MVP", proj * camera.GetViewMatrix() * m);
	model.Draw();

}

void TestDrawModel::OnImGuiRender()
{	
	if(ImGui::SliderFloat3("camera.Position.x", &camera.pos.x, -360.0f, 360.0f))
		camera.updateCameraVectors();

	if (ImGui::SliderFloat3("1", &testUp.x, -1.0f, 1.0f))
	{
		camera = Camera(camera.pos, testUp);
	}
}

void TestDrawModel::OnUpdate(float deltaTime)
{
	timer.Tick();
	processInput(deltaTime);
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

void TestDrawModel::MouseEvent(float x, float y, MouseButton mType, MouseState mState)
{
	static float lastX, lastY;
	static bool firstTime = true;

	if (Input::IsKeyPress(KeyType::KEY_Z))
	{
		window.ShowCurosr();
		lastX = x;
		lastY = y;
		return;
	}
	else
		window.HideCursor();
	
		


	if (mState == MouseState::Wheel)
	{
		zoom -= (float)y;
		if (zoom < 1.0f)
			zoom = 1.0f;
		if (zoom > 45.0f)
			zoom = 45.0f;

		//proj = glm::perspective(glm::radians(zoom), 4.0f / 3.0f, 0.1f, 1000.0f);
	}
	if (mState == MouseState::Move)
	{
		if (firstTime)
		{
			lastX = x;
			lastY = y;
			firstTime = false;
		}
		camera.ProcessMouseMovement(x - lastX, lastY - y);
		lastX = x;
		lastY = y;
	}

}


