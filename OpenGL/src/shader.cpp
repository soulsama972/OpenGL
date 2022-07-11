#include "shader.h"
#include"renderer.h"

Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_RendererID(0) 
{
    ShaderSource source = ParseShader(filePath);
    m_RendererID = CreateShader(source.vertexSrc, source.framgentSrc);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int val)
{
    GLCall(glUniform1i(GetUniformLocation(name), val));
}

void Shader::SetUniform1f(const std::string& name, float val)
{
    GLCall(glUniform1f(GetUniformLocation(name), val));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE, &mat[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_Cache.find(name) != m_Cache.end())
        return m_Cache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesnt exist!" << std::endl;
    m_Cache[name] = location;
    return location;
}

ShaderSource Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[2];
    int mode = -1;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                mode = 0;
            else if (line.find("fragment") != std::string::npos)
                mode = 1;
        }
        else
            ss[mode] << line << "\n";
    }
    return { ss[0].str(), ss[1].str() };
}

int Shader::CompileShader(const std::string& source, uint type)
{
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, NULL));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n" << message << std::endl;
        delete[] message;
        return 0;
    }
    return id;
}

uint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(uint program = glCreateProgram());
    uint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}