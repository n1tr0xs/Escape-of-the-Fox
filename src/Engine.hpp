#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
#include <string>
#include <vector>

#include "constants.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"

#include "smart_SDL.hpp"

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
	void update(const Uint64 deltaTime);
	// Renders the game
	void render();

	std::unique_ptr<Scene> createMenuScene();

	// Game window
	unique_SDL_Window m_window{ nullptr, [](SDL_Window* p) {if (p) SDL_DestroyWindow(p); p = nullptr;} };
	// Game renderer
	unique_SDL_Renderer m_renderer{ nullptr, [](SDL_Renderer* p) {if (p) SDL_DestroyRenderer(p); p = nullptr;} };
	// "virtual screen"
	unique_SDL_Texture m_renderTexture{ nullptr, [](SDL_Texture* p) {if (p) SDL_DestroyTexture(p); p = nullptr;} };
	
	std::unique_ptr<ResourceManager> m_resourceManager; // Resource manager
	std::unique_ptr<Scene> m_currentScene;
	SDL_AudioDeviceID m_audioDeviceID{ 0 }; // AudioDevice

	bool m_running{ false };
	int m_currentLevel{ 0 };
	const int m_maxLevel{ 1 };

	int m_maxFPS{ 60 };
	int m_minFrameTicks = 1000 / m_maxFPS;
};