#include "GameCompleteScene.hpp"
#include "constants.hpp"

GameCompleteScene::GameCompleteScene(ResourceManager* resourceManager) :
	m_resourceManager{ resourceManager } {

	shared_TTF_Font font = m_resourceManager->loadFont("arial.ttf");
	SDL_Color textColor = { 255, 255, 255, 255 };
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Developer: n1tr0xs", textColor));
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Graphic artist: chertowka", textColor));
	m_textLabels.push_back(std::make_unique<TextLabel>(font, "Sound artist: H4RD0ZZ", textColor));

	m_hintLabel = std::make_unique<TextLabel>(font, "Press any key to exit.", textColor);
}

void GameCompleteScene::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_ESCAPE:
			case SDLK_SPACE:
			case SDLK_RETURN:
				m_sceneResult = SceneResult::QuitToMainMenu;
				break;
		}
	}
}

void GameCompleteScene::update(const Uint64 deltaTime) {}

void GameCompleteScene::render(SDL_Renderer* renderer) {
	float verticalSpacing = 10;

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
		dest.y += textLabel->getHeight() + verticalSpacing;
	}

	dest = {
		rendererCenterX - m_hintLabel->getWidth() / 2,
		RENDERER_HEIGHT_IN_PIXELS - m_hintLabel->getHeight() - verticalSpacing,
		m_hintLabel->getWidth(),
		m_hintLabel->getHeight()
	};
	m_hintLabel->render(renderer, &dest);
}