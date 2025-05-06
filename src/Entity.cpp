#include "Entity.hpp"

Entity::Entity(float x, float y, float width, float height, SDL_Texture* texture) :
	GameObject(x, y, width, height), m_texture{ texture } {}

void Entity::updateAnimationFrame(Uint64 deltaTime) {
	m_frameInfo.timer += deltaTime;

	if (m_frameInfo.timer >= m_frameInfo.duration) {
		m_frameInfo.timer = 0.0f;
		if (auto anim = m_currentAnimation.lock()) {
			m_frameInfo.index = (m_frameInfo.index + 1) % anim->getFrameCount();
		}
	}
}

void Entity::addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight) {
	m_animations[name] = std::make_shared<Animation>(row, numFrames, frameWidth, frameHeight);
}

bool Entity::setAnimation(const std::string& name) {
	auto it = m_animations.find(name);
	if (it != m_animations.end()) {
		m_currentAnimation = it->second;
		return true;
	}
	return false;
}

void Entity::render(SDL_Renderer* renderer) {
	if (!m_texture) return;
	if (auto anim = m_currentAnimation.lock()) {
		const SDL_FRect src = anim->getFRect(m_frameInfo.index);
		SDL_RenderTextureRotated(renderer, m_texture, &src, &m_rect, 0.0, nullptr, m_textureFlip);
	}
}

void Entity::render(SDL_Renderer* renderer, SDL_FRect cameraRect) {
	const SDL_FRect rect = {
		m_rect.x - cameraRect.x,
		m_rect.y - cameraRect.y,
		m_rect.w,
		m_rect.h
	};
	if (auto anim = m_currentAnimation.lock()) {
		const SDL_FRect src = anim->getFRect(m_frameInfo.index);
		SDL_RenderTextureRotated(renderer, m_texture, &src, &rect, 0.0, nullptr, m_textureFlip);
	}
}

void Entity::resolveHorizontalCollision(Uint64 deltaTime, Level* level) {
	float newX = m_rect.x + m_velocity.x * deltaTime;

	float topY = m_rect.y;
	float bottomY = topY + m_rect.h;

	float leftEdge = newX;
	float rightEdge = newX + m_rect.w;

	// Check left
	if (level->isSolidVertically(leftEdge, topY, bottomY)) {
		float tileX = std::floor(leftEdge / TILE_SIZE);
		newX = (tileX + 1) * TILE_SIZE;
	}

	// Check right
	if (level->isSolidVertically(rightEdge, topY, bottomY)) {
		float tileX = std::floor(rightEdge / TILE_SIZE);
		newX = tileX * TILE_SIZE - m_rect.w;
	}

	m_velocity.x = 0.0f;
	m_rect.x = newX;
}

void Entity::resolveVerticalCollision(Uint64 deltaTime, Level* level) {
	float newY = m_rect.y + m_velocity.y * deltaTime;

	float headY = newY;
	float feetY = headY + m_rect.h;

	float leftX = m_rect.x;
	float rightX = leftX + m_rect.w;

	// Check ground
	if (level->isSolidHorizontally(feetY, leftX, rightX)) {
		float tileY = std::floor(feetY / TILE_SIZE);
		newY = tileY * TILE_SIZE - m_rect.h;
		m_isOnGround = true;
		m_velocity.y = 0.0f;
	}
	else {
		m_isOnGround = false;
	}

	// Check head
	if (level->isSolidHorizontally(headY, leftX, rightX)) {
		float tileY = std::floor(headY / TILE_SIZE);
		newY = (tileY + 1) * TILE_SIZE;
		m_velocity.y = 0.0f;
	}

	m_rect.y = newY;
}