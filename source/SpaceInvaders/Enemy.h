#pragma once

enum class EnemDirection { Left, Right };

class Enemy
{
public:
	Enemy();
	Enemy(int _x, int _y);
	~Enemy();

	bool WithinBounds(int screenWidth, int moveAmount);
	void ChangeDirection();
	void Move(int moveAmount);
	void Draw(int screenWidth, int screenHeight);

	int GetX();
	int GetY();
	int GetSize();
	

private:

	void Setup(int _x, int _y);

	EnemDirection dir;

	int x;
	int y;
	int speed;
	int size = 20;

};

