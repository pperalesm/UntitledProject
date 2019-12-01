#include "Canvas.h"

Canvas::Canvas() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw;
	}

	_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT,
			SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (_window == NULL) {
		throw;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == NULL) {
		throw;
	}

	IMG_Init(IMG_INIT_PNG);
}

Canvas::~Canvas() {
	if (_renderer != NULL) {
		SDL_DestroyRenderer(_renderer);
	}

	if (_window != NULL) {
		SDL_DestroyWindow(_window);
	}

	IMG_Quit();

	SDL_Quit();
}

void Canvas::clear() const {
	SDL_RenderClear(_renderer);
}

void Canvas::render() const {
	SDL_RenderPresent(_renderer);
}
