#pragma once
#include "Ship.h"
#include "Projectile.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <sdl/SDL.h>
#include <gl/glew.h>

class Game {

public:
	Game();
	~Game();

	void Run();

private:
	void InitSystems();
	void GameLoop();
	void Tick();
	void ProcessInput();
	void Draw();

	void Shoot();
	void AddProjectile(int _x, int _y, ProjDirection _dir);
	void MoveShip();
	void MoveProjectiles();
	void ChangeEnemyDirection();


	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	bool running;

	Ship player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Enemy> enemies;

	bool leftDown;
	bool rightDown;
};

