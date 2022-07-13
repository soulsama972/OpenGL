#pragma once


#include"test.h"
#include"objLoader.h"

class TestDrawModel : public Test
{
public:
	TestDrawModel();
	~TestDrawModel();
	void OnRender() override;
	void OnImGuiRender() override;


private:
	
	Mesh<ObjLoader::Vertex> mesh;
	Shader* shader;
	float color[4];
	glm::mat4 view, proj;
	glm::vec3 t1,t2;
};