#include "Player.h"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) :
	Entity(x, y, width, height, texture) {
	int fw = TILE_SIZE * 4;
	int fh = TILE_SIZE * 2;
	//addAnimation("idle", 0, 4, fw, fh);
	//addAnimation("running", 1, 4, fw, fh);
	//addAnimation("jumping", 2, 4, fw, fh);
	//addAnimation("crouching", 3, 4, fw, fh);
	m_currentAnimation = m_animations["idle"].get();
}

void Player::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_A:
				m_movingLeft = true;
				break;
			case SDLK_D:
				m_movingRight = true;
				break;
			case SDLK_SPACE:
				m_jumpPressed = true;
				break;
		}
	}
	if (event.type == SDL_EVENT_KEY_UP) {
		switch (event.key.key) {
			case SDLK_A:
				m_movingLeft = false;
				break;
			case SDLK_D:
				m_movingRight = false;
				break;
			case SDLK_SPACE:
				m_jumpPressed = false;
				break;
		}
	}
}

void Player::update(Uint64 deltaTime, Level* level) {
	float speedX = 0.5f;
	float jumpStrength = .15f * TILE_SIZE;
	float gravity = 0.02f;

	if (m_jumpPressed && m_isOnGround) {
		m_velocity.y = -jumpStrength;
		m_isOnGround = false;
	}

	if (m_movingLeft) {
		m_velocity.x = -speedX;
	}

	if (m_movingRight) {
		m_velocity.x = speedX;
	}

	if (!m_isOnGround) {
		m_velocity.y += gravity * deltaTime;
	}

	resolveHorizontalCollision(deltaTime, level);
	resolveVerticalCollision(deltaTime, level);

	updateAnimationFrame(deltaTime);
}

void Player::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
	SDL_FRect rect = {
		m_rect.x - cameraRect.x,
		m_rect.y - cameraRect.y,
		m_rect.w,
		m_rect.h
	};
	//SDL_RenderTexture(renderer, m_texture, NULL, &rect);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::resolveHorizontalCollision(Uint64 deltaTime, Level* level) {
	float newX = m_rect.x + m_velocity.x * deltaTime;

	float topY = m_rect.y;
	float bottomY = topY + m_rect.h;

	float leftEdge = newX;
	float rightEdge = newX + m_rect.w;

	// Check left
	if (level->isSolidVertically(leftEdge, topY, bottomY)) {
		float tileX = std::floor(leftEdge / TILE_SIZE);
		newX = (tileX + 1) * TILE_SIZE;
	}

	// Check right
	if (level->isSolidVertically(rightEdge, topY, bottomY)) {
		float tileX = std::floor(rightEdge / TILE_SIZE);
		newX = tileX * TILE_SIZE - m_rect.w;
	}

	m_velocity.x = 0.0f;
	m_rect.x = newX;
}

void Player::resolveVerticalCollision(Uint64 deltaTime, Level* level) {
	float newY = m_rect.y + m_velocity.y * deltaTime;

	float headY = newY;
	float feetY = headY + m_rect.h;

	float leftX = m_rect.x;
	float rightX = leftX + m_rect.w;

	// Check ground
	if (level->isSolidHorizontally(feetY, leftX, rightX)) {
		float tileY = std::floor(feetY / TILE_SIZE);
		newY = tileY * TILE_SIZE - m_rect.h;
		m_isOnGround = true;
		m_velocity.y = 0.0f;
	}
	else {
		m_isOnGround = false;
	}

	// Check head
	if (level->isSolidHorizontally(headY, leftX, rightX)) {
		float tileY = std::floor(headY / TILE_SIZE);
		newY = (tileY + 1) * TILE_SIZE;
		m_velocity.y = 0.0f;
	}

	m_rect.y = newY;
}
