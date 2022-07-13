#include "textrue.h"

#include"std_image/std_image.h"

Textrue::Textrue(const std::string& path) : filePath(path), localBuffer(nullptr), width(0), height(0), BPP(0), isBind(false)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	GLCall(glGenTextures(1, &renderer));
	GLCall(glBindTexture(GL_TEXTURE_2D, renderer));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	
	if (localBuffer)
		stbi_image_free(localBuffer);
}

Textrue::~Textrue()
{
	GLCall(glDeleteTextures(1, &renderer));
}

void Textrue::Bind(uint slot) const
{
	if (!isBind)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, renderer));
		isBind = true;
	}
}

void Textrue::UnBind() const
{
	if (isBind)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		isBind = false;
	}
}
