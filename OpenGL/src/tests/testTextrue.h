#include"test.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"



class TestTextrue2D : public Test
{
public:
	 TestTextrue2D();
	~TestTextrue2D();

	void OnRender() override;
	void OnImGuiRender() override;

private:
	struct v
	{
		float v[16];
	};

	VertexArray* va;
	VertexBuffer<v>* vb;
	IndexBuffer* ib;
	Shader* shader;
	Textrue* tex;

	glm::mat4 view, proj;
	glm::vec3 t1, t2;
};