#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include <vector>

#include "constants.h"
#include "ResourceManager.h"
#include "Scene.h"
//#include "Entity.h"
//#include "Player.h"
//#include "Level.h"
//#include "Camera.h"

class Game {
public:
	// Constructor
	Game(const std::string& title);
	// Destructor
	~Game();

	// Main game loop
	void run();

private:
	// Process events and user input
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
	SDL_Texture* m_renderTexture; // "virtual screen"
	std::unique_ptr<ResourceManager> m_resourceManager; // Resource manager

	std::unique_ptr<Scene> m_currentScene;
	//std::unique_ptr<Level> m_level; // Level
	//std::unique_ptr<Camera> m_camera; // Camera
	//std::vector<std::unique_ptr<Entity>> m_entities; // Game entities
};