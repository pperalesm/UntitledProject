#ifndef ALLY_H_
#define ALLY_H_

#include <string>

#include "Entity.h"

class Ally: public Entity {
protected:
	std::string message;
	//interaction
	//itemsToSell

public:
	Ally() : Entity() {}
	Ally(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName) : Entity(x, y, width, height, canvas, textureName) {}
	virtual ~Ally() = default;
	Ally(const Ally &other) = delete;
	Ally(Ally &&other) = delete;
	Ally& operator=(const Ally &other) = delete;
	Ally& operator=(Ally &&other) = delete;
};

#endif /* ALLY_H_ */
