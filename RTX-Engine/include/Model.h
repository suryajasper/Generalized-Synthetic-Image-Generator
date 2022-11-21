#pragma once

#include "Transformable.h"
#include "Component.h"

#include "Texture2D.h"
#include "CubeMap.h"
#include "Mesh.h"

#include "Camera.h"
#include "Light.h"

#include "ShaderProgram.h"
#include "VAO.h"

class Model : public Component
{
public:
	~Model();

	void InitializeComponent() override;
	void Serialize() override {};

	void LoadMesh(const char* fileName);
	void LinkTexture(TextureMappingType texType, const char* fileName);

	void LinkSkybox(CubeMap* skybox);
	void LinkLights(std::vector<Light*>* lights);

	void Draw(Camera* camera);

	ShaderProgram* shader;
private:
	VAO* modelVAO;
	std::vector<Light*> lights;
	CubeMap* skybox;

	Camera* camera;
	Mesh* mesh;
	std::vector<Texture2D*> textures;
	Texture2D* tex;

	void DispatchMatrices(Camera* camera);
	void CreateVAO();
};

