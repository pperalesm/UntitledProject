#include "Map.h"

Map::Map(const Canvas &canvas, const std::string fileName) {
	int nRows;
	int nCols;
	int auxInt;
	std::vector<Tile> auxVector;
	std::ifstream mapFile;
	std::unordered_map<int, Texture> idToTexture;
	std::unordered_map<int, const char*> idToFile;
	SDL_Rect auxRect;

	mapFile.open(fileName);

	if (mapFile.is_open()) {
		mapFile >> nRows;
		mapFile >> nCols;

		idToFile[1] = "rock.png";
		idToFile[2] = "grass.png";

		auxRect.w = Canvas::TILE_WIDTH;
		auxRect.h = Canvas::TILE_HEIGHT;
		_tileLayerRect.w = nCols*Canvas::TILE_WIDTH;
		_tileLayerRect.h = nRows*Canvas::TILE_HEIGHT;

		_tileLayer = SDL_CreateTexture(canvas.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _tileLayerRect.w, _tileLayerRect.h);
		SDL_SetRenderTarget(canvas.getRenderer(), _tileLayer);
		SDL_RenderClear(canvas.getRenderer());

		for (int row = 0; row < nRows; row++) {
			for (int col = 0; col < nCols; col++) {
				mapFile >> auxInt;

				if (idToTexture.find(auxInt) == idToTexture.end()) {
					idToTexture[auxInt] = Texture(canvas, idToFile[auxInt]);
				}

				auxRect.x = col*Canvas::TILE_WIDTH;
				auxRect.y = row*Canvas::TILE_HEIGHT;

				idToTexture[auxInt].draw(canvas, auxRect);
			}
		}

		SDL_SetRenderTarget(canvas.getRenderer(), nullptr);

		_tileLayerRect.w = Canvas::CANVAS_WIDTH;
		_tileLayerRect.h = Canvas::CANVAS_HEIGHT;
		_tileLayerRect.x = 0;
		_tileLayerRect.y = 0;

		for (int row = 0; row < nRows; row++) {
			for (int col = 0; col < nCols; col++) {
				mapFile >> auxInt;
				if (auxInt) {
					auxVector.push_back(Tile(true));
				} else {
					auxVector.push_back(Tile(false));
				}
			}
			_logicLayer.push_back(auxVector);
			auxVector.clear();
		}

		for (int row = 0; row < nRows; row++) {
			for (int col = 0; col < nCols; col++) {
				mapFile >> auxInt;
				if (auxInt) {
					_logicLayer[row][col].initEnemy(auxInt, col*Canvas::TILE_WIDTH, row*Canvas::TILE_HEIGHT, canvas);
				}
			}
		}

		mapFile.close();
	} else {
		throw;
	}
}

void Map::draw(const Canvas &canvas, const int cameraX, const int cameraY) const {
	SDL_Rect cameraRect;

	cameraRect.w = Canvas::CANVAS_WIDTH;
	cameraRect.h = Canvas::CANVAS_HEIGHT;
	cameraRect.x = cameraX - cameraRect.w/2;
	cameraRect.y = cameraY - cameraRect.h/2;

	SDL_RenderCopy(canvas.getRenderer(), _tileLayer, &cameraRect, &_tileLayerRect);
}

bool Map::checkCollisions(const DynamicEntity &entity, const Uint32 timeElapsed) const {
	int x = entity.getFutureXPosition(timeElapsed);
	int y = entity.getFutureYPosition(timeElapsed);

	if (_logicLayer[(y + entity.getHeight()/2)/Canvas::TILE_HEIGHT][(x + entity.getWidth()/2)/Canvas::TILE_WIDTH].isFree() &&
			_logicLayer[(y + entity.getHeight()/2)/Canvas::TILE_HEIGHT][(x - entity.getWidth()/2)/Canvas::TILE_WIDTH].isFree() &&
			_logicLayer[(y - entity.getHeight()/2)/Canvas::TILE_HEIGHT][(x + entity.getWidth()/2)/Canvas::TILE_WIDTH].isFree() &&
			_logicLayer[(y - entity.getHeight()/2)/Canvas::TILE_HEIGHT][(x - entity.getWidth()/2)/Canvas::TILE_WIDTH].isFree()) {
		return true;
	}

	return false;
}

void Map::checkSpawns(const int cameraX, const int cameraY, std::list<std::unique_ptr<Enemy>> &activeEnemies) {
	int verticalSight = ((Canvas::CANVAS_HEIGHT/Canvas::TILE_HEIGHT)/2 + 2);
	int horizontalSight = ((Canvas::CANVAS_WIDTH/Canvas::TILE_WIDTH)/2 + 2);

	int firstRow;
	int lastRow;
	if (cameraY/Canvas::TILE_HEIGHT - verticalSight < 0) {
		firstRow = 0;
	} else {
		firstRow = cameraY/Canvas::TILE_HEIGHT - verticalSight;
	}
	if (cameraY/Canvas::TILE_HEIGHT + verticalSight > static_cast<int>(_logicLayer.size())) {
		lastRow = _logicLayer.size();
	} else {
		lastRow = cameraY/Canvas::TILE_HEIGHT + verticalSight;
	}

	int firstCol;
	int lastCol;
	if (cameraX/Canvas::TILE_WIDTH - horizontalSight < 0) {
		firstCol = 0;
	} else {
		firstCol = cameraX/Canvas::TILE_WIDTH - horizontalSight;
	}
	if (cameraX/Canvas::TILE_WIDTH + horizontalSight > static_cast<int>(_logicLayer[0].size())) {
		lastCol = _logicLayer.size();
	} else {
		lastCol = cameraX/Canvas::TILE_WIDTH + horizontalSight;
	}

	for (int row = firstRow; row < lastRow; row++) {
		for (int col = firstCol; col < lastCol; col++) {
			if (_logicLayer[row][col].isSpawnTime()) {
				activeEnemies.push_back(_logicLayer[row][col].spawn(col*Canvas::TILE_WIDTH + Canvas::TILE_WIDTH/2, row*Canvas::TILE_HEIGHT + Canvas::TILE_HEIGHT/2));
			}
		}
	}
}
