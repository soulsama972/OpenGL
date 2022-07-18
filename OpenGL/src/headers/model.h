#pragma once
#include"mesh.h"
#include"textrue.h"

// assimp
#include<assimp/scene.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>

// glm
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

struct Vertex
{
	glm::vec3 p;
	glm::vec2 t;
	glm::vec3 n;
};

class Model
{
public:
	Model();
	~Model();
	Model(const std::string& path, const std::string& baseDir);

	bool Init(const std::string& path, const std::string& baseDir);
	void AddTextrue(const std::string& path);
	void Draw();
private:

    void ProcessNode(const aiNode* node, const aiScene* scene, const VertexBufferLayout& layout, const std::string& baseDir);
    void ProcessMesh(const aiMesh* mesh, const aiScene* scene, const VertexBufferLayout& layout, const std::string& baseDir);
	void loadMaterialTextures(const aiMaterial* mat, const aiTextureType& type, const std::string& typeName,const  std::string& baseDir);

	std::vector<Mesh<Vertex>*> meshes;
	std::vector<Texture*> textures;
	bool initialized;
};


