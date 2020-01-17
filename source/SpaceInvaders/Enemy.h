#pragma once

enum class EnemDirection { Left, Right };

class Enemy
{
public:
	Enemy();
	Enemy(int _x, int _y);
	~Enemy();

	bool CheckChangeDirection();
	void ChangeDirection();
	void Move();


private:

	void Setup(int _x, int _y);

	EnemDirection dir;

	int x;
	int y;
	int size;
	int speed;

};

