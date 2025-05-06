#pragma once

#include <memory>

#include "ResourceManager.hpp"
#include "Scene.hpp"


class TextLabel {
public:
	TextLabel(const std::string& text);

	void render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor);
	// Getters
	std::string getText() const { return m_text; };
private:
	std::string m_text;
};

class GameCompleteScene : public Scene {
public:
	GameCompleteScene(ResourceManager* resourceManager);

	void handleEvent(const SDL_Event& event) override;
	void update(Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;
private:
	ResourceManager* m_resourceManager;
	std::vector<std::unique_ptr<TextLabel>> m_textLabels;
};