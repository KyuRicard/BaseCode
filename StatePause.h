#pragma once

#include "GameStates.h"

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