#include "GameStates.hpp"
#include "StateParser.h"
#include "Game.h"

StateTutorial::StateTutorial()
{

}

void StateTutorial::Update()
{
	for each (Button * var in entitats)
	{
		var->Update();
	}
}

void StateTutorial::Render()
{
	for each (Button * var in entitats)
	{
		var->Draw();
	}
}

void StateTutorial::HandleEvents()
{
	map<int, int> keys = EventHandler::GetInstance()->GetKeyEvents();
	for each (auto var in keys)
	{
		//poop
	}
}

bool StateTutorial::OnEnter()
{
	StateParser::ParseState("tutorial.xml", this->tutorialID, &entitats, &textures);

	callbacks.push_back(NULL);
	callbacks.push_back(
		([]() {
		TheGame->GetManager()->ChangeState(new StateGame());
	})
		);

	callbacks.push_back(
		([]() {
		TheGame->LevelUp();
		TheGame->GetManager()->ChangeState(new StateGame());
	})
		);

	for each (Button * var in entitats)
	{
		var->SetOnClickListener(callbacks.at(var->CallbackID));
	}
	return true;
}

bool StateTutorial::OnExit()
{
	callbacks.clear();
	entitats.clear();
	textures.clear();
	return true;
}