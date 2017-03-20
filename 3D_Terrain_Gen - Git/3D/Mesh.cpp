#include <iostream>
#include "Mesh.h"

Mesh::Mesh(int mapSize, int meshSize){
	this->mapSize = mapSize;
	this->meshSize = meshSize;

}

void Mesh::genTriangleMesh(vector<GLfloat> heightData)
{

	int sideNum = mapSize;

	GLfloat xspot = -1;
	GLfloat zspot = -1;
	GLfloat squaresize = meshSize / sideNum; //fit squares into given meshsize

	for (int z = 0; z != sideNum; z++)
	{
		for (int x = 0; x != sideNum; x++)
		{
			mesh.insert(mesh.end(), { xspot, 0.0f, zspot });
			mesh.insert(mesh.end(), { xspot, 0.0f, zspot + squaresize });
			mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot });

			xspot += squaresize;
		}
		xspot = -1;
		for (int x = 0; x != sideNum; x++)
		{
			mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot + squaresize });
			mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot });
			mesh.insert(mesh.end(), { xspot, 0.0f, zspot + squaresize });

			xspot += squaresize;
		}
		xspot = -1;
		zspot += squaresize;
	}

	for (int i = 1; i < mesh.size(); i += 3)
	{
		mesh[i] = heightData[(mesh[i - 1] + 1) / squaresize + (sideNum + 1)*(mesh[i + 1] + 1) / squaresize];
	}
}

void Mesh::genTriangleNormals()
{
	for (int i = 0; i != mesh.size(); i += 9)
	{
		vec3 first(mesh[i + 3] - mesh[i], mesh[i + 4] - mesh[i + 1], mesh[i + 5] - mesh[i + 2]);
		vec3 second(mesh[i + 6] - mesh[i], mesh[i + 7] - mesh[i + 1], mesh[i + 8] - mesh[i + 2]);

		vec3 normal = first.cross(second);
		normal.normalize();

		triNormals.push_back(normal);
		triNormals.push_back(normal);
		triNormals.push_back(normal);
	}

	normals.resize(mesh.size()); //check

	for (int i = 0; i != triNormals.size(); i++)
	{
		normals[i * 3] = triNormals[i].x;
		normals[i * 3 + 1] = triNormals[i].y;
		normals[i * 3 + 2] = triNormals[i].z;
	}
}

void Mesh::initVertArray()
{
	//generate vao
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vbomesh);
	glBindBuffer(GL_ARRAY_BUFFER, vbomesh);
	glBufferData(GL_ARRAY_BUFFER, mesh.size()*sizeof(GLfloat), &(mesh[0]), GL_STATIC_DRAW);

	//buffer attribute for mesh
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbomesh);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.size()*sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

	//bufffer for vertexnorms
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
}

void Mesh::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, mesh.size());
}

void Mesh::disableVertArrays()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}