#include "Player.hpp"

Player::Player(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Entity{ x, y, width, height, texture } {

	setSpeedX(0.5f);
}

void Player::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_A:
				m_horizontalDirection = MovingDirection::Left;
				break;
			case SDLK_D:
				m_horizontalDirection = MovingDirection::Right;
				break;
			case SDLK_SPACE:
				m_jumpPressed = true;
				break;
		}
	}
	if (event.type == SDL_EVENT_KEY_UP) {
		switch (event.key.key) {
			case SDLK_A:
				if (m_horizontalDirection == MovingDirection::Left)
					m_horizontalDirection = MovingDirection::None;
				break;
			case SDLK_D:
				if (m_horizontalDirection == MovingDirection::Right)
					m_horizontalDirection = MovingDirection::None;
				break;
			case SDLK_SPACE:
				m_jumpPressed = false;
				break;
		}
	}
}

void Player::update(const Uint64 deltaTime) {
	if (m_jumpPressed && m_isOnGround) {
		setVelocityY(-getJumpStrength());
		setIsOnGround(false);
	}

	switch (m_horizontalDirection) {
		case MovingDirection::None:
			setVelocityX(0.0f);
			break;
		case MovingDirection::Right:
			setVelocityX(getSpeedX());
			break;
		case MovingDirection::Left:
			setVelocityX(-getSpeedX());
			break;
	}

	if (!getIsOnGround()) {
		setVelocityY(getVelocityY() + getGravityForce() * deltaTime);
	}

	updateAnimationFrame(deltaTime);
}