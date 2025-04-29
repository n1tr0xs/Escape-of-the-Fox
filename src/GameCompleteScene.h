#pragma once

#include "Scene.h"
#include "ResourceManager.h"

#include <memory>

class TextLabel {
public:
	TextLabel(const std::string& text);
	void render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor);
	std::string getText() const;
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