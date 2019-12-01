#ifndef GAME_H_
#define GAME_H_

#include "Canvas.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Ally.h"
#include "Clone.h"

class Game {
private:
	Canvas _canvas;
	Player _player;
	Map _map;
	std::unordered_map<int, Uint32> _keysPressed;
	std::list<std::unique_ptr<Enemy>> _activeEnemies;

public:
	Game();
	virtual ~Game() = default;
	Game(const Game &other) = delete;
	Game(Game &&other) = delete;
	Game& operator=(const Game &other) = delete;
	Game& operator=(Game &&other) = delete;

	bool processEvents();
	void run();
};

#endif /* GAME_H_ */
