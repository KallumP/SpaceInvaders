#include "Ship.h"
#include "OGLFunctions.h"
#include <GL/glew.h>

Ship::Ship() {

	Setup(0, 0);
}

//constructor
Ship::Ship(int windowHeight) {

	Setup(0, -(windowHeight / 2) + 10);
}

//destructor
Ship::~Ship() {

}

void Ship::Setup(int _x, int _y) {

	x = _x;
	y = _y;

	width = 80;
	height = 40;
}

//passes time in the ship
void Ship::Tick() {

}

//lets the ship move
void Ship::Move(int moveAmount) {
	
	//adds the parameter onto the ship's x coordinate
	x += moveAmount;
}

//draws the ship
void Ship::Draw(int screenWidth, int screenHeight) {

	float glX = OGLFunctions::CoordinateFixer(x, screenWidth);
	float glY = OGLFunctions::CoordinateFixer(y, screenHeight);
	float glWidth = OGLFunctions::CoordinateFixer(width, screenWidth);
	float glHeight = OGLFunctions::CoordinateFixer(height, screenHeight);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex2f(glX, glY + glHeight);
	glVertex2f(glX - glWidth/2, glY);
	glVertex2f(glX + glWidth/2, glY);

	glEnd();
}