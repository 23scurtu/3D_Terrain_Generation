#include <iostream>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include "loadShaders.h"
#include "Utils.h"
#include "Matrices.h"
#include "Vectors.h"
#include "Shaders.h"
#include "Map.h"
#include "Mesh.h"

using namespace std;

int main()
{
	//Change mapsize to increase the density or detail of the terrain
	//(keep as a power of two)
	const int mapsize = 512; 
	const int start = 64;

	Map heightMap(mapsize+1,mapsize+1);

	//Setting the corner values of the terrain to some arbitrary initial
	//values, these act as the basepoint for the terrain to be generated from
	heightMap.setElement(0, 0, start);
	heightMap.setElement(0, mapsize, start);
	heightMap.setElement(mapsize, 0, start);
	heightMap.setElement(mapsize, mapsize, start);

	//heightMap.generate(mapsize+1, float(0.6));
    //heightMap.generate(mapsize + 1,3);
	//heightMap.generate(mapsize + 1, 5, 0, 255);
	heightMap.generate(mapsize + 1, 60, 0.59);
	heightMap.capData(0, 255);
	heightMap.smooth(1, 2);

	//Sets heightmap values to values between 1 and -1 for rendering
	vector<GLfloat> heightdata;
	for (int y = 0; y != heightMap.getY(); y++)
	{
		for (int x = 0; x != heightMap.getX(); x++)
		{
			heightdata.push_back((GLfloat(heightMap.getElement(x,y)))/255);
		}
	}

	Mesh mesh(mapsize, 2.0f);
	mesh.genTriangleMesh(heightdata);
	mesh.genTriangleNormals();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "3D Terrain Generation", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK){ cout << "GLEW init failed"; return -1; }
	glfwSwapInterval(1);

	float size = 1.0f;
	float radx = 3.14*2;
	float rady = 3.14 * 2;
	float radz= 3.14 * 2;

	mat4 translate;
	translate.createTranslate(vec3(0, 0, -5));
	mat4 scale;
	scale.createScale(size, size, size);
	mat4 perspect;
	perspect.createPerspect(45, 16.0f / 9.0f, 0.1f, 100.0f);
	mat4 rotatex;
	rotatex.createRotation(vec3(1,0,0), 0);
	mat4 rotatey;
	rotatey.createRotation(vec3(0, 1, 0), 0);
	mat4 rotatez;
	rotatez.createRotation(vec3(0, 0, 1), 0);

	mat4 viewMatrix;
	vec3 light(0, 1, -2);

	shader shaders("shader.vertshader", "shader.fragshader");
	mesh.initVertArray();

	int width, height, initWidth, initHeight;
	glfwGetFramebufferSize(window, &initWidth, &initHeight);

	while (!glfwWindowShouldClose(window))
	{
		viewMatrix = perspect*translate*rotatex*rotatey*rotatez*scale;
		mat4 modelMatrix = translate*rotatex*rotatey*rotatez*scale;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport((-initWidth + width) / 2, (-initHeight + height) / 2, 1280, 720);

		if (GetAsyncKeyState(VK_UP))
		{
			radx += 0.02;
			rotatex.createRotation(vec3(1,0,0), radx);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			radx -= 0.02;
			rotatex.createRotation(vec3(1, 0, 0), radx);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			rady += 0.02;
			rotatey.createRotation(vec3(0, 1, 0), rady);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			rady -= 0.02;
			rotatey.createRotation(vec3(0, 1, 0), rady);
		}
		if (GetAsyncKeyState(0x41))
		{
			radz += 0.02;
			rotatez.createRotation(vec3(0, 0, 1), radz);
		}
		if (GetAsyncKeyState(0x44))
		{
			radz -= 0.02;
			rotatez.createRotation(vec3(0, 0, 1), radz);
		}
		
		//Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Z-Buffer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//Transforms triangle view
		shaders.setUniformMat4("view", viewMatrix);
		shaders.setUniformVec3("in_light", light);
		shaders.setUniformMat4("model", modelMatrix);

		//Use shader and draw triangles
		shaders.enable(); // (Runs shader program)
		mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	mesh.disableVertArrays();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
