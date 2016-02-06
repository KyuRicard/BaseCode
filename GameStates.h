#pragma once
#include <iostream>
#include <vector>
#include "AllEntities.hpp"
#include <SDL.h>
#include "Button.h"
#include "EventHandler.h"
#include "TileLayer.h"
#include "Level.h"

using namespace std;

class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvents() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual string GetStateID() const = 0;
};
