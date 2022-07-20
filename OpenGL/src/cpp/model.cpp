#include "model.h"

#define ASSIMP_FLAGS  aiProcess_Triangulate |aiProcess_GenUVCoords |aiProcess_OptimizeMeshes |aiProcess_OptimizeGraph

Model::Model(): initialized(false)
{
}

Model::~Model()
{
    for (uint i = 0; i < meshes.size(); i++)
        delete meshes[i];
    for (uint i = 0; i < textures.size(); i++)
        delete textures[i];
}

Model::Model(const std::string& path, const std::string& baseDir) : initialized(false)
{
    if (!Init(path,baseDir))
        std::cout << "could not load the model" << std::endl;
}

bool Model::Init(const std::string& path, const std::string& baseDir)
{
    Assimp::Importer importer;
    VertexBufferLayout layout;

    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    const aiScene* scene = importer.ReadFile(path.c_str(), ASSIMP_FLAGS);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;
    

    //loadOBJ(scene->mMeshes[0], scene);
    ProcessNode(scene->mRootNode, scene,layout,baseDir);
    initialized = true;

    return true;
}

void Model::AddTextrue(const std::string& path)
{
    textures.push_back(new Texture(path));
}

void Model::Draw()
{
    for (uint i = 0; i < meshes.size(); i++)
    {
        if (i < textures.size())
        {
            textures[i]->Bind(i);
            GLCall(glUniform1i(glGetUniformLocation(1, "tex"), i));
        }
        meshes[i]->Draw();
    }

}

void Model::ProcessNode(const aiNode* node, const aiScene* scene, const VertexBufferLayout& layout, const std::string& baseDir)
{

      // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene,layout,baseDir);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        ProcessNode(node->mChildren[i], scene, layout,baseDir);
}

void Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene, const VertexBufferLayout& layout, const std::string& baseDir)
{
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    // walk through each of the mesh's vertices
    for (uint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        
        vertex.p = vector;
        
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.n = vector;
        }
        // texture coordinates
        if (mesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.t = vec;
        }
        else
            vertex.t = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (uint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];


        for (uint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
        
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", baseDir);
    loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", baseDir);
    loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", baseDir);
    loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", baseDir);

    meshes.push_back(new Mesh(vertices.data(), static_cast<uint>(vertices.size()), indices.data(), static_cast<uint>(indices.size()), layout, static_cast<uint>(vertices.size()),static_cast<uint>( vertices.size()), 1, false));
}

void Model::loadMaterialTextures(const aiMaterial* mat, const aiTextureType& type, const std::string& typeName, const std::string& baseDir)
{
    auto IsExist = [](const std::vector<Texture*>& textures,const std::string& text)
    {
        for (auto& t : textures)
        {
            if (!t->GetFilePath().compare(text))
                return true;
        }
        return false;
    };

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        const std::string path = baseDir + "/" + str.C_Str();
        if(!IsExist(textures, path))
            textures.push_back(new Texture(path));
    }
}


