#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Scene.hpp"
#include "MenuButton.hpp"

class MenuScene : public Scene {
public:
	MenuScene(ResourceManager* resourceManager);
	~MenuScene();
	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	// Adds button to Menu
	void addButton(const std::string& text, SceneResult result, SDL_Color textColor = { 255, 255, 255, 255 }, SDL_Color textSelectedColor = { 255, 255, 0 , 255 });
	// Adds background music
	void addMusic(const std::string& fileName);
private:
	ResourceManager* m_resourceManager{ nullptr };
	TTF_Font* m_font{ nullptr };
	Mix_Chunk* m_backgroundMusic{ nullptr };

	int m_selectedItem{ 0 };
	bool m_enterPressed{ false };
	std::vector<std::unique_ptr<MenuButton>> m_buttons;
};