#include "StateManager.h"

using namespace std;

StateManager::StateManager(GameState * state)
{	
	PushState(state);
	TextureManager::GetInstance()->Load(buttonWait.c_str(), "buttonWait");
	TextureManager::GetInstance()->Load(buttonHover.c_str(), "buttonHover");
	TextureManager::GetInstance()->Load(buttonPressed.c_str(), "buttonPressed");
}

void StateManager::PushState(GameState * state)
{
	state->OnEnter();
	gameStates.push_back(state);
}

void StateManager::ChangeState(GameState * state)
{
	state->OnEnter();
	gsDelete.push_back(gameStates.back());
	gameStates.back() = state;
}

void StateManager::PopState()
{
	gameStates.back()->OnExit();
	gsDelete.push_back(gameStates.back());
	gameStates.pop_back();
}

StateManager::~StateManager()
{
	gameStates.clear();
	gsDelete.clear();
}

void StateManager::HandleEvents()
{
	gameStates.back()->HandleEvents();
}

void StateManager::Update()
{
	gameStates.back()->Update();
}

void StateManager::Render()
{
	gameStates.back()->Render();
}