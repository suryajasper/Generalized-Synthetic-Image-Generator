#include "Mesh.h"

Mesh::Mesh(const char* fileName)
{
	LoadMeshDataFromFile(fileName);
}

Mesh::~Mesh()
{
	delete shaderProgram;
	delete texture;
}

void Mesh::PrintMeshData()
{
	unsigned int i = 0;
	while (i < numVerts - 1) {
		for (unsigned int j = 0; j < 8; j++) {
			std::cout << attribs[i * 8 + j] << "\t";
		}
		std::cout << std::endl;
		i++;
	}
}

void Mesh::AddVertex(GLfloat x, GLfloat y, GLfloat z)
{
	vertices.push_back(glm::vec3(x, y, z));
}

void Mesh::AddTexCoord(GLfloat u, GLfloat v)
{
	texCoords.push_back(glm::vec2(u, v));
}

void Mesh::AddNormal(GLfloat x, GLfloat y, GLfloat z)
{
	normals.push_back(glm::vec3(x, y, z));
}

void Mesh::AddFace(unsigned int faceVerts[3], unsigned int faceTexCoords[3], unsigned int faceNorms[3])
{
	for (unsigned int i = 0; i < 3; i++) {
		if (DEBUG_MODE) std::cout << "adding face "
			<< "\t" << vertices.size() << "-" << faceVerts[i] - 1
			<< "\t" << texCoords.size() << "-" << faceTexCoords[i] - 1
			<< "\t" << normals.size() << "-" << faceNorms[i] - 1
			<< std::endl;

		glm::vec3 vert = vertices[faceVerts[i]-1];
		glm::vec2 texCoord = texCoords[faceTexCoords[i]-1];
		glm::vec3 norm = normals[faceNorms[i]-1];

		if (DEBUG_MODE) {
			std::cout << "vertex" << "\t" << vert.x << "\t" << vert.y << "\t" << vert.z << std::endl;
			std::cout << "texture" << "\t" << texCoord.x << "\t" << texCoord.y << std::endl;
			std::cout << "normal" << "\t" << norm.x << "\t" << norm.y << "\t" << norm.z << std::endl;
			std::cout << "----------------------------" << std::endl;
		}

		attribs[numVerts * 8 + 0] = vert.x; attribs[numVerts * 8 + 1] = vert.y; attribs[numVerts * 8 + 2] = vert.z;
		attribs[numVerts * 8 + 3 + 0] = texCoord.x; attribs[numVerts * 8 + 3 + 1] = texCoord.y;
		attribs[numVerts * 8 + 5 + 0] = norm.x; attribs[numVerts * 8 + 5 + 1] = norm.y; attribs[numVerts * 8 + 5 + 2] = norm.z;
		
		numVerts++;
	}
}

std::istream& slash(std::istream& in) {
	if (in.get() != '/')
		in.setstate(std::ios_base::failbit);
	return in;
}

void Mesh::LoadMeshDataFromFile(const char* fileName)
{
	std::cout << fileName << std::endl;
	std::ifstream cin(fileName);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	bool readFaces = false;

	unsigned int i = 0;

	char func[99]; GLfloat data[3];
	while (!cin.eof()) {
		cin >> func;

		if (DEBUG_MODE) std::cout << "---------X" << func << "X" << std::endl;

		if (strcmp(func, "v") == 0) {
			cin >> data[0] >> data[1] >> data[2];
			if (DEBUG_MODE) std::cout << "vertex " << data[0] << "\t" << data[1] << "\t" << data[2] << std::endl;
			AddVertex(data[0], data[1], data[2]);
		} 
		else if (strcmp(func, "vt") == 0) {
			cin >> data[0] >> data[1];
			if (DEBUG_MODE) std::cout << "tex coord " << data[0] << "\t" << data[1] << std::endl;
			AddTexCoord(data[0], data[1]);
		} 
		else if (strcmp(func, "vn") == 0) {
			cin >> data[0] >> data[1] >> data[2];
			if (DEBUG_MODE) std::cout << "normal " << data[0] << "\t" << data[1] << "\t" << data[2] << std::endl;
			AddNormal(data[0], data[1], data[2]);
		} 
		else if (strcmp(func, "f") == 0) {
			readFaces = true;

			unsigned int vis[3], tcis[3], nis[3];

			cin >> vis[0] >> slash >> tcis[0] >> slash >> nis[0]
				>> vis[1] >> slash >> tcis[1] >> slash >> nis[1]
				>> vis[2] >> slash >> tcis[2] >> slash >> nis[2];

			if (DEBUG_MODE) std::cout << "face " << "\t"
				<< vis[0] << "\t" << tcis[0] << "\t" << nis[0] << "\t"
				<< vis[1] << "\t" << tcis[1] << "\t" << nis[1] << "\t"
				<< vis[2] << "\t" << tcis[2] << "\t" << nis[2] << "\t" 
				<< std::endl;

			AddFace(vis, tcis, nis);
		}

		i++;
	}

	cin.close();

	vertices.clear();
	normals.clear();
	texCoords.clear();
}

