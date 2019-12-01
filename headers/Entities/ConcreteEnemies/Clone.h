#ifndef HEADERS_ENTITIES_CONCRETEENEMIES_CLONE_H_
#define HEADERS_ENTITIES_CONCRETEENEMIES_CLONE_H_

#include "Enemy.h"

class Clone: public Enemy {
public:
	Clone() : Enemy() {}
	Clone(const int x, const int y, const Canvas &canvas) : Enemy(x, y, Canvas::TILE_WIDTH - 5, Canvas::TILE_HEIGHT - 5, canvas, "player.png", 0.4, 100, 100, 1, 400) {}
	virtual ~Clone() = default;
	Clone(const Clone &other) = delete;
	Clone(Clone &&other) = delete;
	Clone& operator=(const Clone &other) = delete;
	Clone& operator=(Clone &&other) = delete;
};

#endif /* HEADERS_ENTITIES_CONCRETEENEMIES_CLONE_H_ */
