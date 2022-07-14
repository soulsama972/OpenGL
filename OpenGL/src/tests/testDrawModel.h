#pragma once


#include"test.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

struct Vertex
{
	glm::vec3 p;
	glm::vec2 t;
	glm::vec3 n;
};


class TestDrawModel : public Test
{
public:
	TestDrawModel();
	~TestDrawModel();
	void OnRender() override;
	void OnImGuiRender() override;
	void OnUpdate(float deltaTime) override;
	void processInput();

private:
	

	Mesh<Vertex> mesh;
	Shader* shader;
	float color[4];
	glm::mat4 view, proj;
	glm::vec3 t1,t2;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	Texture* tex;

};