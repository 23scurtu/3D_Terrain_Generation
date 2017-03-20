#include "Vectors.h"
#include <math.h>

vec3::vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void vec3::scaler()
{
	x *= 1.0f;
	y *= 1.0f;
	z *= 1.0f;
}

float vec3::mag()
{
	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return mag;
}

void vec3::normalize()
{
	float mag = this->mag();
	x /= mag;
	y /= mag;
	z /= mag;
}

/*vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}*/

vec3 vec3::cross(vec3 b)
{
	return vec3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
}

vec3 vec3::operator + (const vec3 &first)
{
	return vec3(x + first.x, y + first.y, z + first.z);
}