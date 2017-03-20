#ifndef SHADERS_H
#define SHADERS_H

#include "Vectors.h"
#include "Matrices.h"

class shader
{
		int ID;
	public:
		static const int VERTEX_ATTRIB = 0;
		static const int TEXTURE_ATTRIB = 1;

		shader(const char* vertex, const char* fragment);
		void enable();
		void disable();
		void setUniformVec3(GLchar* name, vec3 vector);
		void setUniformMat4(GLchar* name, mat4 matrix);
};

#endif