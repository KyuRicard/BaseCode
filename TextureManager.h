#pragma once
#include<iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

#define NULL 0
#define Manager TextureManager::GetInstance()

class TextureManager
{
private:
	TextureManager();
	std::map<std::string, SDL_Texture *> textures;
	static TextureManager * instancia;
	const char * ASSETS_FOLDER = "assets/";
	const char * IMG_FOLDER = "img/";
public:	
	static TextureManager * GetInstance()
	{
		if (instancia == 0)
		{
			instancia = new TextureManager();
		}
		return instancia;
	}
	
	bool Load(const char* filename, std::string id);
	bool Unload(std::string);
	std::map<std::string, SDL_Texture *> GetArray() {
		return textures;
	};
	~TextureManager();
};

