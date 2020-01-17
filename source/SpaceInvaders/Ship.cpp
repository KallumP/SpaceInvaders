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
	glVertex2f(glX - glWidth / 2, glY);
	glVertex2f(glX + glWidth / 2, glY);

	glEnd();
}

//returns whether the ship will go outside the screen's bounds after the movement
bool Ship::WithinBounds(int screenWidth, int moveAmount) {

	//keeps track of what x will be after the movement
	int nextX = x + moveAmount;

	//checks to see if the player was outside the screen 
	if ((nextX - width / 2) < -screenWidth / 2 || (nextX + width / 2) > screenWidth / 2)
		
		//returns that the ship will not be within the screen bounds after the movement
		return false;

	//returns that the ship will be within the screen bounds after the movement
	return true;
}
