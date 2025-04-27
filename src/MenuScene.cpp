#include "MenuScene.h"

#include "constants.h"
#include <string>
#include <format>

MenuScene::MenuScene(ResourceManager* resourceManager) :
	m_resourceManager(resourceManager) {
	m_resourceManager->loadFont("arial.ttf");

	m_buttons.emplace_back(std::make_unique<MenuButton>("Start game", SceneResult::StartGame));
	m_buttons.emplace_back(std::make_unique<MenuButton>("Quit", SceneResult::Quit));
}

void MenuScene::handleEvent(const SDL_Event& event) {
	int buttonsCount = m_buttons.size();
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_S:
			case SDLK_DOWN:
				m_selectedItem = (m_selectedItem - 1 + buttonsCount) % buttonsCount;
				break;
			case SDLK_W:
			case SDLK_UP:
				m_selectedItem = (m_selectedItem + 1) % buttonsCount;
				break;
			case SDLK_RETURN:
				m_enterPressed = true;
				break;
		}
	}
}

void MenuScene::update(float deltaTime) {
	if (m_enterPressed) {
		m_sceneResult = m_buttons[m_selectedItem]->getResult();
		m_enterPressed = false;
	}
}

void MenuScene::render(SDL_Renderer* renderer) {
	float buttonHeight = 100;
	float buttonSpacing = 50;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Color textSelectedColor = { 255, 255, 0 , 255 };
	TTF_Font* font = m_resourceManager->loadFont("arial.ttf");

	SDL_FRect dest = { 0, 0, 100, buttonHeight };
	for (size_t i = 0; i < m_buttons.size(); ++i) {
		m_buttons[i]->render(renderer, font, dest, m_selectedItem == i ? textSelectedColor : textColor);
		dest.y += buttonHeight + buttonSpacing;
	}
}

// MenuButton

MenuButton::MenuButton(const std::string& text, SceneResult result) :
	m_text(text), m_result(result) {}

std::string MenuButton::getText() const {
	return m_text;
}

SceneResult MenuButton::getResult() const {
	return m_result;
}

void MenuButton::render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, m_text.c_str(), m_text.length(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderTexture(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}
