#include "Entity.hpp"

Entity::Entity(float x, float y, float width, float height, SDL_Texture* texture) :
	GameObject{x, y, width, height}, m_texture{ texture } {}

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