#include "Model.h"

Model::Model()
{
	this->shader = new ShaderProgram();
	this->shader->Initialize("resources/shaders/default.vert", "resources/shaders/default.frag");

	this->uniformManager = new UniformManager(this->shader);
}

Model::~Model()
{
	delete shader;
	delete uniformManager;
	delete modelVAO;
	delete mesh;
	delete tex;
}

void Model::LoadMesh(const char* fileName)
{
	mesh = new Mesh(fileName);

	CreateVAO();
}

void Model::LinkTexture(const char* fileName)
{
	shader->BindProgram();
	tex = new Texture2D(shader);
	tex->LoadImage(TEX_MAP_COLOR, fileName);
}

void Model::Draw(Camera* camera)
{
	shader->BindProgram();

	GLfloat scale = 0.5f;
	uniformManager->SetUniform("scale", UNIFORM_FLOAT, &scale);
	
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

	camera->ViewProjMatrices(view, proj);
	glm::mat4x4 MPV = proj * view * model;

	uniformManager->SetUniform("MPV", UNIFORM_MAT4X4, &MPV);
}

void Model::CreateVAO()
{
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
