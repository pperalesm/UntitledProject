#include "Entity.h"

Entity::Entity(const int x, const int y, const int width, const int height, const Canvas &canvas, const char *textureName) : _x(x), _y(y),
		_width(width), _height(height) {
	_texture = IMG_LoadTexture(canvas.getRenderer(), textureName);
}

void Entity::draw(const Canvas &canvas, const int cameraX, const int cameraY, const SDL_Rect *clip) const {
	SDL_Rect canvasRect;

	canvasRect.w = _width;
	canvasRect.h = _height;
	canvasRect.x = _x - cameraX - _width/2 + Canvas::CANVAS_WIDTH/2;
	canvasRect.y = _y - cameraY - _height/2 + Canvas::CANVAS_HEIGHT/2;

	SDL_RenderCopy(canvas.getRenderer(), _texture, clip, &canvasRect);
}
