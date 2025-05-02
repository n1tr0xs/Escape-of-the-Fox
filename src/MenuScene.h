#pragma once

#include "Scene.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class MenuButton {
public:
	MenuButton(const std::string& text, SceneResult result);

	void render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor);

	// Getters
	std::string getText() const;
	SceneResult getResult() const;
private:
	std::string m_text;
	SceneResult m_result;
};

class MenuScene : public Scene {
public:
	MenuScene(ResourceManager* resourceManager);
	void handleEvent(const SDL_Event& event) override;
	void update(Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void addButton(const std::string& text, SceneResult result);
private:
	ResourceManager* m_resourceManager;

	int m_selectedItem = 0;
	bool m_enterPressed = false;
	std::vector<std::unique_ptr<MenuButton>> m_buttons;
};