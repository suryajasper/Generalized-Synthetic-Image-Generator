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

    return programId;
}

GLuint ShaderProgram::CreateShader(int shaderType, std::string path)
{
    char* shaderSource;
    ReadShaderDataFromFile(path, &shaderSource);

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    std::cout << "--COMPILE shader: " << ((status == GL_TRUE) ? "success" : "fail") << std::endl;

    return shader;
}

void ShaderProgram::AttachShader(GLuint shaderId) 
{
    std::cout << "--ATTACH shader " << shaderId << " to program " << this->programId << std::endl;
    glAttachShader(this->programId, shaderId);
    shaders.push_back(shaderId);
}

void ShaderProgram::DeleteShader(GLuint shaderId)
{
    glDeleteShader(shaderId);
}

void ShaderProgram::BindProgram()
{
    glUseProgram(programId);
}

void ShaderProgram::LinkProgram() 
{
    glLinkProgram(programId);
}

void ShaderProgram::ReadShaderDataFromFile(std::string path, char** shaderData)
{
    std::ifstream fin(path);
    if (!fin) return;

    fin.seekg(0, std::ios::end);
    int len = fin.tellg();

    fin.seekg(0, std::ios::beg);
    *shaderData = new char[len];
    for (int i = 0; i < len; i++)
        (*shaderData)[i] = '\0';
    fin.read(*shaderData, len);
    fin.close();
}