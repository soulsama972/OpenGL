#include "textrue.h"

#include"std_image/std_image.h"

Textrue::Textrue(const std::string& path) : m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_Renderer));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Textrue::~Textrue()
{
	GLCall(glDeleteTextures(1, &m_Renderer));
}

void Textrue::Bind(uint slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));
}

void Textrue::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
