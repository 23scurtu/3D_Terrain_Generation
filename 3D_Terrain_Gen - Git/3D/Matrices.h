#ifndef MATRICES_H
#define MATRICES_H

#include "Vectors.h"

class mat4
{
	public:
		static const int size = 4 * 4;
		float elements[size];

		mat4();

		mat4 operator * (const mat4 &first);

		void createIdentity();
		void clear();
		void createPerspect(float FoV, float aspect, float n, float f);
		void createTranslate(vec3 vector);
		void createScale(float x, float y, float z);
		void createRotation(vec3 axis, float rad);
		void display();
};

#endif