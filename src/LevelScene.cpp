#include "LevelScene.h"
#include <format>
#include <string>

LevelScene::LevelScene(ResourceManager* resourceManager, int levelNum) :
	m_resourceManager(resourceManager) {

	// Creating Level	
	SDL_Texture* levelTileSheetTexture = m_resourceManager->loadTexture("back.png", levelNum);
	SDL_Texture* backgroundStaticTexture = m_resourceManager->loadTexture("backgroundStatic.png", levelNum);
	SDL_Texture* backgroundBackTexture = m_resourceManager->loadTexture("backgroundBack.png", levelNum);
	SDL_Texture* backgroundFrontTexture = m_resourceManager->loadTexture("backgroundFront.png", levelNum);
	std::string tileMapPath = std::format(LEVEL_ASSET_PATH, levelNum, "tilemap.txt");
	m_level = std::make_unique<Level>(levelTileSheetTexture, backgroundStaticTexture, backgroundBackTexture, backgroundFrontTexture);
	m_level->loadFromFile(tileMapPath);
	// Creating Camera
	float cameraWidth = static_cast<float>(RENDERER_WIDTH_IN_PIXELS);
	float cameraHeight = static_cast<float>(RENDERER_HEIGHT_IN_PIXELS);
	m_camera = std::make_unique<Camera>(cameraWidth, cameraHeight);
	// Creating Player
	SDL_Texture* playerTexture = m_resourceManager->loadTexture("fox.png");
	float playerWidth = static_cast<float>(TILE_SIZE * 4);
	float playerHeight = static_cast<float>(TILE_SIZE * 2);
	m_player = std::make_unique<Player>(0.0f, 0.0f, playerWidth, playerHeight, playerTexture);

}

void LevelScene::handleEvent(const SDL_Event& event) {
	m_level->handleEvent(event);
	m_player->handleEvent(event);
}

void LevelScene::update(Uint64 deltaTime) {
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
	m_level->render(renderer, m_camera->getRect());
	m_player->render(renderer, m_camera->getRect());
}
