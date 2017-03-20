#include <GL\glew.h>
#include "loadShaders.h"
#include "Utils.h"
#include <vector>

using namespace std;

GLuint loadShaders(const char* vertShaderPath, const char* fragShaderPath){

	GLint Result = GL_FALSE;
	int InfoLogLength;
	
	//create shaders
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertShaderSource = LoadFileToString(vertShaderPath);
	string fragShaderSource = LoadFileToString(fragShaderPath);

	// compile shaders
	const char* rawVertShaderSource = vertShaderSource.c_str();
	const char* rawFragShaderSource = fragShaderSource.c_str();
	glShaderSource(vertShader, 1, &rawVertShaderSource, NULL);
	glShaderSource(fragShader, 1, &rawFragShaderSource, NULL);
	glCompileShader(vertShader);
	glCompileShader(fragShader);

		//error check shaders
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			vector<char> fragShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(fragShader, InfoLogLength, NULL, &fragShaderErrorMessage[0]);
			printf("%s\n", &fragShaderErrorMessage[0]);

		}
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			vector<char> vertShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(vertShader, InfoLogLength, NULL, &vertShaderErrorMessage[0]);
			printf("%s\n", &vertShaderErrorMessage[0]);

		}

	//link program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
 	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> programErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);

	}


	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);


	return program;
}