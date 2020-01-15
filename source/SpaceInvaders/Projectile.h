#pragma once

enum class Direction { Up, Down };

class Projectile
{

public:

	Projectile();
	Projectile(int _x, int _y, Direction _dir);
	~Projectile();
	
	void Tick();
	void Move();
	void Draw(int width, int height);

private:

	void Setup(int _x, int _y, Direction _dir);

	Direction dir;

	int x;
	int y;
	int size;
};

