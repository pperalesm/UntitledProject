#include <Tile.h>

void Tile::initEnemy(const int enemyId, const int x, const int y, const Canvas &canvas) {
	if (enemyId == 1) {
		_enemy = Clone(x, y, canvas);
		_lastSpawn = SDL_GetTicks();
	}
}

std::unique_ptr<Enemy> Tile::spawn(const int x, const int y) {
	_enemy.teleport(x, y);
	_enemyAlive = true;
	return std::make_unique<Enemy>(_enemy);
}

bool Tile::isSpawnTime() const {
	if (_enemyAlive || _lastSpawn == 0) {
		return false;
	}

	return true;
}
