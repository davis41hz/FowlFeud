#include "Renderer.h"
#include "GameInstance.h"
#include <iostream>
#include <fstream>
using namespace std;
GameInstance::GameInstance(int players, int gameType) {
	this->numPlayers=players;
	this->gameMode = gameType;
	this->hordeCount = 0;
	this->status = true;
	this->playersDead = 0;
	this->isVictorious = false;
	this->currentLevel = -1;
	this->controller = NULL;
	this->controller2 = NULL;
}


GameInstance::~GameInstance() {
    SDL_DestroyWindow(window);
	Mix_FreeMusic(backgroundMusic);
	SDL_GameControllerClose(controller);
	SDL_GameControllerClose(controller2);

	// clean up any remaining gameobjects in the map
    for(GameObject* gameObject : GameObject::getGameObjects()) {
		delete gameObject->clean();
    }
}

int GameInstance::startGame() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        status = false;
        return -1;
    }
	status = true;

	AudioSystem::getInstance(); // initialize the audio system

    window = SDL_CreateWindow(this->gameName, 0, 0, this->dimension, this->dimension, 0);
    renderer = Renderer::getInstance(window).getRenderer();
    SDL_SetRenderDrawColor(renderer, 60, 150, 0, 255); // set renderer to green to draw grassy background

    buildLevel();

	backgroundMusic = Mix_LoadMUS(backgroundMusicFile.c_str());
	AudioSystem::getInstance().playMusic(backgroundMusic, -1);

	// manage controller input
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (!SDL_IsGameController(i)) { continue; }

		if((controller && numPlayers == 1) || (controller && controller2 && numPlayers == 2)) {
			break;
		}

		if (!controller) {
			this->controller = SDL_GameControllerOpen(i);
        } else if(!controller2) {
			this->controller2 = SDL_GameControllerOpen(i);
		}
    }
    return 0;
}

void GameInstance::updateGameObjects() {
	bool enemiesAlive = false;

    for(GameObject* gameObject : GameObject::getGameObjects()) { // update every existing gameobject
        gameObject->updateObject();
        if(!gameObject->getExistence()) { // remove gameobject that don't exist anymore
            if(gameObject->getTag() == "player") {
                playersDead++;
                if(playersDead == numPlayers) { // end game if all players die
					status = false;
					return;
				}
            }
            delete gameObject->clean();

        } else if(gameObject->getTag() == "enemy") {
			enemiesAlive = true;
		}
    }


	if(!enemiesAlive) {
		if (this->gameMode == 2){ // if you're playing horde mode.

			this->hordeCount = this->hordeCount + 1;
			// do a for loop on the horde count and make more enemies based on how many hordes have been survived.
			int b = 0;

			for (int a = 0; a < hordeCount; a = a + 1){ // put some enemies in there.
				new EnemyGameObject(0+b, 0+b, 100, 1, 15, 850, "textures/enemySprite.bmp", this->player);
				if (numPlayers == 2){
					new EnemyGameObject(dimension-32-b, dimension-32-b, 100, 1, 15, 850, "textures/enemySprite.bmp", this->player2);
				}
				b = b + 120;
			}
		}

		if (this->gameMode ==1){ // if you want to play regular mode
			nextLevel();
		}

	}
}

void GameInstance::renderGameObjects() {
    SDL_RenderClear(renderer);
    for(GameObject* gameObject : GameObject::getGameObjects()) { // render all the gameobjects
        gameObject->renderGraphics();
    }
    SDL_RenderPresent(renderer);
}

bool GameInstance::handleInput() {
    SDL_Event eventFrame;
    while(SDL_PollEvent(&eventFrame)) {
        if(eventFrame.type == SDL_QUIT) { // player closes window
            status = false;
			return false;
        } else if((eventFrame.type == SDL_KEYDOWN || eventFrame.type == SDL_KEYUP || eventFrame.type == SDL_CONTROLLERBUTTONUP || eventFrame.type == SDL_CONTROLLERBUTTONDOWN || eventFrame.type == SDL_CONTROLLERAXISMOTION) && numPlayers==1 && status) {// || eventFrame.type == SDL_CONTROLLERBUTTONUP || eventFrame.type == SDL_CONTROLLERBUTTONDOWN
            player->handleInput(eventFrame);
        }
        else if((eventFrame.type == SDL_KEYDOWN || eventFrame.type == SDL_KEYUP || eventFrame.type == SDL_CONTROLLERBUTTONUP || eventFrame.type == SDL_CONTROLLERBUTTONDOWN || eventFrame.type == SDL_CONTROLLERAXISMOTION) && numPlayers==2 && status){
			if(player->getHealth() != NULL) { //ensures player is alive
				player->handleInput(eventFrame);
			}
			if(player2->getHealth() != NULL) { // ensures player is alive
				player2->handleInput(eventFrame);
			}
        }

    }
	return true;
}

bool GameInstance::buildLevel() {
	playersDead = 0;
	currentLevel++;
	char code;
	std::ifstream levelFile;

	// open the relevant file
	if(numPlayers == 1) {
		if(currentLevel > onePlayerLevels.size()) { return false; }
		levelFile.open(onePlayerLevels[currentLevel]);
	} else if(numPlayers == 2) {
		if(currentLevel > twoPlayerLevels.size()) { return false; }
		levelFile.open(twoPlayerLevels[currentLevel]);
	}

	// players must be spawned first as a reference to them must be passed to enemies
	for(int j = 0; j < dimension; j += 32) { // find players first for enemy reference
		for(int k = 0; k < dimension; k += 32) {
			levelFile.get(code);
			if(code == '\n') {
				levelFile.get(code);
			}
			switch (code) {
				case 'p':
					player = new PlayerGameObject(k ,j ,100, 2, 600, "textures/playerSprite.bmp", 40, SDLK_a, SDLK_d,SDLK_w, SDLK_s, SDLK_SPACE, 0 ,0, 0);
					break;
				case 's':
					player2 = new PlayerGameObject(k, j,100, 2, 600, "textures/player2Sprite.bmp", 40, SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_RSHIFT, 700, 0, 1);
					break;
				default:
					break;
			}
		}
	}

	levelFile.seekg(0); // return to file start

	// add in all non-player gameobjects
	for(int l = 0; l < dimension; l += 32) {
		for(int m = 0; m < dimension; m += 32) {
			levelFile.get(code);
			if(code == '\n') {
				levelFile.get(code);
			}
			switch (code) {
				case 'x':
					new WallGameObject(m,l);
					break;
				case 'e':
					new EnemyGameObject(m, l, 100, 1, 15, 850, "textures/enemySprite.bmp", player);
					break;
				case 'f':
					new EnemyGameObject(m, l, 100, 1, 15, 850, "textures/enemySprite.bmp", player2);
					break;
				case 'b':
					new EnemyGameObject(m, l, 300, 1, 20, 600, "textures/boss.bmp", player);
					break;
				default:
					break;
			}
		}

		// add in walls surrounding play area to restrict player to the window
		new WallGameObject(l,-32);
        new WallGameObject(-32, l);
        new WallGameObject(dimension, l);
        new WallGameObject(l, dimension);
	}

	levelFile.close();
	return true;
}

void GameInstance::nextLevel() {
	// clean up the remenants of the last level
	for(GameObject* gameObject : GameObject::getGameObjects()) {
		delete gameObject->clean();
    }

	// build a new level
	if(!buildLevel()) { // if there are no more levels to build, the player has won
		isVictorious = true;
		status = false;
	}
}



void GameInstance::displayEndScreen() {
	AudioSystem::getInstance().fadeOutMusic(100);
	SDL_RenderClear(renderer);

    if(isVictorious) {
		AudioSystem::getInstance().playSoundEffect(winSound, 0);
	    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(WINSCREEN)), NULL, NULL);
	} else {
		AudioSystem::getInstance().playSoundEffect(loseSound, 0);
		SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(LOSESCREEN)), NULL, NULL);
	}
    SDL_RenderPresent(renderer);

}

bool GameInstance::getStatus() { return status; }
