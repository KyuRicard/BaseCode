#pragma once

#include "GameStates.h"

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