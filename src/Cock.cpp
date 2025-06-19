#include "Cock.hpp"

Cock::Cock(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Enemy(x, y, width, height, texture) {

	m_leftEdgeX = getX() - TILE_SIZE * 10;
	m_rightEdgeX = getX() + TILE_SIZE * 10;
	m_horizontalDirection = MovingDirection::Left;

	setSpeedX(TILE_SIZE / 64.);
	setSpeedY(TILE_SIZE / 128.);
}

void Cock::update(const Uint64 deltaTime) {
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

	if (!m_isOnGround) {
		setVelocityY(getVelocityY() + m_gravityForce * deltaTime);
	}
}