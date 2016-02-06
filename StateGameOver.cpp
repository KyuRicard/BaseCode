#include "GameStates.hpp"
#include "StateParser.h"
#include "Game.h"
#include "AudioManager.h"

void StateGameOver::Update() {
	for each (Entity * item in entitats) {
		item->Update();
	}
}

void StateGameOver::Render() {
	for each (Entity * item in entitats) {
		item->Draw();
	}
}

void StateGameOver::HandleEvents() {
	
}

bool StateGameOver::OnEnter() {
	StateParser::ParseState("go.xml", GetStateID(), &entitats, &textures);
	callbacks.push_back(NULL);
	callbacks.push_back(([]() {
		TheGame->GetManager()->ChangeState(new StateMenu());
	}));
	for each (Entity * var in entitats)
	{
		if (Button * btn = dynamic_cast<Button *>(var)) {
			btn->SetOnClickListener(callbacks.at(btn->CallbackID));
			btn->params->SetXPos((float)((Tools::GetWidth() / 2) - (btn->params->GetWidth() / 2)));
		}
		
	}
	entitats[0]->params->SetWidth(Tools::GetWidth());
	entitats[0]->params->SetHeight(Tools::GetHeight());
	return true;
}

bool StateGameOver::OnExit() {
	for each (string var in textures)
	{
		Manager->Unload(var);
	}
	entitats.clear();
	textures.clear();
	return true;
}