#pragma once
#include "GameStates.h"

class StateWin : public GameState
{
private:
	string StateID = "win";
	vector<Entity *> entitats;
	vector<string> textures;
	vector<void(*)()> callbacks;
public:
	StateWin() {}

	void Update();
	void Render();
	void HandleEvents();

	bool OnEnter();
	bool OnExit();

	string GetStateID() const
	{
		return StateID;
	}
};