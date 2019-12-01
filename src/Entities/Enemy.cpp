#include "Enemy.h"

void Enemy::decideMove(const int playerX, const int playerY) {
	if ((sqrt(pow((_x - playerX), 2) + pow((_y - playerY), 2)) <= _aggroRadius && _xVelocity == 0 && _yVelocity == 0) ||
			(_xVelocity == _speed && _x >= playerX) || (_xVelocity == -_speed && _x <= playerX) ||
			(_yVelocity == _speed && _y >= playerY) || (_yVelocity == -_speed && _y <= playerY) ||
			(_directionChangeCounter % CHANGE_DIRECTION_AT == 0 && (_xVelocity != 0 || _yVelocity != 0))) {
		_spriteChangeCounter = 0;
		_directionChangeCounter = 1;
		if (abs(_x - playerX) > abs(_y - playerY)) {
			_yVelocity = 0;
			if (_x - playerX > 0) {
				_xVelocity = -_speed;
				_lastDirection = LEFT;
			} else {
				_xVelocity = _speed;
				_lastDirection = RIGHT;
			}
		} else {
			_xVelocity = 0;
			if (_y - playerY > 0) {
				_yVelocity = -_speed;
				_lastDirection = UP;
			} else {
				_yVelocity = _speed;
				_lastDirection = DOWN;
			}
		}
	} else {
		_directionChangeCounter++;
	}
}

void Enemy::tryOtherDirection(const int playerX, const int playerY) {
	if (_yVelocity != 0) {
		_yVelocity = 0;
		if (_x - playerX > 10) {
			_xVelocity = -_speed;
			_lastDirection = LEFT;
		} else if (_x - playerX < -10) {
			_xVelocity = _speed;
			_lastDirection = RIGHT;
		} else {
			_xVelocity = 0;
		}
	} else {
		_xVelocity = 0;
		if (_y - playerY > 10) {
			_yVelocity = -_speed;
			_lastDirection = UP;
		} else if (_y - playerY < -10) {
			_yVelocity = _speed;
			_lastDirection = DOWN;
		} else {
			_yVelocity = 0;
		}
	}
}
