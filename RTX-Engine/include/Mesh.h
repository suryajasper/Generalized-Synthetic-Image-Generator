#pragma once
#include <glm/glm.hpp>
#include "Texture2D.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

class Mesh
{
public:
	Mesh(char* fileName);
	~Mesh();
	
	void LinkTexture(Texture2D* tex2D);
	void PrintMeshData();

	unsigned int numVerts = 0;
	GLfloat attribs[1000000];

private:
	ShaderProgram* shaderProgram;
	UniformManager* uniformManager;
	Texture2D* texture;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	
	bool DEBUG_MODE = false;

	void AddVertex(GLfloat x, GLfloat y, GLfloat z);
	void AddTexCoord(GLfloat u, GLfloat v);
	void AddNormal(GLfloat x, GLfloat y, GLfloat z);

	void AddFace(unsigned int faceVerts[3], unsigned int faceTexCoords[3], unsigned int faceNorms[3]);

	void LoadMeshDataFromFile(char* fileName);
};

