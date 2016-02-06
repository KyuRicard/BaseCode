#include "GameStates.hpp"
#include "Game.h"
#include "StateParser.h"

void StateIntro::Update()
{
}

void StateIntro::Render()
{
	for each (InertEntity * var in entitats)
	{
		var->Draw();
	}
	if (SDL_GetTicks() - millis > 1500)
		TheGame->GetManager()->ChangeState(new StateMenu());
}

void StateIntro::HandleEvents()
{
}

bool StateIntro::OnEnter()
{
	StateParser::ParseState("intro.xml", GetStateID(), &entitats, &textures);
	entitats[0]->params->SetWidth(Tools::GetWidth());
	entitats[0]->params->SetHeight(Tools::GetHeight());
	entitats[0]->texture = entitats[0]->params->GetId();
	millis = SDL_GetTicks();
	return true;
}

bool StateIntro::OnExit()
{
	for each (string var in textures)
	{
		Manager->Unload(var);
	}
	entitats.clear();
	textures.clear();
	return true;
}