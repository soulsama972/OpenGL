#include "testDrawModel.h"
#include <GLFW/glfw3.h>
#include"textrue.h"

#include <filesystem>

std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    std::filesystem::path cwd = std::filesystem::current_path();
    
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        textures.push_back(Texture(str.C_Str()));
    }
    return textures;
}


void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint>& indices, std::vector<Texture>& textures)
{
    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
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
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
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
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


    //return m(vertices, indices, textures);
}

void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint>& indices, std::vector<Texture>& textures)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene,vertices, indices, textures);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, vertices, indices, textures);
	}
}

TestDrawModel::TestDrawModel() :color{ 0, 255.0f, 255.0f, 255.0f }, t2{ 1,1,1 }, t1(0, 0, 0)
{
    tex = new Texture("./res/models/gun/Gun.png");
    shader = new Shader("res/shaders/testDrawModel.shader");
    VertexBufferLayout layout;
    Assimp::Importer importer;
    //"G:\projects\OpenGL\OpenGL\res\models\91-anime_character\Anime_character.fbx"
	const aiScene* scene = importer.ReadFile("./res/models/sp/Only_Spider_with_Animations_Export.dae",  aiProcess_Triangulate | aiProcess_FlipUVs);

    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{

	}
    else
    {
        processNode(scene->mRootNode, scene, vertices, indices, textures);

    }

    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
	
    mesh.Init(nullptr, 0,nullptr,0,layout, indices.size(), vertices.size(), 10);
    mesh.GetVertexBuffer().AppendData(vertices.data(), vertices.size());
    mesh.GetIndexBuffer().Append(indices.data(), indices.size());


    cameraPos = glm::vec3(0.0f, -5.0f, 10.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(1.0f, 1.0f, 0.0f);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	proj = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);





}

TestDrawModel::~TestDrawModel()
{
	delete shader;
}

void TestDrawModel::OnRender()
{
	shader->Bind();
    tex->Bind();

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::rotate(model, glm::radians(static_cast<float>(glfwGetTime()) * 33), glm::vec3(0.0f, 1.0f, 1.0f));


    shader->SetUniform1i("tex", 0);
	shader->SetUniformMat4f("u_MVP", proj * view * model);
	//shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
	renderer.Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), mesh.GetVertexBuffer(), *shader);
}

void TestDrawModel::OnImGuiRender()
{
	ImGui::ColorEdit4("change Color", color);
	ImGui::SliderFloat3("cameraPos", &cameraPos.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("cameraUp", &cameraUp.x, -100.0f, 100.0f);
    ImGui::SliderFloat3("cameraFront", &cameraFront.x, -1.0f, 1.0f);
}

void TestDrawModel::OnUpdate(float deltaTime)
{
	processInput();
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
extern GLFWwindow* window;
void TestDrawModel::processInput()
{

		const float cameraSpeed = 0.1f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


}