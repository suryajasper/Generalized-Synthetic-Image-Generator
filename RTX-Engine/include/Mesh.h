#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include "Texture2D.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

#include <fstream>
#include <iostream>

const int MAX_ATTRIB = 10000000;
typedef unsigned long long hash;

struct MeshVert {
	unsigned int numNorms;
	glm::vec3 normSum;

	void addNorm(glm::vec3 norm) {
		normSum += norm;
		numNorms++;
	}

	void average() {
		normSum /= (GLfloat)numNorms;
	}
};

class Mesh
{
public:
	Mesh(const char* fileName);
	~Mesh();

	void PrintMeshData();
	void ShadeSmooth();

	unsigned int numVerts = 0;
	unsigned int numUniqueVerts = 0;

	GLfloat attribs[MAX_ATTRIB];
	MeshVert meshVerts[MAX_ATTRIB / 3];
	unsigned int objToLoc[MAX_ATTRIB / 3];

private:
	ShaderProgram* shaderProgram;
	Texture2D* texture;

	std::hash<glm::vec3> hashVec3;

	std::map<hash, std::vector<unsigned int>> vertToNormLocs;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	
	bool DEBUG_MODE = false;

	void AddVertex(GLfloat x, GLfloat y, GLfloat z);
	void AddTexCoord(GLfloat u, GLfloat v);
	void AddNormal(GLfloat x, GLfloat y, GLfloat z);

	void AddFace(unsigned int faceVerts[3], unsigned int faceTexCoords[3], unsigned int faceNorms[3]);

	void LoadMeshDataFromFile(const char* fileName);
};

