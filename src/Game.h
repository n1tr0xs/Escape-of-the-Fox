#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include <vector>

#include "ResourceManager.h"
#include "Entity.h"
#include "Player.h"
#include "Level.h"

class Game {
public:
	// Constructor
	Game(const std::string& title, int width, int height);
	// Destructor
	~Game();

	// Main game loop
	void run();

private:
	// Handles user input
	void processEvents();
	// Updates game logic
	void update(Uint64 deltaTime);
	// Renders the game
	void render();
	// Logs error and quit the program
	void SDL_Fail(const std::string& message);
	

	bool m_running = false; // Is game running ?
	SDL_Window* m_window = nullptr; // Game window
	SDL_Renderer* m_renderer = nullptr; // Game renderer
	std::unique_ptr<ResourceManager> m_resourceManager; // Resource manager

	std::unique_ptr<Level> level; // Level
	std::vector<std::unique_ptr<Entity>> m_entities; // Game entities
};