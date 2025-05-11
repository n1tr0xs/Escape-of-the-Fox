#pragma once

#include <memory>

#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "TextLabel.hpp"

class GameCompleteScene : public Scene {
public:
	GameCompleteScene(ResourceManager* resourceManager);

	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;
private:
	ResourceManager* m_resourceManager;
	std::vector<std::unique_ptr<TextLabel>> m_textLabels;
	std::unique_ptr<TextLabel> m_hintLabel;
};