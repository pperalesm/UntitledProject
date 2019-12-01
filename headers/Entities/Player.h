#ifndef PLAYER_H_
#define PLAYER_H_

#include <unordered_map>

#include "DynamicEntity.h"

class Player: public DynamicEntity {
private:
	//items
	//gems

public:
	Player() : DynamicEntity() {}
	Player(const Canvas &canvas);
	virtual ~Player() = default;
	Player(const Player &other) = delete;
	Player(Player &&other) = delete;
	Player& operator=(const Player &other) = delete;
	Player& operator=(Player &&other) = delete;

	void draw(const Canvas &canvas) const { DynamicEntity::draw(canvas, _x, _y); }

	void processInputs(std::unordered_map<int, Uint32> &keysPressed);
};

#endif /* PLAYER_H_ */
