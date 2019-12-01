#ifndef CANVAS_H_
#define CANVAS_H_

#include <SDL.h>
#include <SDL_image.h>

class Canvas {
public:
	static const int CANVAS_WIDTH = 1920;
	static const int CANVAS_HEIGHT = 1080;
	static const int TILE_WIDTH = 80;
	static const int TILE_HEIGHT = 80;

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;

public:
	Canvas();
	virtual ~Canvas();
	Canvas(const Canvas &other) = delete;
	Canvas(Canvas &&other) = delete;
	Canvas& operator=(const Canvas &other) = delete;
	Canvas& operator=(Canvas &&other) = delete;

	SDL_Renderer *getRenderer() const { return _renderer; }
	bool processEvents() const;
	void clear() const;
	void render() const;
};

#endif /* CANVAS_H_ */
