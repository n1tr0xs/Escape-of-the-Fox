#include "BeeSwarm.hpp"

BeeSwarm::BeeSwarm(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Enemy(x, y, width, height, texture) {

	m_left_top = {
		m_rect.x - TILE_SIZE * 3,
		m_rect.y - TILE_SIZE * 2,
	};

	m_right_bottom = {
		m_rect.x + TILE_SIZE * 3,
		m_rect.y + TILE_SIZE * 2,
	};

	m_horizontalDirection = MovingDirection::Left;
	m_verticalDirection = MovingDirection::Top;

	setSpeedX(TILE_SIZE / 64.);
	setSpeedY(TILE_SIZE / 128.);
}

void BeeSwarm::update(const Uint64 deltaTime) {
	if (m_horizontalDirection == MovingDirection::Left) {
		if (m_rect.x > m_left_top.x) {
			m_velocity.x = -m_speed.x;
		}
		else {
			m_horizontalDirection = MovingDirection::Right;
		}
	}
	else if (m_horizontalDirection == MovingDirection::Right) {
		if (m_rect.x < m_right_bottom.x) {
			m_velocity.x = m_speed.x;
		}
		else {
			m_horizontalDirection = MovingDirection::Left;
		}
	}

	if (m_verticalDirection == MovingDirection::Top) {
		if (m_rect.y > m_left_top.y) {
			m_velocity.y = -m_speed.y;
		}
		else {
			m_verticalDirection = MovingDirection::Bottom;
		}
	}
	else if (m_verticalDirection == MovingDirection::Bottom) {
		if (m_rect.y < m_right_bottom.y) {
			m_velocity.y = m_speed.y;
		}
		else {
			m_verticalDirection = MovingDirection::Top;
		}
	}
}