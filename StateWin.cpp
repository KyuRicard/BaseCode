#include "GameStates.hpp"
#include "StateParser.h"
#include "Game.h"
#include "AudioManager.h"

void StateWin::Update() {
	for each (Entity * item in entitats) {
		item->Update();
	}
}

void StateWin::Render() {
	for each (Entity * item in entitats) {
		item->Draw();
	}
}

void StateWin::HandleEvents() {

}

bool StateWin::OnEnter() {
	Audio->LoadMusic("victory");
	Audio->PlayMusic("victory");
	TheGame->SetLevel(1);

	StateParser::ParseState("win.xml", GetStateID(), &entitats, &textures);
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

bool StateWin::OnExit() {
	for each (string var in textures)
	{
		Manager->Unload(var);
	}
	entitats.clear();
	textures.clear();
	return true;
}