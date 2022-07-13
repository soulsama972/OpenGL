#include "objLoader.h"

using namespace ObjLoader;

void ObjLoader::loadObject(const std::string& filePath, Obj& obj)
{
	std::vector<Pos> vertex;
	std::vector<Tex> tex;
	std::vector<Pos> normal;
	std::vector<uint> iV,iT,iN;

	std::string line , prefix;
	std::stringstream ss;
	std::ifstream file(filePath);
	
	Pos v;
	Tex t;

	if (!file)
		return;

	while (std::getline(file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}

		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v")
		{
			ss >> v.x >> v.y >> v.z;
			vertex.push_back(v);
		}
		else if (prefix == "vn")
		{
			ss >> v.x >> v.y >> v.z;
			normal.push_back(v);
		}

		else if (prefix == "vt")
		{
			ss >> t.x >> t.y >> v.z;
			tex.push_back(t);
		}

		else if (prefix == "f" && line.find("//") == std::string::npos)
		{
			uint tempIndex, counter = 0, count = 0;
			while (ss >> tempIndex)
			{
				if (counter == 0) // vertex
				{
					iV.push_back(tempIndex);
				}
				else if (counter == 1) // textrue
				{
					iT.push_back(tempIndex);
				}
				else if (counter == 2) // normal
				{
					iN.push_back(tempIndex);
				}

				if (ss.peek() == ' ')
				{
					counter++;
					ss.ignore(1);
				}
				if (ss.peek() == '/')
				{
					ss.ignore(1);
					if (ss.peek() == '/')
						ss.ignore(1);
					counter++;
				}
				
				if (counter == 2)
				{
					counter = 0;
					count++;
				}
			}
		}
	}
	obj.vertices.resize(iV.size() + 1);

	for (uint i = 0; i < iV.size(); i++)
	{
		
		obj.vertices[i].v = vertex[iV[i] -1];
		obj.vertices[i].t = tex[iT[i] -1];
		//obj.vertices[i].n = normal[iN[i] -1];
	}

}
