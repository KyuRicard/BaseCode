#include "TextureManager.h"
#include "Game.h"
#include <string>
#include <sstream>

using namespace std;

TextureManager * TextureManager::instancia = 0;

bool TextureManager::Load(const char * filename, string id)
{
	stringstream ss;
	ss << ASSETS_FOLDER << IMG_FOLDER << filename;
	string file;
	ss >> file;
	SDL_Surface * surface = IMG_Load(file.c_str());
	SDL_Texture * textura = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
	SDL_FreeSurface(surface);
	textures[id] = textura;
	if (textura == NULL) {	   
		printf("Error al carregar la textura %s.", file.c_str());
		return false;
	}
	return true;
}

bool TextureManager::Unload(std::string id)
{
	if (textures[id] == NULL)
	{
		return false;
	}
	else
	{
		SDL_DestroyTexture(textures[id]); 
		return true;
	}
}

TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	instancia = NULL;
	textures.~map();
}
