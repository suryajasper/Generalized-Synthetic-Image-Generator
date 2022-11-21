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
    std::cout << "--COMPILE shader [" << path << "]: " << ((status == GL_TRUE) ? "success" : "fail") << std::endl;

    return shader;
}

void ShaderProgram::SetUniform(const char* uniformName, UniformType type, void* data)
{
    GLuint uniformLoc = glGetUniformLocation(this->programId, uniformName);

    switch (type) {
    case UNIFORM_MAT4X4:
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(*((glm::mat4x4*)data)));
        break;
    case UNIFORM_VEC3:
        glUniform3fv(uniformLoc, 1, glm::value_ptr(*((glm::vec3*)data)));
        break;
    case UNIFORM_VEC2:
        glUniform2fv(uniformLoc, 1, glm::value_ptr(*((glm::vec2*)data)));
        break;
    case UNIFORM_FLOAT:
        glUniform1fv(uniformLoc, 1, (GLfloat*)data);
        break;
    case UNIFORM_INT:
        glUniform1i(uniformLoc, *((GLint*)data));
        break;
    }
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