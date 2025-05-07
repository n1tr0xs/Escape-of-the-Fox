#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Scene.hpp"
#include "MenuButton.hpp"

class MenuScene : public Scene {
public:
	MenuScene(ResourceManager* resourceManager);
	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void addButton(const std::string& text, SceneResult result, SDL_Color textColor = { 255, 255, 255, 255 }, SDL_Color textSelectedColor = { 255, 255, 0 , 255 });
private:
	ResourceManager* m_resourceManager;
	TTF_Font* m_font;

	int m_selectedItem = 0;
	bool m_enterPressed = false;
	std::vector<std::unique_ptr<MenuButton>> m_buttons;
};