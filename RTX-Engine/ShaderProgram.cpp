#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    this->programId = glCreateProgram();
    this->shaders = std::vector<GLuint>();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->programId);
    for (GLuint shaderId : this->shaders)
        glDeleteShader(shaderId);
}

GLuint ShaderProgram::Initialize(std::string vertFile, std::string fragFile)
{
    GLuint vert = CreateShader(GL_VERTEX_SHADER, vertFile);
    GLuint frag = CreateShader(GL_FRAGMENT_SHADER, fragFile);

    BindProgram();

    AttachShader(vert);
    AttachShader(frag);

    LinkProgram();
}

GLuint ShaderProgram::CreateShader(int shaderType, std::string path)
{
	char** shaderSource = ReadShaderDataFromFile(path);

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSource, NULL);
    glCompileShader(shader);

    return shader;
}

void ShaderProgram::AttachShader(GLuint shaderId) 
{
    glAttachShader(this->programId, shaderId);
    shaders.push_back(shaderId);
}

void ShaderProgram::DeleteShader(GLuint shaderId)
{
    glDeleteShader(shaderId);
    shaders.erase(std::remove(shaders.begin(), shaders.end(), shaderId), shaders.end());
}

void ShaderProgram::BindProgram()
{
    glUseProgram(programId);
}

void ShaderProgram::LinkProgram() 
{
    glLinkProgram(programId);
}

char** ShaderProgram::ReadShaderDataFromFile(std::string path)
{
    char** shaderData;

    std::ifstream fin(path);
    if (!fin) return nullptr;

    fin.seekg(0, std::ios::end);
    int len = fin.tellg();

    fin.seekg(0, std::ios::beg);
    *shaderData = new char[len];
    for (int i = 0; i < len; i++)
        (*shaderData)[i] = '\0';
    fin.read(*shaderData, len);
    fin.close();

    return shaderData;
}