#pragma once
#include "typing.h"


class Texture
{
public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	void Init(const std::string& path);
	void Bind(uint slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline std::string GetFilePath() const { return filePath; }
private:
	uint renderer;
	uchar* localBuffer;
	int width, height, BPP;
	std::string filePath;
	static uint bindId;

};

