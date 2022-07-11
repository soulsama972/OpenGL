#pragma once
#include"renderer.h"


class Textrue
{
public:
	Textrue(const std::string& path);
	~Textrue();

	void Bind(uint slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	uint m_Renderer;
	uchar* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	std::string m_FilePath;


};

