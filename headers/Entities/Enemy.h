#ifndef ENEMY_H_
#define ENEMY_H_

#include <math.h>

#include "DynamicEntity.h"
#include "Canvas.h"

class Enemy: public DynamicEntity {
protected:
	static const int CHANGE_DIRECTION_AT = 50;
	int _aggroRadius;
	int _directionChangeCounter;

public:
	Enemy() : DynamicEntity(), _aggroRadius(0), _directionChangeCounter(0) {}
	Enemy(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName, const double speed,
			const int health, const int resources, const int resourceRegen, const int aggroRadius) : DynamicEntity(x, y, width, height, canvas,
			textureName, speed, health, resources, resourceRegen), _aggroRadius(aggroRadius), _directionChangeCounter(0) {}
	virtual ~Enemy() = default;
	Enemy(const Enemy &other) = default;
	Enemy(Enemy &&other) = default;
	Enemy& operator=(const Enemy &other) = delete;
	Enemy& operator=(Enemy &&other) = default;

	void teleport(const int x, const int y) { _x = x; _y = y; }

	void decideMove(const int playerX, const int playerY);
	void tryOtherDirection(const int playerX, const int playerY);
};

#endif /* ENEMY_H_ */
