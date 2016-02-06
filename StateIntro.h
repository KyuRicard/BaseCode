#pragma once

#include "GameStates.h"

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