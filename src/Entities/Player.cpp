#include "Player.h"

Player::Player(const Canvas &canvas) : DynamicEntity(1500, 1000, Canvas::TILE_WIDTH - 5, Canvas::TILE_HEIGHT - 5, canvas, "player.png", 0.5, 100, 100, 1) {
	_clip.w = 18;
	_clip.h = 18;
	_clip.y = 9;
	_clip.x = 0;
}

void Player::processInputs(std::unordered_map<int, Uint32> &keysPressed) {
	Uint32 maxTime = keysPressed[SDL_SCANCODE_W];
	int recentKey = SDL_SCANCODE_W;

	if (keysPressed[SDL_SCANCODE_A] > maxTime) {
		maxTime = keysPressed[SDL_SCANCODE_A];
		recentKey = SDL_SCANCODE_A;
	}
	if (keysPressed[SDL_SCANCODE_S] > maxTime) {
		maxTime = keysPressed[SDL_SCANCODE_S];
		recentKey = SDL_SCANCODE_S;
	}
	if (keysPressed[SDL_SCANCODE_D] > maxTime) {
		maxTime = keysPressed[SDL_SCANCODE_D];
		recentKey = SDL_SCANCODE_D;
	}

	if (maxTime == 0) {
		stop();
	} else if (recentKey == SDL_SCANCODE_W && _yVelocity != -_speed) {
		_xVelocity = 0;
		_yVelocity = -_speed;
		_lastDirection = UP;
		_spriteChangeCounter = 0;
	} else if (recentKey == SDL_SCANCODE_A && _xVelocity != -_speed) {
		_xVelocity = -_speed;
		_yVelocity = 0;
		_lastDirection = LEFT;
		_spriteChangeCounter = 0;
	} else if (recentKey == SDL_SCANCODE_S && _yVelocity != _speed) {
		_xVelocity = 0;
		_yVelocity = _speed;
		_lastDirection = DOWN;
		_spriteChangeCounter = 0;
	} else if (recentKey == SDL_SCANCODE_D && _xVelocity != _speed) {
		_xVelocity = _speed;
		_yVelocity = 0;
		_lastDirection = RIGHT;
		_spriteChangeCounter = 0;
	}
}
