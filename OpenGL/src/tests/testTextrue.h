#include"test.h"




class TestTextrue2D : public Test
{
public:
	 TestTextrue2D();
	~TestTextrue2D();

	void OnRender() override;
	void OnImGuiRender() override;

	void AddTextrue(glm::vec3 pos, float  i);
	void UpdateTextrue(uint index, glm::vec2 pos);

private:
	struct v
	{
		glm::vec2 pos;
		glm::vec2 tex;
		glm::vec3 transalte;
		float index;
	};

	Mesh<v> mesh;
	Shader* shader;
	Texture* tex, *tex2;

	glm::mat4 view, proj;
	glm::vec3 t1, t2;
	uint index;
};