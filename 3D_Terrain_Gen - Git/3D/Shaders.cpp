#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Shaders.h"
#include "loadShaders.h"

shader::shader(const char* vertex, const char* fragment)
{
	ID = loadShaders(vertex, fragment);
}

void shader::enable()
{
	glUseProgram(ID);
}

void shader::disable()
{
	glUseProgram(0);
}

//make cache
void shader::setUniformVec3(GLchar* name, vec3 vector)
{
	glUniform3f(glGetUniformLocation(ID, name), vector.x, vector.y, vector.z);
}

void shader::setUniformMat4(GLchar* name, mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_TRUE, &matrix.elements[0]);
}