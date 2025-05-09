#include "Player.hpp"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) :
	Entity(x, y, width, height, texture) {
	float fw = 256;
	float fh = 128;
	addAnimation("idle", 0, 4, fw, fh);
	//addAnimation("running", 1, 4, fw, fh);
	//addAnimation("jumping", 2, 4, fw, fh);
	//addAnimation("crouching", 3, 4, fw, fh);
	setAnimation("idle");
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

void Player::update(const Uint64 deltaTime, Level* level) {
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

	updateAnimationFrame(deltaTime);
}