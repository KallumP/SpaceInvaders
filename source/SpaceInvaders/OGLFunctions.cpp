#include "OGLFunctions.h"


//changes coordinates from screen pixel coordinates to the 1 based coordinates used in opengl
float OGLFunctions::CoordinateFixer(int screenCoordinate, int bounds) {

	float ratio;

	//gets the ratio of the coordinates to the screen size
	ratio = screenCoordinate / (float)(bounds / 2);

	float fixed;

	//finds the fixed coordinate using the ratio
	fixed = (float)1 * ratio;

	return fixed;
}