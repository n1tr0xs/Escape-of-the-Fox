#include "Player.hpp"

Player::Player(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Entity{ x, y, width, height, texture } {
	
	setSpeedX(0.5f);
}

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
	if (m_jumpPressed && m_isOnGround) {
		m_velocity.y = -m_jumpStrength;
		m_isOnGround = false;
	}

	switch (m_movingDirection) {
		case MovingDirection::None:
			m_velocity.x = 0.0f;
			break;
		case MovingDirection::Right:
			m_velocity.x = m_speed.x;
			break;
		case MovingDirection::Left:
			m_velocity.x = -m_speed.x;
			break;
		default:
			break;
	}

	if (!m_isOnGround) {
		m_velocity.y += m_gravityForce * deltaTime;
	}

	updateAnimationFrame(deltaTime);
}