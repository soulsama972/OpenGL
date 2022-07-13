#pragma once


#include"typing.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

namespace ObjLoader
{
	struct Pos
	{
		float x, y, z;
	};
	using Normal = Pos;

	struct Tex
	{
		float x, y;
	};
	struct Color
	{
		float r, g, b, a;
	};
	struct Vertex
	{
		Pos v;
		Tex t;
		Normal n;
	};
	struct Obj
	{
		std::vector<Vertex> vertices;
		std::vector<uint> indices;

	};

	void loadObject(const std::string& filePath, Obj& obj);
	

}

