#include "GameCompleteScene.hpp"
#include "constants.hpp"

GameCompleteScene::GameCompleteScene(ResourceManager* resourceManager) :
	m_resourceManager{ resourceManager } {
	
	TTF_Font* font = m_resourceManager->loadFont("arial.ttf");
	SDL_Color textColor = { 255, 255, 255, 255 };
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Developer: n1tr0xs", textColor));
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Graphic artist: chertowka", textColor));
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Sound artist: H4RD0ZZ", textColor));
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

void GameCompleteScene::update(const Uint64 deltaTime) {}

void GameCompleteScene::render(SDL_Renderer* renderer) {
	float verticalSpacing = 0;

	float total_height = -verticalSpacing;
	for (const auto& textLabel : m_textLabels) {
		total_height += textLabel->getHeight() + verticalSpacing;
	}
	float rendererCenterX = RENDERER_WIDTH_IN_PIXELS / 2.0;
	float rendererCenterY = RENDERER_HEIGHT_IN_PIXELS / 2.0;
	SDL_FRect dest = { 0.0f, rendererCenterY - total_height / 2.0f, 0.0f, 0.0f };
	for (const auto& textLabel : m_textLabels) {
		dest.x = rendererCenterX - textLabel->getWidth() / 2;
		dest.w = textLabel->getWidth();
		dest.h = textLabel->getHeight();
		textLabel->render(renderer, &dest);
		SDL_Log("Text label rendered at: %f %f", dest.x, dest.y);
		SDL_Log("Size: %f %f.", dest.w, dest.h);
		dest.y += textLabel->getHeight() + verticalSpacing;
	}
}