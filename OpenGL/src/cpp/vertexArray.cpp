#include "vertexArray.h"

uint VertexArray::bindID = INVALID_ID;

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	if (rendererID != INVALID_ID)
	{
		UnBind();
		GLCall(glDeleteVertexArrays(1, &rendererID));
	}
}

void VertexArray::Bind()const
{
	if (bindID != rendererID)
	{
		GLCall(glBindVertexArray(rendererID));
		bindID = rendererID;
	}
}

void VertexArray::UnBind() const
{
	if (bindID == rendererID)
	{
		GLCall(glBindVertexArray(0));
		bindID = INVALID_ID;
	}
}
