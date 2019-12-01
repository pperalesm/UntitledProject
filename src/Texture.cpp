#include "Texture.h"

Texture::Texture(const Canvas &canvas, const char *fileName) {
	_texture = IMG_LoadTexture(canvas.getRenderer(), fileName);
}

Texture& Texture::operator=(Texture &&other) {

	_texture = other._texture;

	return *this;
}


void Texture::draw(const Canvas &canvas, SDL_Rect &rect) const {
	SDL_RenderCopy(canvas.getRenderer(), _texture, NULL, &rect);
}
