#include "Camera.hpp"

Camera::Camera(float width, float height) :
	GameObject{ width, height } {}

void Camera::follow(const SDL_FRect& target) {
	m_rect.x = target.x + target.w / 2 - m_rect.w / 2;
	m_rect.y = target.y + target.h / 2 - m_rect.h / 2;
}

void Camera::follow(const SDL_FRect& target, float mapWidth, float mapHeight) {
	follow(target);
	// Map boundaries
	if (m_rect.x < 0) m_rect.x = 0;
	if (m_rect.y < 0) m_rect.y = 0;
	if (m_rect.x + m_rect.w > mapWidth) m_rect.x = mapWidth - m_rect.w;
	if (m_rect.y + m_rect.h > mapHeight) m_rect.y = mapHeight - m_rect.h;
}
