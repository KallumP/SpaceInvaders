#include "Projectile.h"
#include "OGLFunctions.h"

#include <cmath>
#include <GL/glew.h>

Projectile::Projectile() {

}

Projectile::Projectile(int _x, int _y, Direction _dir) {

	Setup(_x, _y, _dir);
}

Projectile::~Projectile() {


}

void Projectile::Setup(int _x, int _y, Direction _dir) {
	x = _x;
	y = _y;
	dir = _dir;
	size = 10;
}

//passes time in the projectile
void Projectile::Tick() {

	Move();
}

//moves the projectile
void Projectile::Move() {

	if (dir == Direction::Up)
		y++;
	else if (dir == Direction::Down)
		y--;
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
