#include "GameStates.hpp"
#include "Game.h"
#include "StateParser.h"
#include "AudioManager.h"

StateMenu::StateMenu()
{

}

void StateMenu::Update()
{
	for each (Button * var in entitats)
	{
		var->Update();
	}
}

void StateMenu::Render()
{
	for each (Button * var in entitats)
	{
		var->Draw();
	}
}

void StateMenu::HandleEvents()
{

}

bool StateMenu::OnEnter()
{
	SDL_SetRenderDrawColor(TheGame->GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	StateParser::ParseState("menu.xml", this->menuID, &entitats, &textures);
	callbacks.push_back(NULL);
	callbacks.push_back(
		([]() {
		if (TheGame->GetLevel() == 0) {
			TheGame->GetManager()->ChangeState(new StateTutorial());
		}
		else {
			TheGame->GetManager()->ChangeState(new StateGame());
		}
	})
		);

	callbacks.push_back(
		([]() {
		TheGame->Close();
	})
		);

	for each (Button * var in entitats)
	{
		var->SetOnClickListener(callbacks.at(var->CallbackID));
		var->params->SetXPos((float)((Tools::GetWidth() / 2) - (var->params->GetWidth() / 2)));
	}

	Audio->LoadMusic("mainmenu");
	Audio->PlayMusic("mainmenu");
	return true;
}

bool StateMenu::OnExit()
{
	callbacks.clear();
	entitats.clear();
	for each (string var in textures)
	{
		Manager->Unload(var);
	}
	textures.clear();
	return true;
}