#pragma once
#include "typing.h"


class Textrue
{
public:
	Textrue(const std::string& path);
	~Textrue();

	void Bind(uint slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

private:
	uint renderer;
	uchar* localBuffer;
	int width, height, BPP;
	std::string filePath;
	bool mutable isBind;

};

