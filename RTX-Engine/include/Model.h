#pragma once
#include "UniformManager.h"
#include "Texture2D.h"
#include "Transformable.h"
#include "Mesh.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "Light.h"

class Model : public Transformable
{
public:
	Model();
	~Model();

	void LoadMesh(const char* fileName);
	void LinkTexture(const char* fileName);

	void SetLight(Light* light);

	void Draw(Camera* camera);

	ShaderProgram* shader;
private:
	UniformManager* uniformManager;
	VAO* modelVAO;
	Light* light;

	Camera* camera;
	Mesh* mesh;
	Texture2D* tex;

	void DispatchMatrices(Camera* camera);
	void CreateVAO();
};

