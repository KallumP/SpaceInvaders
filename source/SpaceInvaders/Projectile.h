#pragma once

enum class ProjDirection { Up, Down };

class Projectile
{

public:

	Projectile();
	Projectile(int _x, int _y, ProjDirection _dir);
	~Projectile();

	bool WithinBounds(int screenHeight);
	void Move();
	void Draw(int width, int height);
	bool Collided(int _x, int _y, int _size);

private:

	void Setup(int _x, int _y, ProjDirection _dir);

	ProjDirection dir;
	int speed;

	int x;
	int y;
	int size;
};

