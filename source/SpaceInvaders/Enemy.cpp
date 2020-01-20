#include "Enemy.h"
#include "OGLFunctions.h"

#include <cmath>
#include <GL/glew.h>

Enemy::Enemy() {

}

Enemy::Enemy(int _x, int _y) {

	Setup(_x, _y);
}

Enemy::~Enemy() {

}

void Enemy::Setup(int _x, int _y) {

	x = _x;
	y = _y;
	dir = EnemDirection::Right;
}


bool Enemy::WithinBounds(int screenWidth, int moveAmount) {

	//checks to see if the enemy go outside the screen after the next movement
	if ((x + moveAmount) - size / 2 < -screenWidth / 2 || (x + moveAmount) + size / 2 > screenWidth / 2)

		//returns that the enemy will not be within the screen bounds
		return false;

	//returns that the enemy will remain within the screen boundss
	return true;
}

//changes the movement direction
void  Enemy::ChangeDirection() {

	//checks to see what the current direction is
	if (dir == EnemDirection::Left)

		dir = EnemDirection::Right;

	else

		dir = EnemDirection::Left;
}

void Enemy::Move(int moveAmount) {

	if (dir == EnemDirection::Right)

		x += moveAmount;

	else
		x -= moveAmount;
}

void Enemy::Draw(int screenWidth, int screenHeight) {

	float glX = OGLFunctions::CoordinateFixer(x, screenWidth);
	float glY = OGLFunctions::CoordinateFixer(y, screenHeight);
	float glSize = OGLFunctions::CoordinateFixer(size / 2, screenWidth);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex2f(glX - glSize, glY + glSize);
	glVertex2f(glX - glSize, glY - glSize);
	glVertex2f(glX + glSize, glY - glSize);

	glVertex2f(glX - glSize, glY + glSize);
	glVertex2f(glX + glSize, glY + glSize);
	glVertex2f(glX + glSize, glY - glSize);

	glEnd();
}

int Enemy::GetX() {
	return x;

}

int Enemy::GetY() {
	return y;

}

int Enemy::GetSize() {
	return size;

}
