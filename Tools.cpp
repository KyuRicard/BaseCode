#include "Tools.h"
#include "SDL.h"
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Game.h"

using namespace std;

double lastFrame = Tools::GetTime();

void Tools::takeScreenShot(int width, int height)
{
	chrono::time_point<std::chrono::system_clock> now = chrono::system_clock::now();
	time_t time_ = chrono::system_clock::to_time_t(now);

	string str;
	str.append(to_string((int)time(&time_)));
	str.append(".png");

	cout << str << endl;

	SDL_Surface * sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(Game::GetInstance()->GetRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	IMG_SavePNG(sshot, str.c_str());
	SDL_FreeSurface(sshot);
}

double Tools::GetDeltaTime()
{
	long currentTime = Tools::GetTime();
	double delta = ((double)currentTime - lastFrame) / 1000;
	lastFrame = Tools::GetTime();
	return delta;
}

long Tools::GetTime()
{
	return SDL_GetTicks() * 1000;
}

bool Tools::InBounding(Entity * entitat, Entity * compare)
{
	int x = compare->params->GetXPos();
	int y = compare->params->GetYPos();
	int w = compare->params->GetWidth();
	int h = compare->params->GetHeight();

	return InBounding(entitat, x, y) || InBounding(entitat, (x + w), y) || InBounding(entitat, x, (y + h)) || InBounding(entitat, (x + w), (y + h));
}

bool Tools::InBounding(Entity * entitat, int x0, int y0)
{
	int x = entitat->params->GetXPos();
	int y = entitat->params->GetYPos();
	int w = entitat->params->GetWidth();
	int h = entitat->params->GetHeight();

	return (x0 > x) && (x0 < x + w) && (y0 > y) && (y0 < y + h);
}

int Tools::GetWidth()
{
	int w;
	SDL_GetWindowSize(TheGame->GetWindow(), &w, NULL);
	return w;
}

int Tools::GetHeight()
{
	int h;
	SDL_GetWindowSize(TheGame->GetWindow(), NULL, &h);
	return h;
}