#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include "loadShaders.h"
#include "Matrices.h"
#include "Vectors.h"
#include "Shaders.h"
#include "Map.h"

class Mesh{
	
	vector<vec3> triNormals;

public:
	GLuint vbomesh, normalBuffer, vaoID;

	vector<GLfloat> mesh, normals;

	int sideNum; //Number of squares on side of mesh
	GLfloat meshSize;
	int mapSize;


	Mesh(int mapSize, int meshSize);

	void genTriangleMesh(vector<GLfloat> heightData);
	void genTriangleNormals();

	void genVertexMesh(vector<GLfloat> heightData);
	void genVertexNormals();

	void initVertArray(); //Requires GLFW and GLEW to be initialized
	void disableVertArrays();
	void draw();

	GLfloat getNormals();

};