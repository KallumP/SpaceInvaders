#include "Ship.h"
#include "Game.h"

#include <GL/glew.h>

Ship::Ship() {

	Setup(0, 0);
}

//constructor
Ship::Ship(int windowMiddle, int windowHeight) {

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

//shoots a projectile from the ship
void Ship::Shoot() {

}

//draws the ship
void Ship::Draw(int screenWidth, int screenHeight) {

	float glX = CoordinateFixer(x, screenWidth);
	float glY = CoordinateFixer(y, screenHeight);
	float glWidth = CoordinateFixer(width, screenWidth);
	float glHeight = CoordinateFixer(height, screenHeight);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex2f(glX, glY + glHeight);
	glVertex2f(glX - glWidth/2, glY);
	glVertex2f(glX + glWidth/2, glY);

	glEnd();
}

//changes coordinates from screen pixel coordinates to the 1 based coordinates used in opengl
float Ship::CoordinateFixer(int screenCoordinate, int bounds) {

	float ratio;

	//gets the ratio of the coordinates to the screen size
	ratio = screenCoordinate / (float)(bounds / 2);
	
	float fixed;

	//finds the fixed coordinate using the ratio
	fixed = (float)1 * ratio;
	
	return fixed;
}
