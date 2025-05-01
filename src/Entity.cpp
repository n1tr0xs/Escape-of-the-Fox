#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, SDL_Texture* texture) :
	m_rect{ x, y, width, height }, m_texture(texture) {}

void Entity::updateAnimationFrame(Uint64 deltaTime) {
	if (!m_currentAnimation)
		return;

	m_frameInfo.timer += deltaTime;

	if (m_frameInfo.timer >= m_frameInfo.duration) {
		m_frameInfo.timer = 0.0f;
		m_frameInfo.index = (m_frameInfo.index + 1) % m_currentAnimation->getFrameCount();
	}
}

void Entity::addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight) {
	m_animations[name] = std::make_unique<Animation>(row, numFrames, frameWidth, frameHeight);
}

void Entity::render(SDL_Renderer* renderer) {
	if (!m_currentAnimation)
		return;
	const auto& src = m_currentAnimation->getFRect(m_frameInfo.index);
	SDL_RenderTextureRotated(renderer, m_texture, &src, &m_rect, 0.0, nullptr, m_textureFlip);
}