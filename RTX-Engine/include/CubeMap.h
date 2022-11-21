#pragma once

#include "Texture2D.h"
#include "Camera.h"
#include "VAO.h"

#include "stb/stb_image.h"

class CubeMap : public Texture2D
{
public:
	CubeMap(ShaderProgram* shader);
	~CubeMap();

	bool LoadFaces(std::string faces[6]);
	
	void Draw(Camera* camera);

	void Bind();
	void Unbind();

private:
	VAO* skyboxVAO;

	void CreateVAO();
};

