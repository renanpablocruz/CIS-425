#include "Texture.h"

Texture::Texture()
{
	wrap = false;
	loadExternalTextures();
}

BitMapFile* Texture::getBMPData(std::string filename)
{
	BitMapFile *bmp = new BitMapFile;
	unsigned int size, offset, headerSize;

	// Read input file name.
	std::ifstream infile(filename.c_str(), std::ios::binary);

	// Get the starting point of the image data.
	infile.seekg(10);
	infile.read((char *)&offset, 4);

	// Get the header size of the bitmap.
	infile.read((char *)&headerSize, 4);

	// Get width and height values in the bitmap header.
	infile.seekg(18);
	infile.read((char *)&bmp->sizeX, 4);
	infile.read((char *)&bmp->sizeY, 4);

	// Allocate buffer for the image.
	size = bmp->sizeX * bmp->sizeY * 24;
	bmp->data = new unsigned char[size];

	// Read bitmap data.
	infile.seekg(offset);
	infile.read((char *)bmp->data, size);

	// Reverse color from bgr to rgb.
	int temp;
	for (unsigned int i = 0; i < size; i += 3)
	{
		temp = bmp->data[i];
		bmp->data[i] = bmp->data[i + 2];
		bmp->data[i + 2] = temp;
	}

	return bmp;
}

unsigned int Texture::getTexture(int pos)
{
	return textures[pos];
}

void Texture::loadExternalTextures()
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(NUM_TEXTURES, textures);

	loadSingleTexture("Textures/red.bmp", 0);
	loadSingleTexture("Textures/brown.bmp", 1);
	loadSingleTexture("Textures/blue.bmp", 2);
	loadSingleTexture("Textures/dark_ground.bmp", 3);
	loadSingleTexture("Textures/dark_sky.bmp", 4);
	loadSingleTexture("Textures/light_ground.bmp", 5);
	loadSingleTexture("Textures/light_sky.bmp", 6);
	loadSingleTexture("Textures/tank_drawing.bmp", 7);
}

void Texture::loadSingleTexture(std::string filename, int pos)
{
	BitMapFile *image;
	image = getBMPData(filename);

	glBindTexture(GL_TEXTURE_2D, textures[pos]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image->data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);
}
