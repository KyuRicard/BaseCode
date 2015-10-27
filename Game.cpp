#include "Game.h"

Game * Game::joc = 0;

void Game::HandleKeys(SDL_Scancode code)
{
	switch (code) {
	case SDL_SCANCODE_ESCAPE:
		Close();
		break;
	case SDL_SCANCODE_F11:
		Fullscreen = !Fullscreen;
		if (Fullscreen)
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(window, SDL_WINDOW_BORDERLESS);
		break;
	case SDL_SCANCODE_F2:
		takeScreenshot = true;
		break;
	case SDL_SCANCODE_A:
		player->Move(-7);
		break;
	case SDL_SCANCODE_D:
		player->Move(7);
		break;
	}	
}

Game::Game()
{
	Game::window = 0;
	Game::renderer = 0;
	Game::Running = true;
	Game::takeScreenshot = false;
}


Game::~Game()
{
	entitats.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Running = NULL;
	takeScreenshot = NULL;
}

bool Game::Init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{	
	this->width = width;
	this->height = height;
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
		if (window != 0) 
			renderer = SDL_CreateRenderer(window, -1, 0);		
		if (fullscreen) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			Fullscreen = true;
		}
		else {
			Fullscreen = false;
		}
	}
	if (window == 0 || renderer == 0)
	{		
		return false;
	}	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	int initFlags = IMG_INIT_PNG;
	if (!(IMG_Init(initFlags) & initFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());		
	}
	player = new Player();
	EntityParams * params = new EntityParams("player", 0, 0, 32, 32, 3, 6);
	player->Load(params, "Actor3.png");
	entitats.push_back(player);

	TextureManager::GetInstance()->Load("player.bmp", "primitiu");
	return true;
}

bool Game::IsRunning()
{
	return Running;
}

void Game::Clear()
{	
	Game::~Game();
}

void Game::EventHandler()
{
	if ((SDL_GetTicks() / 20) % 5 != 0)
		return;
	while (SDL_PollEvent(&event)) {
		if (&event == NULL)
			return;
		switch (event.type) {
		case SDL_KEYDOWN:
			HandleKeys(event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	srand((int)time(NULL));
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	if (takeScreenshot)
	{
		takeScreenShot(width, height);
		takeScreenshot = false;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	for each (LivingEntity * var in entitats)
	{
		if (var->HaveAnimation())
			var->DrawFrame();
		else
			var->Draw();
	}
	
	SDL_RenderPresent(renderer);
}

void Game::Close()
{
	Running = false;
}
