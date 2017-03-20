#include <iostream>
#include <GL\glew.h>
#include "Utils.h"

using namespace std;

string LoadFileToString(string filepath)
{
	string fileData = "";
	ifstream stream(filepath, ifstream::in);

	if (stream.is_open())
	{
		string line = "";

		while (getline(stream, line))
		{
			fileData += "\n" + line;
		}
		stream.close();
	}
	return fileData;
}

GLuint loadBMP(const char * imagepath)
{
	unsigned char header[54];
	unsigned int dataPos; //Pos where data begins
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;

	FILE * file;
	fopen_s(&file, imagepath, "rb");//maybe not?,  FILE * file = fopen(imagepath,"rb");
	if (!file)
	{
		cout << "Image could not be opened" << endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54)
	{
		cout << "Not bmp file" << endl;
		return false;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		cout << "not bmp file correct" << endl;
		return 0;
	}
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) imageSize = width*height * 3;
	if (dataPos == 0) dataPos = 54;

	data = new unsigned char[imageSize];//CREATE BUFFER

	fread(data, 1, imageSize, file); //Read data from file to buffer
	fclose(file);

	//Create and open gl texture 
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	//Give image to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//When minimizing image use linear blend of mipmaps, each filtered linear 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//Gen mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}

// make void convertUV()