#ifndef TILE_H_
#define TILE_H_

#include <SDL.h>
#include <memory>

#include "Clone.h"

class Tile {
private:
	static const Uint32 SPAWN_AT = 25;
	bool _free;
	Uint32 _lastSpawn;
	Enemy _enemy;
	bool _enemyAlive;

public:
	Tile() : _free(true), _lastSpawn(0), _enemyAlive(false) {}
	Tile(const bool isFree) : _free(isFree), _lastSpawn(0), _enemyAlive(false) {}
	virtual ~Tile() = default;
	Tile(const Tile &other) = default;
	Tile(Tile &&other) = default;
	Tile& operator=(const Tile &other) = delete;
	Tile& operator=(Tile &&other) = delete;

	bool isEnemyAlive() { return _enemyAlive; }
	bool isFree() const { return _free; }
	void setCollision(const bool isFree) { _free = isFree; }

	void initEnemy(const int enemyId, const int x, const int y, const Canvas &canvas);
	std::unique_ptr<Enemy> spawn(const int x, const int y);
	bool isSpawnTime() const;
};

#endif /* TILE_H_ */
