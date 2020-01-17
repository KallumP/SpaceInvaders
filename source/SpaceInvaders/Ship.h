#pragma once
#include <gl/glew.h>


class Ship {

public:

	Ship(int windowHeight);
	Ship();
	~Ship();

	bool WithinBounds(int screenWidth, int moveAmount);
	void Move(int moveAmount);
	void Draw(int width, int height);

	int x;
	int y;

private:

	void Setup(int _x, int _y);

	int height;
	int width;
};

