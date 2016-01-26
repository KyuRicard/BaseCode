#pragma once

#include "Entity.h"
#include "Vector2D.h"
#include <tinyxml2.h>
#include "TileLayer.h"

namespace Tools
{
	void takeScreenShot(int, int);
	double GetDeltaTime();
	long GetTime();
	bool InBounding(Entity *, Entity *);
	bool InBounding(Entity *, int x0, int y0);
	int GetWidth();
	int GetHeight();
	Vector2D CalcPosFromImage(int, int);
	int Decomp(int, int, int);
	string Clear(string str);
	string GetValueFromNode(string node, tinyxml2::XMLElement * root);
	int ToCell(int, TileLayer *);
}
