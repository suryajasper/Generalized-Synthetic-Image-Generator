#pragma once
#include "UniformManager.h"
#include "Texture2D.h"
#include "Transformable.h"
#include "Mesh.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "VAO.h"

class Model : Transformable
{
public:
	Model();
	~Model();

	void LoadMesh(const char* fileName);
	void LinkTexture(const char* fileName);

	void Draw(Camera* camera);

	ShaderProgram* shader;
private:
	UniformManager* uniformManager;
	VAO* modelVAO;

	Camera* camera;
	Mesh* mesh;
	Texture2D* tex;

	void DispatchMatrices(Camera* camera);
	void CreateVAO();
};

