#pragma once
#include "TextureManager.h"
#include <iostream>
#include "EventHandler.h"
#include "Entity.h"
#include "InertEntity.h"

#define WAIT 1
#define HOVER 2
#define PRESSED 3

class Button : public Entity
{
private:
	std::string id;	
	std::string buttonID;
	int state = WAIT;
	InertEntity * text;
public:
	EntityParams * params;
	void Load(EntityParams * params);
	static Entity * Create();

	void SetOnClickListener(void(*callback)());	
	
	void Draw();	
	void DrawFrame();
	void Update();
	void Clear();

	int CallbackID;
protected:
	void(*callback)();
};
