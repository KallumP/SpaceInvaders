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
	player = Ship(screenWidth / 2, screenHeight);


	gameState = GameState::PLAY;
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

//game loop
void Game::GameLoop() {

	//checks to see if the game is still running
	while (gameState == GameState::PLAY) {

		ProcessInput();
		Draw();
	}
}

//tick sequence
void Game::Tick() {

	//ticks the player
	player.Tick();
	
	//loops through each of the projectiles and ticks them
	for (size_t i = 0; i < playerProjectiles.size(); i++)

		playerProjectiles[i].Tick();
}

//gets inputs from the user
void Game::ProcessInput() {

	SDL_Event e;

	//checks to see if there was an event
	while (SDL_PollEvent(&e)) {

		switch (e.type) {

			//checks to see if the cross was clicked
			case SDL_QUIT:

			//sets the game state to exit
			gameState = GameState::EXIT;

			break;

			//checks to see if any key was pressed down
			case SDL_KEYDOWN:

			//checks what key was pressed
			switch (e.key.keysym.sym) {

				//checks for a left arrow press
				case SDLK_LEFT:

				//moves the player to the leftwards
				player.Move(-5);
				break;

				//checks for a right arrow press
				case SDLK_RIGHT:

				//moves the player righwards
				player.Move(5);
				break;

				//checks to see if the space bar was pressed
				case SDLK_SPACE:

				//causes the player to shoot
				player.Shoot();
				break;
			}
			break;
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


	//swaps the buffer screen
	SDL_GL_SwapWindow(window);
}

//adds a new projectile into the game
void Game::AddProjectile(int _x, int _y, Direction _dir){


}
