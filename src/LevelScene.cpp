#include "LevelScene.hpp"

#include "BeeSwarm.hpp"
#include "Cock.hpp"

LevelScene::LevelScene(ResourceManager* resourceManager, int levelNum) :
	m_resourceManager{ resourceManager } {

	m_level = createLevel(levelNum);
	m_camera = createCamera();
	m_player = createPlayer();
	m_pauseScene = createPauseScene();
	//m_enemies.push_back(createSimpleEnemy());
	//m_enemies.push_back(createBeeSwarm());
	m_enemies.push_back(createCock());
}

void LevelScene::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_ESCAPE:
				m_isPaused = !m_isPaused;
				break;
		}
	}
	if (m_isPaused) {
		m_pauseScene->handleEvent(event);
	}
	else {
		m_player->handleEvent(event);
		for (const auto& enemy : m_enemies) {
			enemy->handleEvent(event);
		}
	}
}

void LevelScene::update(const Uint64 deltaTime) {
	if (m_isPaused) {
		m_pauseScene->update(deltaTime);
		SceneResult pauseResult = m_pauseScene->getResult();
		switch (pauseResult) {
			case SceneResult::Continue:
				m_isPaused = false;
				m_pauseScene->resetResult();
				break;
			case SceneResult::QuitToMainMenu:
				m_sceneResult = SceneResult::QuitToMainMenu;
				break;
		}
	}
	else {
		float mapWidth = m_level->getMapWidthInPixels();
		float mapHeight = m_level->getMapHeightInPixels();

		m_player->update(deltaTime);
		resolveCollision(m_player.get(), deltaTime);
		for (const auto& enemy : m_enemies) {
			enemy->update(deltaTime);
			resolveCollision(enemy.get(), deltaTime);
			resolveEnemyPlayerCollision(m_player.get(), enemy.get());
		}
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
}

void LevelScene::render(SDL_Renderer* renderer) {
	if (m_isPaused) {
		m_pauseScene->render(renderer);
	}
	else {
		m_level->render(renderer, m_camera->getRect());
		m_player->render(renderer, m_camera->getRect());
		for (const auto& enemy : m_enemies) {
			enemy->render(renderer, m_camera->getRect());
		}
	}
}

void LevelScene::resolveCollision(Entity* entity, Uint64 deltaTime) {
	resolveHorizontalCollision(entity, deltaTime);
	resolveVerticalCollision(entity, deltaTime);
}

void LevelScene::resolveHorizontalCollision(Entity* entity, Uint64 deltaTime) {
	float currentX = entity->getX();
	float velocityX = entity->getVelocityX();
	float newX = currentX + velocityX * deltaTime;

	float topY = entity->getY();
	float bottomY = topY + entity->getHeight();

	float step = 0;
	if (velocityX > 0) step = 1.0f;
	if (velocityX < 0) step = -1.0f;

	while ((step > 0 && currentX < newX) || (step < 0 && currentX > newX)) {
		currentX += step;

		float leftEdge = currentX;
		float rightEdge = currentX + entity->getWidth();

		if (step > 0) {
			// Moving right
			if (m_level->isSolidVertically(rightEdge, topY, bottomY)) {
				currentX = std::floor(rightEdge / TILE_SIZE) * TILE_SIZE - entity->getWidth();
				entity->setVelocityX(0.0f);
				break;
			}
		}
		else if (step < 0) {
			// Moving left
			if (m_level->isSolidVertically(leftEdge, topY, bottomY)) {
				currentX = (std::floor(leftEdge / TILE_SIZE) + 1) * TILE_SIZE;
				entity->setVelocityX(0.0f);
				break;
			}
		}
	}

	entity->setX(currentX);
	entity->setVelocityX(0.0f);
}


void LevelScene::resolveVerticalCollision(Entity* entity, Uint64 deltaTime) {
	float velocityY = entity->getVelocityY();
	float currentY = entity->getY();
	float newY = currentY + velocityY * deltaTime;

	float leftX = entity->getX();
	float rightX = leftX + entity->getWidth();

	float step = 0;
	if (velocityY > 0) step = 1.0f;
	if (velocityY < 0) step = -1.0f;

	bool collisionDetected = false;

	while ((step > 0 && currentY < newY) || (step < 0 && currentY > newY)) {
		currentY += step;

		float headY = currentY;
		float feetY = headY + entity->getHeight();

		if (step > 0) {
			// Falling (check ground)
			if (m_level->isSolidHorizontally(feetY, leftX, rightX)) {
				currentY = std::floor(feetY / TILE_SIZE) * TILE_SIZE - entity->getHeight();
				entity->setOnGround(true);
				entity->setVelocityY(0.0f);
				collisionDetected = true;
				break;
			}
		}
		else {
			// Jumping (check bumping)
			if (m_level->isSolidHorizontally(headY, leftX, rightX)) {
				currentY = (std::floor(headY / TILE_SIZE) + 1) * TILE_SIZE;
				entity->setVelocityY(0.0f);
				collisionDetected = true;
				break;
			}
		}
	}

	if (!collisionDetected) {
		entity->setOnGround(false);
	}

	entity->setY(currentY);
}

void LevelScene::resolveEnemyPlayerCollision(Entity* player, Entity* enemy) {
	if (utils::isCollide(player->getRect(), enemy->getRect())) {
		//m_sceneResult = SceneResult::GameOver;
	}
}

std::unique_ptr<Player> LevelScene::createPlayer() {
	shared_SDL_Texture playerTexture = m_resourceManager->loadTexture("player.png");
	float playerWidth = static_cast<float>(TILE_SIZE * 4);
	float playerHeight = static_cast<float>(TILE_SIZE * 2);
	std::unique_ptr<Player> player = std::make_unique<Player>(1300.0f, 0.0f, playerWidth, playerHeight, playerTexture);

	float fw = 512;
	float fh = fw / 2;
	player->addAnimation("idle", 0, 1, fw, fh);
	//player->addAnimation("running", 1, 4, fw, fh);
	//player->addAnimation("jumping", 2, 4, fw, fh);
	//player->addAnimation("crouching", 3, 4, fw, fh);

	return player;
}

std::unique_ptr<Entity> LevelScene::createSimpleEnemy() {
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(200.0f, 500.0f, 3.0f * TILE_SIZE, 1.0f * TILE_SIZE, nullptr);
	return enemy;
}

std::unique_ptr<Entity> LevelScene::createBeeSwarm() {
	std::unique_ptr<BeeSwarm> beeSwarm = std::make_unique<BeeSwarm>(300.0f, 200.0f, 3.0f * TILE_SIZE, 1.0f * TILE_SIZE, nullptr);
	return beeSwarm;
}

std::unique_ptr<Entity> LevelScene::createCock() {
	std::unique_ptr<Cock> cock = std::make_unique<Cock>(1800.0f, 200.0f, 3.0f * TILE_SIZE, 1.0f * TILE_SIZE, nullptr);
	return cock;
}

std::unique_ptr<PauseMenu> LevelScene::createPauseScene() {
	return std::make_unique<PauseMenu>(m_resourceManager);
}

std::unique_ptr<Level> LevelScene::createLevel(int levelNum) {
	shared_SDL_Texture levelTileSheetTexture = m_resourceManager->loadTexture("back.png", levelNum);
	shared_SDL_Texture backgroundStaticTexture = m_resourceManager->loadTexture("backgroundStatic.png", levelNum);
	shared_SDL_Texture backgroundBackTexture = m_resourceManager->loadTexture("backgroundBack.png", levelNum);
	shared_SDL_Texture backgroundFrontTexture = m_resourceManager->loadTexture("backgroundFront.png", levelNum);
	std::unique_ptr<Level> level = std::make_unique<Level>(levelNum, levelTileSheetTexture, backgroundStaticTexture, backgroundBackTexture, backgroundFrontTexture);
	return level;
}

std::unique_ptr<Camera> LevelScene::createCamera() {
	float cameraWidth = static_cast<float>(RENDERER_WIDTH_IN_PIXELS);
	float cameraHeight = static_cast<float>(RENDERER_HEIGHT_IN_PIXELS);
	std::unique_ptr<Camera> camera = std::make_unique<Camera>(cameraWidth, cameraHeight);
	return camera;
}