#include "Cock.hpp"

Cock::Cock(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Enemy(x, y, width, height, texture) {

	m_leftEdgeX = getX() - TILE_SIZE * 10;
	m_rightEdgeX = getX() + TILE_SIZE * 10;
	m_horizontalDirection = MovingDirection::Left;

	setSpeedX(TILE_SIZE / 64.);
}

void Cock::update(const Uint64 deltaTime) {

	m_dashCooldown -= deltaTime;
	if (m_isDashing) {
		m_dashDuration -= deltaTime;
		if (m_dashDuration <= 0.0f) {
			m_isDashing = false;
		}
		switch (m_horizontalDirection) {
			case MovingDirection::Right:
				setVelocityX(DASH_SPEED);
				break;
			case MovingDirection::Left:
				setVelocityX(-DASH_SPEED);
				break;
		}
	}
	else {
		if (m_horizontalDirection == MovingDirection::Left) {
			if (getX() > m_leftEdgeX) {
				setVelocityX(-getSpeedX());
			}
			else {
				m_horizontalDirection = MovingDirection::Right;
			}
		}
		else if (m_horizontalDirection == MovingDirection::Right) {
			if (getX() < m_rightEdgeX) {
				setVelocityX(getSpeedX());
			}
			else {
				m_horizontalDirection = MovingDirection::Left;
			}
		}

		if (m_dashCooldown <= 0.0f) {
			m_isDashing = true;
			m_dashDuration = DASH_DURATION;
			m_dashCooldown = DASH_COOLDOWN;
		}
	}
	if (!m_isOnGround) {
		setVelocityY(getVelocityY() + getGravityForce() * deltaTime);
	}
}