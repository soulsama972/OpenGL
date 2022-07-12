#pragma once
#include"typing.h"
#include<string>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>

#include"glm/glm.hpp"

struct ShaderSource
{
	std::string vertexSrc;
	std::string framgentSrc;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform1i(const std::string& name, int val);
	void SetUniform1f(const std::string& name, float val);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
	void SetUinforms();
private:
	ShaderSource ParseShader(const std::string& filePath);
	int GetUniformLocation(const std::string& name) const;
	int CompileShader(const std::string& source, uint type);
	uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	
	uint m_RendererID;
	std::string m_filePath;
	mutable std::unordered_map<std::string, uint> m_Cache;

};

