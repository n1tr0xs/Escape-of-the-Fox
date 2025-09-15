#include "constants.hpp"
#include "MenuScene.hpp"

MenuScene::MenuScene(ResourceManager* resourceManager) :
	m_resourceManager{ resourceManager } {
	m_font = m_resourceManager->loadFont("arial.ttf");
}

MenuScene::~MenuScene() {
	//Mix_FadeOutChannel(BACKGROUND_MUSIC_CHANNEL, 1000);
}

void MenuScene::handleEvent(const SDL_Event& event) {
	int buttonsCount = static_cast<int>(m_buttons.size());
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_S:
			case SDLK_DOWN:
				m_buttons[m_selectedItem]->unSelect();
				m_selectedItem = (m_selectedItem - 1 + buttonsCount) % buttonsCount;
				m_buttons[m_selectedItem]->select();
				break;
			case SDLK_W:
			case SDLK_UP:
				m_buttons[m_selectedItem]->unSelect();
				m_selectedItem = (m_selectedItem + 1) % buttonsCount;
				m_buttons[m_selectedItem]->select();
				break;
			case SDLK_RETURN:
				m_enterPressed = true;
				break;
		}
	}
}

void MenuScene::update(const Uint64 deltaTime) {
	//if (m_backgroundMusic && !Mix_Playing(BACKGROUND_MUSIC_CHANNEL))
		//Mix_PlayChannel(BACKGROUND_MUSIC_CHANNEL, m_backgroundMusic.get(), -1);
	if (m_enterPressed) {
		m_sceneResult = m_buttons[m_selectedItem]->getResult();

		m_enterPressed = false;
	}
}

void MenuScene::render(SDL_Renderer* renderer) {
	float buttonSpacing = 0;

	float total_height = -buttonSpacing;
	for (const auto& button : m_buttons) {
		total_height += button->getHeight() + buttonSpacing;
	}
	float rendererCenterX = RENDERER_WIDTH_IN_PIXELS / 2.0;
	float rendererCenterY = RENDERER_HEIGHT_IN_PIXELS / 2.0;
	SDL_FRect dest = { 0.0f, rendererCenterY - total_height / 2.0f, 0.0f, 0.0f };
	for (const auto& button : m_buttons) {
		dest.x = rendererCenterX - button->getWidth() / 2;
		dest.w = button->getWidth();
		dest.h = button->getHeight();
		button->render(renderer, &dest);
		dest.y += button->getHeight() + buttonSpacing;
	}
}

void MenuScene::addButton(const std::string& text, SceneResult result, SDL_Color textColor, SDL_Color textSelectedColor) {
	m_buttons.push_back(std::make_unique<MenuButton>(m_font, text, result, textColor, textSelectedColor));
	m_buttons[m_selectedItem]->select();
}

void MenuScene::addMusic(const std::string& fileName) {
	//m_backgroundMusic = m_resourceManager->loadSound(fileName);
}
