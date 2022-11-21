#include "CubeMap.h"

CubeMap::CubeMap(ShaderProgram* shader) 
	: Texture2D(shader, TEX_CUBEMAP)
{
    Bind();

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    CreateVAO();
}

CubeMap::~CubeMap()
{
    delete skyboxVAO;
}

bool CubeMap::LoadFaces(std::string faces[6])
{
    shader->BindProgram();
	this->Bind();

    int width, height, nrChannels;
    for (unsigned int i = 0; i < 6; i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, STBI_rgb);
        if (data)
        {
            std::cout << "Loaded cubemap face " << faces[i] << " successfully" << std::endl;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            return false;
        }
    }

    GLuint texUnit = (GLuint)mapType;
    shader->SetUniform("skybox", UNIFORM_INT, &texUnit);

	return true;
}

void CubeMap::Draw(Camera* camera)
{
    glm::mat4 view, proj;
    camera->ViewProjMatrices(view, proj);
    view = glm::mat4(glm::mat3(view));

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    shader->BindProgram();
    skyboxVAO->Bind();
    this->Bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    shader->SetUniform("proj", UNIFORM_MAT4X4, &proj);
    shader->SetUniform("view", UNIFORM_MAT4X4, &view);

    skyboxVAO->Unbind();
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}

void CubeMap::Bind()
{
    glEnable(GL_TEXTURE_CUBE_MAP);
    glActiveTexture(GL_TEXTURE0 + (GLuint)mapType);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texId);
}

void CubeMap::Unbind()
{
    glActiveTexture(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::CreateVAO()
{
    GLfloat skyboxVertices[36*3] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    GLuint skyboxIndices[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    };

    GLuint numVertComps = 36 * 3;
    GLuint numVerts = 36;

    shader->BindProgram();

    skyboxVAO = new VAO(numVertComps, numVerts, 3);
    skyboxVAO->CreateVBO(sizeof(skyboxVertices), skyboxVertices);
    skyboxVAO->CreateEBO(skyboxIndices);
    skyboxVAO->LinkVertexAttribute(0, 3);
}