#ifndef VECTORS_H
#define VECTORS_H

class vec3
{
	public:
		float x, y, z;

		vec3();
		vec3(float a, float b, float c) : x(a), y(b), z(c){}

		vec3 operator + (const vec3 &first);

		void scaler();
		float mag();
		void normalize();
		vec3 cross(vec3 b);

		// ad rotate vector
};

#endif