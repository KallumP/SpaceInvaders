#pragma once
#include "Game.h"
#include <gl/glew.h>


class Ship {

public:

	Ship(int windowMiddle, int windowHeight);
	Ship();
	~Ship();

	void Move(int moveAmount);
	void Shoot();

	void Tick();
	void Draw(int width, int height);

private:

	void Setup(int _x, int _y);
	float CoordinateFixer(int screenCoordinate ,int bounds);

	int x;
	int y;
	int height;
	int width;
};

