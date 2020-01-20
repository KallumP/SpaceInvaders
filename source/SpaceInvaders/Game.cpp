#include <iostream>

#include "Game.h"
#include "Ship.h"

#include <sdl/SDL.h>
#include <gl/glew.h>

using namespace std;

//sends an error message to the console
void Error(string errorMessage) {

	cout << errorMessage << endl;
	cout << "Press any key to exit";

	int buffer;
	cin >> buffer;
}

//constructor
Game::Game() {

	window = nullptr;
	screenWidth = 400;
	screenHeight = 400;

	//creates the ship object
	player = Ship(screenHeight);
	SetupEnemies();

	running = true;;
}

//destructor
Game::~Game() {

}

//starts the game
void Game::Run() {
	InitSystems();
	GameLoop();
}

//sets up the window
void Game::InitSystems() {

	SDL_Init(SDL_INIT_EVERYTHING);

	//Creates an SDL window
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	//error checks the window
	if (window == nullptr)
		Error("SDL window could not be made");

	//creates an openGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	//Error checks the SDL GL context
	if (glContext == nullptr)
		Error("SDLGL context could not be made");

	GLenum check = glewInit();

	//Error checks glew
	if (check != GLEW_OK)
		Error("Could not initialize glew");

	//sets up double buffering (draws to a two screens to stop flickering)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//sets up enemies
void Game::SetupEnemies() {

	int rowCount = 4;
	int columnCount = 5;

	int verticalSpacing = 30;
	int horizontalSpacing = screenWidth / columnCount;

	//loops for each row of enemies
	for (size_t i = 1; i < rowCount + 1; i++)

		//loops for each column in the row
		for (size_t j = 0; j < columnCount; j++)

			//adds a new enemy to the vector
			enemies.push_back(Enemy(-(screenWidth / 2) + (j * horizontalSpacing) + horizontalSpacing / 2, screenHeight / 2 - i * verticalSpacing));
}

//game loop
void Game::GameLoop() {

	const int frequency = 60;
	const int period = 1000 / 60;

	Uint32 frameStartTime;

	//checks to see if the game is still running
	while (running) {

		//saves the amount of milliseconds since the start of the program
		frameStartTime = SDL_GetTicks();

		ProcessInput();
		Tick();
		Draw();

		//checks to see if this tick too less milliseconds than a frame should take
		if (period > (SDL_GetTicks() - frameStartTime))

			//delays the tick to keep a constant fps
			SDL_Delay(period - (SDL_GetTicks() - frameStartTime));
	}
}

//tick sequence
void Game::Tick() {

	//moves the ship
	MoveShip();

	//moves the projectiles
	MoveProjectiles();

	//moves the enemies
	MoveEnemies();

	//checks collision
	CheckCollision();

}

//gets inputs from the user
void Game::ProcessInput() {

	SDL_Event e;

	//checks to see if there was an event
	while (SDL_PollEvent(&e)) {

		//checks to see what sort of event
		switch (e.type) {

			//checks to see if the cross was clicked
			case SDL_QUIT:

			//sets the game state to exit
			running = false;

			break;


			//checks to see if any key was pressed down
			case SDL_KEYDOWN:

			//checks what key was pressed down
			switch (e.key.keysym.sym) {

				//checks for a left arrow press
				case SDLK_LEFT:

				leftDown = true;
				break;

				//checks for a right arrow press
				case SDLK_RIGHT:

				rightDown = true;
				break;

				//checks to see if the space bar was pressed
				case SDLK_SPACE:

				//causes the player to shoot
				Shoot();
				break;
			}
			break;

			//checks to see if any key was let go of
			case SDL_KEYUP:

			//checks what key was let go of
			switch (e.key.keysym.sym) {

				//left arrow key
				case SDLK_LEFT:

				leftDown = false;
				break;

				//right arrow key
				case SDLK_RIGHT:


				rightDown = false;
				break;
			}
		}
	}
}

//draws the game
void Game::Draw() {

	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnableClientState(GL_COLOR_ARRAY);

	//draws out the player
	player.Draw(screenWidth, screenHeight);

	//loops through each of the projectiles and ticks them
	for (size_t i = 0; i < playerProjectiles.size(); i++)

		playerProjectiles[i].Draw(screenWidth, screenHeight);

	for (size_t i = 0; i < enemies.size(); i++)

		enemies[i].Draw(screenWidth, screenHeight);


	//swaps the buffer screen
	SDL_GL_SwapWindow(window);
}

//shoots a projectile from the ship
void Game::Shoot() {

	//checks to see if therew as less than 5 projectiles
	if (playerProjectiles.size() < 400)

		//adds a projectile to the end of the list
		playerProjectiles.push_back(Projectile(player.x, player.y, ProjDirection::Up));
}

//adds a new projectile into the game
void Game::AddProjectile(int _x, int _y, ProjDirection _dir) {


}

//deals with player input to move the ship
void Game::MoveShip() {

	//variable used to determin how much to move the player by
	int moveAmount = 0;

	//checks to see if the left key was pressed
	if (leftDown)
		moveAmount -= shipSpeed;

	//checks to see if the right key was pressed
	if (rightDown)
		moveAmount += shipSpeed;

	//checks to see if the player was within the bounds and if the player should be moved
	if (player.WithinBounds(screenWidth, moveAmount) && moveAmount != 0)

		//moves the player
		player.Move(moveAmount);
}

//moves all the projectiles
void Game::MoveProjectiles() {

	//loops through each of the projectiles and ticks them
	for (size_t i = 0; i < playerProjectiles.size(); i++)

		//checks to see if the projectile can move again
		if (playerProjectiles[i].WithinBounds(screenHeight))

			//moves the projectile
			playerProjectiles[i].Move();

		else if (!playerProjectiles[i].WithinBounds(screenHeight))

			//removes the projectile
			playerProjectiles.erase(playerProjectiles.begin() + i);
}

//checks to see if the enemies direction should be changed
void Game::CheckChangeEnemyDirection() {

	bool change = false;

	//loops through all the enemies
	for (size_t i = 0; i < enemies.size(); i++)

		//checks if the current enemy is outside the screen bounds
		if (!enemies[i].WithinBounds(screenWidth, enemySpeed))

			change = true;


	if (change)

		for (size_t i = 0; i < enemies.size(); i++)

			enemies[i].ChangeDirection();
}

//moves all the enemies
void Game::MoveEnemies() {

	//tries to change direction
	CheckChangeEnemyDirection();

	//loops through the enemies
	for (size_t i = 0; i < enemies.size(); i++)

		//moves the current enemy
		enemies[i].Move(enemySpeed);
}

//checks for collisions between projectiles and enemies
void Game::CheckCollision() {

	//checks to see if there were any projectiles
	if (playerProjectiles.size() != 0) {

		//loops through all the projectiles
		for (size_t i = playerProjectiles.size() - 1; i >= 0; i--)
		{

			//checks to see if the projectile for loop went wrong
			if (i > playerProjectiles.size() - 1) {

				cout << "Projectile for loop went wrong i = " << i << endl;
				break;
			}
			else {

				//loops through all the enemies
				for (size_t j = enemies.size() - 1; j >= 0; j--)
				{

					//checks to see if the for loop went wrong
					if (j > enemies.size() - 1)
					{
						cout << "Enemy for loop went wrong j = " << j << endl;
						//breaks out of the for loop
						break;
					}
					else {

						//checks for a collision
						if (playerProjectiles[i].Collided(enemies[j].GetX(), enemies[j].GetY(), enemies[j].GetSize())) {

							//removes the collided enemy
							enemies.erase(enemies.begin() + j);

							//removes the collided projectile
							playerProjectiles.erase(playerProjectiles.begin() + i);
						}
					}
				}
			}
		}
	}
}