#ifndef TEXTURE_H
#define TEXTURE_H

#include "Canvas.h"

class Texture {
private:
	SDL_Texture *_texture;

public:
	Texture() : _texture(nullptr) {}
	Texture(const Canvas &canvas, const char *fileName);
	virtual ~Texture() = default;
	Texture(const Texture &other) = delete;
	Texture(Texture &&other) = delete;
	Texture& operator=(const Texture &other) = delete;
	Texture& operator=(Texture &&other);

	void draw(const Canvas &canvas, SDL_Rect &rect) const;
};

#endif /* TEXTURE_H_ */
