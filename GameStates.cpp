#include "GameStates.h"
#include "Game.h"
#include "StateParser.h"
#include "LayerParser.h"

using namespace std;

void StateGame::Update()
{
	for each (LivingEntity * var in entitats)
	{
		if ((var->GetYPos() + var->GetHeight()) < Tools::GetHeight())
		{
			var->yAccel = POSITIVE;
		}
		else
		{
			var->yAccel = NULL;
		}
		
		if (Enemy * en = dynamic_cast<Enemy *>(var)) {
			en->Update(player);
		}
		var->Update();
	}
	layer->Update(player);
	cout << "Player: " << player->position.X << " " << player->position.Y << endl;
}

void StateGame::Render()
{
	layer->Render();
	for each (LivingEntity * var in entitats)
	{
		if (var->HaveAnimation())
			var->DrawFrame();
		else
			var->Draw();
	}
}

void StateGame::HandleEvents()
{
	map<int, int> keys = EventHandler::GetInstance()->GetKeyEvents();
	for each (auto key in keys)
	{
		if (key.second == DOWN)
		{
			if (key.first == 4)
			{
				player->xAccel = NEGATIVE;
			}
			else if (key.first == 7)
			{
				player->xAccel = POSITIVE;
			}
			else if (key.first == 41)
			{
				TheGame->GetManager()->PushState(new StatePause());
			}
			else if (key.first == 44 && player->GetYPos() != Tools::GetHeight())
			{
				player->Jump();
			}
			else if (key.first == SDL_SCANCODE_LSHIFT) {
				player->yAccel = NEGATIVE;
			}
		}
		else if (key.second == UP)
		{
			if (key.first == 4 || key.first == 7)
			{
				player->xAccel = NULL;
			}
		}		
	}
}

bool StateGame::OnEnter()
{
	StateParser::ParseState("game.xml", this->gameID, &entitats, &textures);
	for each (LivingEntity * var in entitats)
	{
		if (Player * pl = dynamic_cast<Player *>(var))
		{
			player = pl;
		}
	}
	SDL_SetRenderDrawColor(TheGame->GetRenderer(), 0x00, 0x90, 0xFF, 0xFF);
	layer = Layerer->ParseTileLayer("assets/xml/state.tmx");
	return true;
}

bool StateGame::OnExit()
{
	for each (string var in textures)
	{
		Manager->Unload(var);
	}
	entitats.clear();
	textures.clear();
	SDL_SetRenderDrawColor(TheGame->GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
	return true;
}

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
	StateParser::ParseState("menu.xml", this->menuID, &entitats, &textures);
	callbacks.push_back(NULL);
	callbacks.push_back(
		([]() {
			TheGame->GetManager()->ChangeState(new StateGame());
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
	}
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

StatePause::StatePause()
{
	
}

void StatePause::Update()
{
	for each (Button * var in entitats)
	{
		var->Update();
	}
}

void StatePause::Render()
{
	for each (Button * var in entitats)
	{
		var->Draw();
	}
}

void StatePause::HandleEvents()
{
	map<int, int> keys = EventHandler::GetInstance()->GetKeyEvents();
	for each (auto var in keys)
	{
		if (var.second == DOWN)
		{
			if (var.first == 41)
			{
				TheGame->GetManager()->PopState();
			}
		}
	}
}

bool StatePause::OnEnter()
{
	StateParser::ParseState("pause.xml", this->pauseID, &entitats, &textures);

	callbacks.push_back(NULL);
	callbacks.push_back(
		([]() {
			TheGame->GetManager()->PopState();
		})
	);

	callbacks.push_back(
		([]() {
			TheGame->GetManager()->ChangeState(new StateMenu());
		})
	);

	for each (Button * var in entitats)
	{
		var->SetOnClickListener(callbacks.at(var->CallbackID));
	}
	return true;
}

bool StatePause::OnExit()
{
	callbacks.clear();
	entitats.clear();
	textures.clear();
	return true;
}

void StateIntro::Update()
{
}

void StateIntro::Render()
{
	for each (InertEntity * var in entitats)
	{
		var->Draw();
	}
	if (SDL_GetTicks() - millis > 5000)
		TheGame->GetManager()->ChangeState(new StateMenu());
}

void StateIntro::HandleEvents()
{
}

bool StateIntro::OnEnter()
{
	StateParser::ParseState("intro.xml", GetStateID(), &entitats, &textures);
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
