#include "BeeSwarm.hpp"

BeeSwarm::BeeSwarm(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Enemy(x, y, width, height, texture) {

	m_leftTop = {
		getX() - TILE_SIZE * 3,
		getY() - TILE_SIZE * 2,
	};

	m_rightBottom = {
		getX() + TILE_SIZE * 3,
		getY() + TILE_SIZE * 2,
	};

	m_horizontalDirection = MovingDirection::Left;
	m_verticalDirection = MovingDirection::Top;

	setSpeedX(TILE_SIZE / 64.);
	setSpeedY(TILE_SIZE / 128.);
}

void BeeSwarm::update(const Uint64 deltaTime) {
	if (m_horizontalDirection == MovingDirection::Left) {
		if (getX() > m_leftTop.x) {
			setVelocityX(-getSpeedX());
		}
		else {
			m_horizontalDirection = MovingDirection::Right;
		}
	}
	else if (m_horizontalDirection == MovingDirection::Right) {
		if (getX() < m_rightBottom.x) {
			setVelocityX(getSpeedX());
		}
		else {
			m_horizontalDirection = MovingDirection::Left;
		}
	}

	if (m_verticalDirection == MovingDirection::Top) {
		if (getY() > m_leftTop.y) {
			setVelocityY(-getSpeedY());
		}
		else {
			m_verticalDirection = MovingDirection::Bottom;
		}
	}
	else if (m_verticalDirection == MovingDirection::Bottom) {
		if (getY() < m_rightBottom.y) {
			setVelocityY(getSpeedY());
		}
		else {
			m_verticalDirection = MovingDirection::Top;
		}
	}
}