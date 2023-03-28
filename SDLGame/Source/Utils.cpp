/*
This file contains functions which can be used for simple file I/O and functions which apply to many different uses.
*/

#include "Utils.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int Utils::LoadSprite(const char *file, SDL_Renderer *renderer, SDL_Point* dimensions, SDL_Texture** sprite)
{
	SDL_Surface *temp;

	// Load the sprite image
	temp = SDL_LoadBMP(file);
	if (temp == NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
		return (-1);
	}

	dimensions->x = temp->w;
	dimensions->y = temp->h;

	// Set transparent pixel as the pixel at (0,0)
	if (temp->format->palette)
	{
		SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *)temp->pixels);
	}
	else
	{
		switch (temp->format->BitsPerPixel)
		{
		case 15:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint16 *)temp->pixels) & 0x00007FFF);
			break;
		case 16:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *)temp->pixels);
			break;
		case 24:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint32 *)temp->pixels) & 0x00FFFFFF);
			break;
		case 32:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *)temp->pixels);
			break;
		}
	}

	// Create textures from the image
	*sprite = SDL_CreateTextureFromSurface(renderer, temp);
	if (!sprite) 
	{
		fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
		SDL_FreeSurface(temp);
		return (-1);
	}

	SDL_FreeSurface(temp);

	return (0);
}

// Original Code taken from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
// slight alterations have been made to compartmentalize the code and clean it up
unsigned char * Utils::loadBMP(const char * imagepath, unsigned int &width, unsigned int &height)
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-byte header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	FILE *file;
	// Open the file
	fopen_s(&file, imagepath, "rb"); // rb stands for read binary
	if (!file)
	{
		printf("Image could not be opened\n");
		return 0;
	}

	if (fread(header, 1, 54, file) != 54)
	{ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M') // the first 2 letters of the header are BM for Bit Map
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
	{
		imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	}

	if (dataPos == 0)
	{
		dataPos = 54; // The BMP header is done that way
	}

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	return data;
}