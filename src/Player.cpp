#include "Player.h"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) :
	Entity(x, y, width, height, texture) {
	int fw = 256;
	int fh = 128;
	//addAnimation("idle", 0, 4, fw, fh);
	//addAnimation("running", 1, 4, fw, fh);
	//addAnimation("jumping", 2, 4, fw, fh);
	//addAnimation("crouching", 3, 4, fw, fh);
	m_currentAnimation = m_animations["idle"];
}

void Player::update(Uint64 deltaTime, Level* level) {	
	const int TILE_SIZE = 32;
	float speedX = 0.5f;	
	float jumpStrength = .15f * TILE_SIZE;
	float gravity = 0.05f;
	float floor = 13 * TILE_SIZE;

	const bool* keyState = SDL_GetKeyboardState(NULL);
	
	if (keyState[SDL_SCANCODE_SPACE] && m_isOnGround) {
		vy = -jumpStrength;
		m_isOnGround = false;
	}

	if (keyState[SDL_SCANCODE_A]) {
		m_rect.x -= speedX * deltaTime;
	}
	
	if (keyState[SDL_SCANCODE_D]) {
		m_rect.x += speedX * deltaTime;
	}

	if (!m_isOnGround) {
		vy += gravity * deltaTime;
	}

	m_rect.y += vy * deltaTime;

	if (m_rect.y + m_rect.height >= floor) {
		m_rect.y = floor - m_rect.height;
		m_isOnGround = true;
		vy = 0;
	}

	
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
