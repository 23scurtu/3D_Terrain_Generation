#ifndef	LOADSHADERS_H
#define LOADSHADERS_H

#include <GLFW\glfw3.h>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

GLuint loadShaders(const char* vertShaderPath, const char* fragShaderPath);

#endif