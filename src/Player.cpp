#include "Player.hpp"

Player::Player(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Entity{ x, y, width, height, texture } {}

void Player::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_A:
				m_movingDirection = MovingDirection::Left;
				break;
			case SDLK_D:
				m_movingDirection = MovingDirection::Right;
				break;
			case SDLK_SPACE:
				m_jumpPressed = true;
				break;
		}
	}
	if (event.type == SDL_EVENT_KEY_UP) {
		switch (event.key.key) {
			case SDLK_A:
				if (m_movingDirection == MovingDirection::Left)
					m_movingDirection = MovingDirection::None;
				break;
			case SDLK_D:
				if (m_movingDirection == MovingDirection::Right)
					m_movingDirection = MovingDirection::None;
				break;
			case SDLK_SPACE:
				m_jumpPressed = false;
				break;
		}
	}
}

void Player::update(const Uint64 deltaTime) {
	float speedX = 0.5f;
	float jumpStrength = .15f * TILE_SIZE;
	float gravity = 0.02f;

	if (m_jumpPressed && m_isOnGround) {
		m_velocity.y = -jumpStrength;
		m_isOnGround = false;
	}

	switch (m_movingDirection) {
		case MovingDirection::None:
			m_velocity.x = 0.0f;
			break;
		case MovingDirection::Right:
			m_velocity.x = speedX;
			break;
		case MovingDirection::Left:
			m_velocity.x = -speedX;
			break;
		default:
			break;
	}

	if (!m_isOnGround) {
		m_velocity.y += gravity * deltaTime;
	}

	updateAnimationFrame(deltaTime);
}