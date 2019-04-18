#pragma once

class Application;

class GameState
{
public:
	GameState();
	~GameState();

	virtual void Initialize() = 0;

	virtual void update() = 0;

	virtual void draw() = 0;

	virtual void Release() = 0;

protected:

	Application* GameMgr;
};

