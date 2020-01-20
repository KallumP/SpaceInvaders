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
	void SetupEnemies();
	void GameLoop();
	void Tick();
	void ProcessInput();
	void Draw();


	void Shoot();
	void AddProjectile(int _x, int _y, ProjDirection _dir);
	void MoveShip();
	void MoveProjectiles();
	void CheckChangeEnemyDirection();
	void MoveEnemies();
	void CheckCollision();


	SDL_Window* window;
	int screenWidth;
	int screenHeight;
	bool running;

	Ship player;
	std::vector<Projectile> playerProjectiles;
	std::vector<Enemy> enemies;

	int shipSpeed = 5;
	bool leftDown;
	bool aDown;
	bool rightDown;
	bool dDown;
	bool spaceDown;

	int enemySpeed = 1;

	int fireRateCap = 200;
	Uint32 reloadTime;
};

