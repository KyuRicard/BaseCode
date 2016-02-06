#include "GameStates.hpp"
#include "Game.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "Camera.h"
#include "AudioManager.h"
#include "CollisionManager.h"

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
		CheckCollision(var, entitats);
		var->Update();
	}
	level->Update();
	if (player->invulnerable == 0)
	{
		switch (player->lives)
		{
		case 3:
			live1->texture = "live";
			live2->texture = "live";
			live3->texture = "live";
			break;
		case 2:
			live1->texture = "death";
			live2->texture = "live";
			live3->texture = "live";
			break;
		case 1:
			live1->texture = "death";
			live2->texture = "death";
			live3->texture = "live";
			break;
		case 0:
			live1->texture = "death";
			live2->texture = "death";
			live3->texture = "death";
			break;
		}
	}
	else {
		switch (player->lives)
		{
		case 3:
			live1->texture = "glowing";
			live2->texture = "glowing";
			live3->texture = "glowing";
			break;
		case 2:
			live1->texture = "death";
			live2->texture = "glowing";
			live3->texture = "glowing";
			break;
		case 1:
			live1->texture = "death";
			live2->texture = "death";
			live3->texture = "glowing";
			break;
		case 0:
			live1->texture = "death";
			live2->texture = "death";
			live3->texture = "death";
			break;
		}
	}
}

void StateGame::Render()
{
	level->Render();
	for each (LivingEntity * var in entitats)
	{
		var->DrawFrame();
	}
	live1->Draw();
	live2->Draw();
	live3->Draw();
}

void StateGame::HandleEvents()
{
	map<int, int> keys = EventHandler::GetInstance()->GetKeyEvents();
	for each (auto key in keys)
	{
		if (key.second == DOWN)
		{
			if (key.first == SDL_SCANCODE_A)
			{
				player->xAccel = NEGATIVE;
			}
			else if (key.first == SDL_SCANCODE_D)
			{
				player->xAccel = POSITIVE;
			}
			else if (key.first == SDL_SCANCODE_ESCAPE)
			{
				TheGame->GetManager()->PushState(new StatePause());
			}
			else if (key.first == SDL_SCANCODE_W && player->GetYPos() != Tools::GetHeight())
			{
				player->Jump();
			}
			else if (key.first == SDL_SCANCODE_LSHIFT) {
				player->yAccel = NEGATIVE;
			}
			else if (key.first == SDL_SCANCODE_F2) {
				TheGame->TakeScreenshot();
			}
			else if (key.first == SDL_SCANCODE_F11) {
				TheGame->ToggleFullscreen();
			}
			else if (key.first == SDL_SCANCODE_S) {
				player->unStuck();
			}
			else if (key.first == SDL_SCANCODE_PERIOD) {
				TheGame->LevelUp();
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
	Audio->LoadMusic("game");
	Audio->PlayMusic("game");
	Audio->LoadSound("jump");
	Audio->LoadSound("damage");
	Audio->SetVolume(16);

	stringstream ss;
	ss << "assets/xml/state" << TheGame->GetLevel() << ".tmx";
	string route;
	ss >> route;
	level = LevelParser::ParseLevel(route);
	
	SDL_SetRenderDrawColor(TheGame->GetRenderer(), 0x00, 0x90, 0xFF, 0xFF);
	
	for each (Layer * layer in *level->getLayers()) {
		if (ObjectLayer * objLayer = dynamic_cast<ObjectLayer *>(layer)) {
			this->entitats = *objLayer->getEntities();
		}
	}
	for each (LivingEntity * entity in entitats) {
		if (Player * pl = dynamic_cast<Player *>(entity)) {
			player = pl;
		}
		vector<TileLayer *> * colLayers = level->getCollidableTileLayers();
		entity->LoadCollisionLayers(colLayers);
	}
	TheCam->SetTarget(player);
	TheCam->SetMaxPosition(level->getCollidableTileLayers()->at(0)->width * 32);
	TheCam->SetPosition(Vector2D::NULL_VECTOR);

	Manager->Load("hearth.png", "live");
	Manager->Load("antihearth.png", "death");
	Manager->Load("glowing.png", "glowing");
	
	live1 = new InertEntity();
	live1->Load(new EntityParams("live1", Tools::GetWidth() - (int)(32 * 3.2), 15, 32, 32));
	live1->texture = "live";

	live2 = new InertEntity();
	live2->Load(new EntityParams("live2", Tools::GetWidth() - (int)(32 * 2.1), 15, 32, 32));
	live2->texture = "live";

	live3 = new InertEntity();
	live3->Load(new EntityParams("live3", Tools::GetWidth() - 32, 15, 32, 32));
	live3->texture = "live";

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
	level->~Level();
	
	return true;
}








