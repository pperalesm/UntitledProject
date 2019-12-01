#include "DynamicEntity.h"

const double SPEED = 0.5;

DynamicEntity::DynamicEntity(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName,
		const double speed, const int health, const int resources, const int resourceRegen) : Entity(x, y, width, height, canvas, textureName),
		_speed(speed), _xVelocity(0), _yVelocity(0), _health(health), _resources(resources), _resourceRegen(resourceRegen),_abilityPower(0),
		_spriteChangeCounter(0), _lastDirection(DOWN) {
	_clip.w = 18;
	_clip.h = 18;
	_clip.y = 9;
	_clip.x = 0;
}

void DynamicEntity::updatePosition(const Uint32 timeElapsed) {
	_x = getFutureXPosition(timeElapsed);
	_y = getFutureYPosition(timeElapsed);
}

void DynamicEntity::updateSprite() {
	if (_xVelocity == 0 && _yVelocity == 0) {
		_spriteChangeCounter = 0;
		if (_lastDirection == DOWN) {
			_clip.x = 0;
		} else if (_lastDirection == LEFT) {
			_clip.x = _clip.w*3 - 1;
		} else if (_lastDirection == UP) {
			_clip.x = _clip.w*6 - 1;
		} else if (_lastDirection == RIGHT) {
			_clip.x = _clip.w*9;
		}
	} else if (_spriteChangeCounter % CHANGE_SPRITE_AT == 0) {
		_spriteChangeCounter = 1;
		if (_yVelocity > 0) {
			if (_clip.x != _clip.w) {
				_clip.x = _clip.w;
			} else {
				_clip.x += _clip.w - 1;
			}
		} else if (_xVelocity < 0) {
			if (_clip.x != _clip.w*4 - 1) {
				_clip.x = _clip.w*4 - 1;
			} else {
				_clip.x += _clip.w - 1;
			}
		} else if (_yVelocity < 0) {
			if (_clip.x != _clip.w*7) {
				_clip.x = _clip.w*7;
			} else {
				_clip.x += _clip.w;
			}
		} else if (_xVelocity > 0) {
			if (_clip.x != _clip.w*10) {
				_clip.x = _clip.w*10;
			} else {
				_clip.x += _clip.w - 1;
			}
		}
	} else {
		_spriteChangeCounter++;
	}
}
