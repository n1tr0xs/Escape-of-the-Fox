#include "constants.h"
#include "GameCompleteScene.h"
#include <format>
#include <string>

GameCompleteScene::GameCompleteScene(ResourceManager* resourceManager) :
	m_resourceManager(resourceManager) {
	m_resourceManager->loadFont("arial.ttf");

	m_textLabels.emplace_back(std::make_unique<TextLabel>("Developer"));
}

void GameCompleteScene::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_ESCAPE:
			case SDLK_SPACE:
			case SDLK_RETURN:
				m_sceneResult = SceneResult::Quit;
				break;
		}
	}
}

void GameCompleteScene::update(Uint64 deltaTime) {}

void GameCompleteScene::render(SDL_Renderer* renderer) {
	TTF_Font* font = m_resourceManager->loadFont("arial.ttf");
	SDL_FRect dest = { 0, 0, 100, 100 };
	SDL_Color textColor = { 255, 255, 255, 255 };
	for (const auto& textLabel : m_textLabels) {
		textLabel->render(renderer, font, dest, textColor);
	}
}

TextLabel::TextLabel(const std::string& text) :
	m_text(text) {}

void TextLabel::render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, m_text.c_str(), m_text.length(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderTexture(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}
