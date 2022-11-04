#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture2D::Texture2D(ShaderProgram* shaderProgram)
{
	this->shader = shaderProgram;

	glGenTextures(1, &this->texId);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &this->texId);
}

bool Texture2D::LoadImage(TextureMappingType mapType, const char* fileName)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(fileName, &width, &height, &channels, STBI_rgb);
	
	if (image == nullptr) {
		std::cout << "Image " << fileName << " failed to load";
		return false;
	}

	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	shader->SetUniform("tex0", UNIFORM_INT, 0);
	
	Unbind();
	stbi_image_free(image);

	std::cout << "Image successfully loaded: " << width << "x" << height << "\t" << channels << "\n";
	return true;
}

void Texture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);
}

void Texture2D::Unbind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
