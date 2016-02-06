#pragma once

#include "GameStates.h"

class StateGame : public GameState
{
private:
	string gameID = "game";
	vector<Entity *> entitats;
	vector<string> textures;
	Player * player = NULL;
	Level * level;
	InertEntity * live1, *live2, *live3;
public:
	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	Player * GetPlayer() { return player; }
	string GetStateID() const { return gameID; }
};