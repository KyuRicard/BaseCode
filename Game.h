#pragma once
#include <iostream>
#include <string>
#include "Tools.h"
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include <ctime>
#include <random>
#include "StateManager.h"

#define TheGame Game::GetInstance()

class Game
{
private:
	SDL_Window * window;
	SDL_Renderer * renderer;

	Game();

	static Game * joc;
	StateManager * manager;

	int width, height;
	bool Fullscreen;
	bool Running;
	bool takeScreenshot;
	int r, g, b, a;
	int level = 0;
public:
	double delta;
	void ToggleFullscreen();
	void TakeScreenshot() { takeScreenshot = true; }
	static Game * GetInstance() 
	{
		if (joc == 0)
		{
			joc = new Game();
		}
		return joc;
	};
	~Game();
	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool IsRunning();
	void Clear();
	void EventHandler();
	void Update();
	void Render();
	void Close();
	void GameOver();
	int GetLevel()
	{
		return level;
	}
	void SetLevel(int level)
	{
		this->level = level;
	}
	void LevelUp();

	SDL_Renderer * GetRenderer() { return this->renderer; }
	SDL_Window * GetWindow() { return this->window; }
	StateManager * GetManager() { return this->manager; }
};
