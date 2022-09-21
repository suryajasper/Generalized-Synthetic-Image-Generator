#include "UniformManager.h"

UniformManager::UniformManager(ShaderProgram* shaderProgram)
{
	this->shaderPID = shaderProgram->programId;
}

UniformManager::~UniformManager()
{
}

void UniformManager::SetUniform(const char* uniformName, UniformType type, void* data) 
{
	GLuint uniformLoc = glGetUniformLocation(this->shaderPID, uniformName);

	switch (type) {
	case UNIFORM_MAT4X4:
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr( *((glm::mat4x4*)data) ));
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
	}
}
