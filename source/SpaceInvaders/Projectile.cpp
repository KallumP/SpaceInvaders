#include "Projectile.h"
#include "OGLFunctions.h"

#include <cmath>
#include <GL/glew.h>

Projectile::Projectile() {

}

Projectile::Projectile(int _x, int _y, ProjDirection _dir) {

	Setup(_x, _y, _dir);
}

Projectile::~Projectile() {


}

void Projectile::Setup(int _x, int _y, ProjDirection _dir) {
	x = _x;
	y = _y;
	dir = _dir;
	size = 10;
	speed = 2;
}

//returns whether the projectile will be within the screen bounds after the movement
bool Projectile::WithinBounds(int screenHeight) {

	//checks to see if the next movement would cause the projectile to leave the screen
	if (y + speed - size / 2 > screenHeight / 2)

		//returns that the projectile will be outside the screen bounds after the next movement
		return false;

	//returns that the projectile will be within the screen bounds after the next movement
	return true;
}

//moves the projectile
void Projectile::Move() {

	//checks which direction to move the projectile in before moving it
	if (dir == ProjDirection::Up)
		y += speed;
	else if (dir == ProjDirection::Down)
		y -= speed;
}

//draws the projectile
void Projectile::Draw(int screenWidth, int screenHeight) {

	float glX = OGLFunctions::CoordinateFixer(x, screenWidth);
	float glY = OGLFunctions::CoordinateFixer(y, screenHeight);
	float glSize = OGLFunctions::CoordinateFixer(size, screenWidth);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex2f(glX - glSize, glY + glSize);
	glVertex2f(glX - glSize, glY - glSize);
	glVertex2f(glX + glSize, glY - glSize);

	glVertex2f(glX - glSize, glY + glSize);
	glVertex2f(glX + glSize, glY + glSize);
	glVertex2f(glX + glSize, glY - glSize);

	glEnd();


	//used to draw the circular projectile
	//int sides = 10;
	//glBegin(GL_POLYGON);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//float baseAngle = (2 * 3.14159265f)/sides;

	//for (int i = 0; i < sides; i++) {
	//	float angle = baseAngle * i;
	//	float glX = OGLFunctions::CoordinateFixer(size / 2 * cos(baseAngle), screenWidth);
	//	float glY = OGLFunctions::CoordinateFixer(size / 2 * sin(baseAngle), screenHeight);
	//	glVertex2f(glX, glY);
	//}
}
