#include "LevelScene.h"
#include <string>
#include <format>

LevelScene::LevelScene(ResourceManager* resourceManager, int levelNum) :
	m_resourceManager(resourceManager) {

	// Creating Level
	SDL_Texture* levelTexture = m_resourceManager->loadTexture("assets/back.png");
	m_level = std::make_unique<Level>(levelTexture);
	std::string filePath = std::format("assets/level_{:02d}/tilemap.txt", levelNum);
	m_level->loadFromFile(filePath);
	// Creating Camera
	m_camera = std::make_unique<Camera>(RENDERER_WIDTH_IN_PIXELS, RENDERER_HEIGHT_IN_PIXELS);
	// Creating Player
	SDL_Texture* texture = m_resourceManager->loadTexture("assets/fox.png");
	m_player = std::make_unique<Player>(0, 0, TILE_SIZE * 4, TILE_SIZE * 2, texture);

}

void LevelScene::handleEvent(const SDL_Event& event) {
	m_level->handleEvent(event);
	m_player->handleEvent(event);
}

void LevelScene::update(float deltaTime) {
	float mapWidth = m_level->getMapWidthInPixels();
	float mapHeight = m_level->getMapHeightInPixels();

	m_level->update(deltaTime);
	m_player->update(deltaTime, m_level.get());
	// Updating camera position
	SDL_FRect cameraTarget = m_player->getRect();
	m_camera->follow(cameraTarget, mapWidth, mapHeight);
	// Is player dead ?
	float playerBottom = m_player->getRect().y + m_player->getRect().h;
	if (playerBottom > mapHeight) {
		m_playerDead = true;
		m_sceneResult = SceneResult::GameOver;
	}
	// Is level completed ?
	float rightPlayerEdge = m_player->getRect().x + m_player->getRect().w;
	if (rightPlayerEdge >= mapWidth) {
		m_levelCompleted = true;
		m_sceneResult = SceneResult::Victory;
	}
}

void LevelScene::render(SDL_Renderer* renderer) {
	m_level->render(renderer, m_camera.get());
	m_player->render(renderer, m_camera.get());
}
