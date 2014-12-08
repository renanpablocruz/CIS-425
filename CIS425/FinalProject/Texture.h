#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <cstdlib>
#include <fstream>
#include "glutInclude.h"

#define NUM_TEXTURES 10
enum typesOfTextures{ RED_CAMOUFLAGE, BROWN_CAMOUFLAGE, BLUE_CAMOUFLAGE, DARK_GROUND, DARK_SKY, LIGHT_GROUND, LIGHT_SKY, TANK_DRAWING, LOGO };

struct BitMapFile // Struct of bitmap file.
{
	int sizeX;
	int sizeY;
	unsigned char *data;
};

class Texture
{
private:
	unsigned int textures[NUM_TEXTURES];
	bool wrap;
	
public:
	Texture();
	BitMapFile *getBMPData(std::string filename);
	unsigned int getTexture(int pos);
	void loadExternalTextures();
	void loadSingleTexture(std::string filename, int pos);
};

#endif