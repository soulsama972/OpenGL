#include "vertexArray.h"

VertexArray::VertexArray(): isBind(false)
{
	GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&rendererID));
}

void VertexArray::Bind()const
{
	if (!isBind)
	{
		GLCall(glBindVertexArray(rendererID));
	}
	isBind = true;
}

void VertexArray::UnBind() const
{
	if (isBind)
	{
		GLCall(glBindVertexArray(0));
	}
	isBind = false;
}
