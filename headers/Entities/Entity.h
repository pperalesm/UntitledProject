#ifndef ENTITY_H_
#define ENTITY_H_

#include "Canvas.h"

class Entity {
protected:
	int _x;
	int _y;
	int _width;
	int _height;
	SDL_Texture *_texture;

public:
	Entity() : _x(0), _y(0), _width(0), _height(0), _texture(nullptr) {}
	Entity(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName);
	virtual ~Entity() = default;
	Entity(const Entity &other) = default;
	Entity(Entity &&other) = default;
	Entity& operator=(const Entity &other) = delete;
	Entity& operator=(Entity &&other) = default;

	int getX() const { return _x; }
	int getY() const { return _y; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

	virtual void draw(const Canvas &canvas, const int cameraX, const int cameraY, const SDL_Rect *clip = nullptr) const;
};

#endif /* ENTITY_H_ */
