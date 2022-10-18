#include "Model.h"

Model::Model()
{
	this->shader = new ShaderProgram();
	this->shader->Initialize("resources/shaders/default.vert", "resources/shaders/default.frag");
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
	mesh->ShadeSmooth();
	
	CreateVAO();
}

void Model::LinkTexture(const char* fileName)
{
	shader->BindProgram();
	tex = new Texture2D(shader);
	tex->LoadImage(TEX_MAP_COLOR, fileName);
}

void Model::SetLight(Light* light)
{
	this->light = light;
}

void Model::Draw(Camera* camera)
{
	shader->BindProgram();
	
	DispatchMatrices(camera);
	
	modelVAO->Bind();
	tex->Bind();

	glDrawElements(GL_TRIANGLES, mesh->numVerts, GL_UNSIGNED_INT, 0);
}

void Model::DispatchMatrices(Camera* camera)
{
	glm::mat4x4 view, proj, model;

	model = glm::mat4x4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x, {1, 0, 0});
	model = glm::rotate(model, rotation.y, {0, 1, 0});
	model = glm::rotate(model, rotation.z, {0, 0, 1});
	model = glm::scale(model, glm::vec3(scale));

	camera->ViewProjMatrices(view, proj);

	glm::mat4x4 MPV = proj * view * model;

	shader->SetUniform("lightPosIn", UNIFORM_VEC3, &(light->position));
	shader->SetUniform("lightColorIn", UNIFORM_VEC3, &(light->color));
	shader->SetUniform("lightIntensityIn", UNIFORM_FLOAT, &(light->intensity));

	shader->SetUniform("proj", UNIFORM_MAT4X4, &proj);
	shader->SetUniform("view", UNIFORM_MAT4X4, &view);
	shader->SetUniform("model", UNIFORM_MAT4X4, &model);
	shader->SetUniform("MPV", UNIFORM_MAT4X4, &MPV);
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
