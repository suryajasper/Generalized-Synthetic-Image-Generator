#pragma once

#include "Transformable.h"
#include "Component.h"

#include "Texture2D.h"
#include "Mesh.h"

#include "Camera.h"
#include "Light.h"

#include "ShaderProgram.h"
#include "VAO.h"

class Model : public Component
{
public:
	Model();
	~Model();

	void LoadMesh(const char* fileName);
	void LinkTexture(TextureMappingType texType, const char* fileName);

	void LinkLights(std::vector<Light*>* lights);

	void Draw(Camera* camera);

	ShaderProgram* shader;
private:
	VAO* modelVAO;
	std::vector<Light*> lights;

	Camera* camera;
	Mesh* mesh;
	std::vector<Texture2D*> textures;
	Texture2D* tex;

	void DispatchMatrices(Camera* camera);
	void CreateVAO();
};

