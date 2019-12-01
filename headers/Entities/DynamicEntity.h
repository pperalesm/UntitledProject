#ifndef DYNAMICENTITY_H_
#define DYNAMICENTITY_H_

#include "Entity.h"

class DynamicEntity: public Entity {
protected:
	static const int CHANGE_SPRITE_AT = 25;
	static const int UP = 0;
	static const int DOWN = 1;
	static const int LEFT = 2;
	static const int RIGHT = 3;
	double _speed;
	double _xVelocity;
	double _yVelocity;
	int _health;
	int _resources;
	int _resourceRegen;
	int _abilityPower;
	SDL_Rect _clip;
	int _spriteChangeCounter;
	int _lastDirection;

public:
	DynamicEntity() : Entity(), _speed(0), _xVelocity(0), _yVelocity(0), _health(0), _resources(0), _resourceRegen(0), _abilityPower(0),
			_spriteChangeCounter(0), _lastDirection(DOWN) {}
	DynamicEntity(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName, const double speed,
			const int health, const int resources, const int resourceRegen);
	virtual ~DynamicEntity() = default;
	DynamicEntity(const DynamicEntity &other) = default;
	DynamicEntity(DynamicEntity &&other) = default;
	DynamicEntity& operator=(const DynamicEntity &other) = delete;
	DynamicEntity& operator=(DynamicEntity &&other) = default;

	int getFutureXPosition(const Uint32 timeElapsed) const { return _x + static_cast<int>(_xVelocity*timeElapsed); }
	int getFutureYPosition(const Uint32 timeElapsed) const { return _y + static_cast<int>(_yVelocity*timeElapsed); }
	void stop() { _xVelocity = 0; _yVelocity = 0; }

	void draw(const Canvas &canvas, const int cameraX, const int cameraY) const { Entity::draw(canvas, cameraX, cameraY, &_clip); }
	void updatePosition(const Uint32 timeElapsed);
	void updateSprite();
};

#endif /* DYNAMICENTITY_H_ */
