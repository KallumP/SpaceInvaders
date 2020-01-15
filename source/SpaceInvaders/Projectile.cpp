#include "Projectile.h"


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
}



//passes time in the projectile
void Projectile::Tick() {

	Move();
}

//moves the projectile
void Projectile::Move() {

	if (dir == Direction::Up)
		y++;
}

//draws the ship
void Projectile::Draw(int width, int height) {



}



