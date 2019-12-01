#ifndef MAP_H_
#define MAP_H_

#include <fstream>
#include <vector>
#include <list>

#include "Texture.h"
#include "Tile.h"
#include "Player.h"
#include "Clone.h"

class Map {
private:
	SDL_Texture *_tileLayer;
	SDL_Rect _tileLayerRect;
	std::vector<std::vector<Tile>> _logicLayer;

public:
	Map() : _tileLayer(nullptr) {}
	Map(const Canvas &canvas, const std::string fileName);
	virtual ~Map() = default;
	Map(const Map &other) = delete;
	Map(Map &&other) = delete;
	Map& operator=(const Map &other) = delete;
	Map& operator=(Map &&other) = delete;

	void draw(const Canvas &canvas, const int cameraX, const int cameraY) const;
	bool checkCollisions(const DynamicEntity &entity, const Uint32 timeElapsed) const;
	void checkSpawns(const int cameraX, const int cameraY, std::list<std::unique_ptr<Enemy>> &activeEnemies);
};

#endif /* MAP_H_ */
