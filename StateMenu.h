#pragma once

#include "GameStates.h"

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