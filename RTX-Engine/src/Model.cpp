#include "Model.h"

void Model::InitializeComponent()
{
	this->shader = new ShaderProgram();
	this->shader->Initialize("resources/shaders/pbr.vert", "resources/shaders/pbr.frag");

	this->camera = nullptr;
	this->mesh = nullptr;
	this->modelVAO = nullptr;
	this->tex = nullptr;

	this->name = "Model";

	Serialize();
}

Model::~Model()
{
	delete shader;
	delete modelVAO;
	delete mesh;
	delete tex;
}

void Model::LoadMesh(const char* fileName)
{
	mesh = new Mesh(fileName);
	// mesh->ShadeSmooth(1.5f, 45.0f);
	
	CreateVAO();
}

void Model::LinkTexture(TextureMappingType texType, const char* fileName)
{
	shader->BindProgram();

	tex = new Texture2D(shader, texType);
	tex->LoadImage(fileName);
	textures.push_back(tex);
}

void Model::LinkSkybox(CubeMap* skybox)
{
	this->skybox = skybox;
}

void Model::LinkLights(std::vector<Light*>* lights)
{
	this->lights = *lights;
}

void Model::Draw(Camera* camera)
{
	shader->BindProgram();
	
	DispatchMatrices(camera);
	
	modelVAO->Bind();
	for (Texture2D* texture : textures)
		texture->Bind();

	glDrawElements(GL_TRIANGLES, mesh->numVerts, GL_UNSIGNED_INT, 0);
}

void Model::DispatchMatrices(Camera* camera)
{
	glm::mat4x4 view, proj, model;

	Transformable* transform = this->sceneObject->transform;

	model = glm::mat4x4(1.0f);
	model = glm::translate(model, transform->position);
	model = glm::rotate(model, transform->rotation.x, {1, 0, 0});
	model = glm::rotate(model, transform->rotation.y, {0, 1, 0});
	model = glm::rotate(model, transform->rotation.z, {0, 0, 1});
	model = glm::scale(model, glm::vec3(transform->scale));

	camera->ViewProjMatrices(view, proj);

	glm::mat4x4 MPV = proj * view * model;
	GLfloat shininess = 32.0f;

	for (unsigned int i = 0; i < lights.size(); i++) {
		shader->SetUniform((  "lightPositions[" + std::to_string(i) + "]").c_str(),  UNIFORM_VEC3, &(lights[i]->sceneObject->transform->position));
		shader->SetUniform((     "lightColors[" + std::to_string(i) + "]").c_str(),  UNIFORM_VEC3, &(lights[i]->color));
		shader->SetUniform(("lightIntensities[" + std::to_string(i) + "]").c_str(), UNIFORM_FLOAT, &(lights[i]->intensity));
	}

	shader->SetUniform("viewPos", UNIFORM_VEC3, &(camera->sceneObject->transform->position));
	shader->SetUniform("material.shininess", UNIFORM_FLOAT, &shininess);

	shader->SetUniform("proj", UNIFORM_MAT4X4, &proj);
	shader->SetUniform("view", UNIFORM_MAT4X4, &view);
	shader->SetUniform("model", UNIFORM_MAT4X4, &model);
	shader->SetUniform("MPV", UNIFORM_MAT4X4, &MPV);

	GLuint skyboxTexUnit = (GLuint)TEX_CUBEMAP;
	shader->SetUniform("skybox", UNIFORM_INT, &skyboxTexUnit);
}

void Model::CreateVAO()
{
	std::cout << "creating VAO" << std::endl;

	shader->BindProgram();

	GLuint* indices = new GLuint[mesh->numVerts];
	for (unsigned int i = 0; i < mesh->numVerts; i++)
		indices[i] = i;

	VAO* VertArray = new VAO(mesh->numVerts * 8, mesh->numVerts, 8);
	VertArray->CreateVBO(mesh->numVerts * 8 * sizeof(GLfloat), mesh->attribs);
	VertArray->CreateEBO(indices);
	VertArray->LinkVertexAttribute(0, 3);
	VertArray->LinkVertexAttribute(1, 2);
	VertArray->LinkVertexAttribute(2, 3);

	this->modelVAO = VertArray;
}
