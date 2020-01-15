#pragma once
#include "Ship.h"
#include "Projectile.h"

#include <iostream>
#include <vector>
#include <sdl/SDL.h>
#include <gl/glew.h>

enum class GameState { PLAY, EXIT };

class Game {

public:
	Game();
	~Game();

	void Run();
	void AddProjectile(int _x, int _y, Direction _dir);


private:
	void InitSystems();
	void GameLoop();
	void Tick();
	void ProcessInput();
	void Draw();

	void Shoot();

	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	GameState gameState;

	Ship player;
	std::vector<Projectile> playerProjectiles;
};

