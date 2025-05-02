#pragma once

#include "constants.h"
#include "ResourceManager.h"
#include "Scene.h"
#include <memory>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Engine {
public:
	Engine(const std::string& title);
	~Engine();

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

	std::unique_ptr<Scene> createMenuScene();

	SDL_Window* m_window = nullptr; // Game window
	SDL_Renderer* m_renderer = nullptr; // Game renderer
	SDL_Texture* m_renderTexture = nullptr; // "virtual screen"
	std::unique_ptr<ResourceManager> m_resourceManager; // Resource manager
	std::unique_ptr<Scene> m_currentScene;

	bool m_running = false; // Is game running ?
	int m_currentLevel = 0;
	const int m_maxLevel = 2;
};