#include "Matrices.h"
#include <iostream>

// optmize for repition
using namespace std;

mat4::mat4()
{
	fill(elements, elements + 16, 0);
}

void mat4::createIdentity()
{
	elements[0] = 1.0f;
	elements[5] = 1.0f;
	elements[10] = 1.0f;
	elements[15] = 1.0f;
}
void mat4::clear()
{
	fill(elements, elements + 16, 0);
}

void mat4::createPerspect(float FoV, float aspect, float n, float f)
{
	elements[0] = 1 / tan(FoV / 2);
	elements[5] = aspect / tan(FoV / 2);
	elements[10] = (n + f) / (n - f);
	elements[11] = 2 * n*f / (n - f);
	elements[14] = -1.0f;

}

void mat4::createTranslate(vec3 vector)
{
	createIdentity();
	elements[3] = vector.x;
	elements[7] = vector.y;
	elements[11] = vector.z;
}

void mat4::createScale(float x, float y, float z)
{
	elements[0] = x;
	elements[5] = y;
	elements[10] = z;
	elements[15] = 1.0f;
}

void mat4::createRotation(vec3 axis, float rad)
{
	axis.normalize();

	float cosine = cos(rad);
	float sine = sin(rad);

	elements[0] = cosine + pow(axis.x, 2)*(1-cosine);
	elements[1] = axis.x*axis.y*(1 - cosine) - axis.z*sine;
	elements[2] = axis.x*axis.z*(1 - cosine) + axis.y*sine;
	elements[4] = axis.y*axis.x*(1 - cosine) + axis.z*sine;
	elements[5] = cosine + pow(axis.y, 2)*(1 - cosine);
	elements[6] = axis.z*axis.y*(1 - cosine) - axis.x*sine;
	elements[8] = axis.x*axis.z*(1 - cosine) - axis.y*sine;
	elements[9] = axis.z*axis.y*(1 - cosine) + axis.x*sine;
	elements[10] = cosine + pow(axis.z, 2)*(1 - cosine);
	elements[15] = 1.0f;
}
void mat4::display()
{
	for (int a = 0; a != 4; a++)
	{
		for (int b = 0; b != 4; b++)
		{
			cout << elements[a * 4 + b];
		}
		cout << endl;
	}
}

mat4 mat4::operator * (const mat4 &first)
{
	mat4 temp;
	float sum = 0.0f;

	for (int x = 0; x != 4; x++)
	{
		for (int y = 0; y != 4; y++)
		{
			for (int e = 0; e != 4; e++)
			{
				sum += elements[y * 4 + e] * first.elements[x + 4 * e];

			}
			temp.elements[x + y * 4] = sum;
			sum = 0.0f;
		}
			
	}
		
	return temp;
}