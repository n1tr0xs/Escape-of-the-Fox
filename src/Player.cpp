#include "Player.h"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) :
	Entity(x, y, width, height, texture) {
	int fw = TILE_SIZE * 4;
	int fh = TILE_SIZE * 2;
	//addAnimation("idle", 0, 4, fw, fh);
	//addAnimation("running", 1, 4, fw, fh);
	//addAnimation("jumping", 2, 4, fw, fh);
	//addAnimation("crouching", 3, 4, fw, fh);
	m_currentAnimation = m_animations["idle"];
}

void Player::update(Uint64 deltaTime, Level* level) {
	float speedX = 0.5f;
	float jumpStrength = .15f * TILE_SIZE;
	float gravity = 0.02f;
	float floor = 13 * TILE_SIZE;

	const bool* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_SPACE] && m_isOnGround) {
		vy = -jumpStrength;
		m_isOnGround = false;
	}

	if (keyState[SDL_SCANCODE_A]) {
		vx = -speedX * deltaTime;
	}

	if (keyState[SDL_SCANCODE_D]) {
		vx = speedX * deltaTime;
	}
	
	// Horizontal collision
	float newX = m_rect.x + vx * deltaTime;
	float topY = m_rect.y;
	float bottomY = m_rect.y + m_rect.height-1;
	float stepY = 8.0f;
	bool hitWall = false;

	if (vx > 0) {
		float rightEdge = newX + m_rect.width;
		for (float y = topY; y <= bottomY; y += stepY) {
			if (level->isSolidAtPixel(rightEdge, y)) {
				hitWall = true;
				break;
			}
		}
		if (hitWall) {
			float tileX = std::floor(rightEdge / TILE_SIZE);
			newX = tileX * TILE_SIZE - m_rect.width;
		}
	}
	else if (vx < 0) {
		float leftEdge = newX;
		for (float y = topY; y <= bottomY; y += stepY) {
			if (level->isSolidAtPixel(leftEdge, y)) {
				hitWall = true;
				break;
			}
		}
		if (hitWall) {
			float tileX = std::floor(leftEdge / TILE_SIZE);
			newX = (tileX + 1) * TILE_SIZE;
		}
	}
	
	vx = 0.0f;
	m_rect.x = newX;

	if (!m_isOnGround) {
		vy += gravity * deltaTime;
	}

	float newY = m_rect.y + vy * deltaTime;
	float feetY = newY + m_rect.height;

	// Sample bottom width of player to check how many points are solid
	const int sampleSpacing = 8; // every 8px across width
	const int totalSamples = m_rect.width / sampleSpacing;
	const int requiredSolidSamples = 6; // 48px = 1.5 tiles

	int solidSamples = 0;
	for (int i = 0; i < totalSamples; ++i) {
		float sampleX = m_rect.x + i * sampleSpacing;
		if (level->isSolidAtPixel(sampleX, feetY)) {
			++solidSamples;
		}
	}

	bool isTouchingGround = solidSamples >= requiredSolidSamples;

	if (isTouchingGround) {
		float alignedFeet = std::floor((feetY) / TILE_SIZE) * TILE_SIZE;
		newY = alignedFeet - m_rect.height;

		vy = 0.0f;
		m_isOnGround = true;
	}
	else {
		m_isOnGround = false;
	}
	m_rect.y = newY;


	updateAnimationFrame(deltaTime);
}

void Player::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
	SDL_FRect rect = {
		m_rect.x,
		m_rect.y,
		m_rect.width,
		m_rect.height
	};
	//SDL_RenderTexture(renderer, m_texture, NULL, &rect);
	SDL_RenderFillRect(renderer, &rect);
}
