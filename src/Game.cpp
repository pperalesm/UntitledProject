#include "Game.h"
#include <iostream>
Game::Game() : _canvas(), _player(_canvas), _map(_canvas, "mapTest.txt") {
		_keysPressed[SDL_SCANCODE_W] = 0;
		_keysPressed[SDL_SCANCODE_A] = 0;
		_keysPressed[SDL_SCANCODE_S] = 0;
		_keysPressed[SDL_SCANCODE_D] = 0;
	}

bool Game::processEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		} else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return false;
			} else if (_keysPressed[event.key.keysym.scancode] == 0) {
				_keysPressed[event.key.keysym.scancode] = SDL_GetTicks();
			}
		} else if (event.type == SDL_KEYUP) {
			_keysPressed[event.key.keysym.scancode] = 0;
		}
	}

	return true;
}

void Game::run() {
	Uint32 lastTick = SDL_GetTicks();
	Uint32 timeElapsed;

	//Clone enemy(2500, 1500, _canvas);
	Ally ally(2000, 1200, Canvas::TILE_WIDTH, Canvas::TILE_HEIGHT, _canvas, "toni.png");

	while (processEvents()) {
		_canvas.clear();

		_map.draw(_canvas, _player.getX(), _player.getY());
		_map.checkSpawns(_player.getX(), _player.getY(), _activeEnemies);

		timeElapsed = SDL_GetTicks() - lastTick;
		lastTick = SDL_GetTicks();

		for (auto it = _activeEnemies.begin(); it != _activeEnemies.end(); it++) {
			(*it)->decideMove(_player.getX(), _player.getY());
			if (_map.checkCollisions(**it, timeElapsed)) {
				(*it)->updatePosition(timeElapsed);
			} else {
				(*it)->tryOtherDirection(_player.getX(), _player.getY());
			}
			(*it)->updateSprite();
			(*it)->draw(_canvas, _player.getX(), _player.getY());
		}

		ally.draw(_canvas, _player.getX(), _player.getY());

		_player.processInputs(_keysPressed);
		if (_map.checkCollisions(_player, timeElapsed)) {
			_player.updatePosition(timeElapsed);
		} else {
			_player.stop();
		}
		_player.updateSprite();
		_player.draw(_canvas);

		_canvas.render();
	}
}
