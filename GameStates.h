#pragma once
#include <iostream>
#include <vector>
#include "AllEntities.hpp"
#include <SDL.h>
#include "Button.h"
#include "EventHandler.h"
#include "TileLayer.h"
#include "Level.h"

using namespace std;

class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual string GetStateID() const = 0;
};

class StateIntro : public GameState
{
private:
	string introID = "intro";
	vector<string> textures;
	vector<Entity *> entitats;
	int millis;
public:
	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const { return introID; }
};

class StateGame : public GameState
{
private:
	string gameID = "game";
	vector<Entity *> entitats;
	vector<string> textures;
	Player * player = NULL;	
	Level * level;
	InertEntity * live1, * live2, * live3;
public:
	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	Player * GetPlayer() { return player; }
	string GetStateID() const { return gameID; }
};

class StateMenu : public GameState
{
private:
	string menuID = "menu";
	vector<Entity *> entitats;
	vector<string> textures;
	vector<void(*)()> callbacks;
public:
	StateMenu();

	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const
	{
		return menuID;
	}
};

class StatePause : public GameState
{
private:
	string pauseID = "pause";
	vector<Entity *> entitats;
	vector<string> textures;
	vector<void(*)()> callbacks;
public:
	StatePause();

	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const
	{
		return pauseID;
	}
};

class StateTutorial : public GameState
{
private:
	string tutorialID = "tutorial";
	vector<Entity *> entitats;
	vector<string> textures;
	vector<void(*)()> callbacks;
public:
	StateTutorial();

	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const
	{
		return tutorialID;
	}
};
