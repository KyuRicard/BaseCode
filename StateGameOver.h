#pragma once
#include "GameStates.h"

class StateGameOver : public GameState
{
private:
	string stateID = "GameOver";
	vector<string> textures;
	vector<Entity *> entitats;
	vector<void(*)()> callbacks;
public:
	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const { return stateID; }
};

