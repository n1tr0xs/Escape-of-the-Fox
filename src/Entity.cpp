#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, SDL_Texture* texture) :
	m_rect{ x, y, width, height }, m_texture(texture) {
}

void Entity::updateAnimationFrame(Uint64 deltaTime) {
	if (!m_currentAnimation)
		return;

	m_frameTimer += deltaTime;

	if (m_frameTimer >= m_frameDuration) {
		m_frameTimer = 0.0f;
		m_currentFrameIndex = (m_currentFrameIndex + 1) % m_currentAnimation->getFrameCount();
	}
}

void Entity::addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight) {
	m_animations[name] = std::make_shared<Animation>(row, numFrames, frameWidth, frameHeight);
}

void Entity::render(SDL_Renderer* renderer) {
	const auto& src = m_currentAnimation->getFRect(m_currentFrameIndex);
	SDL_FRect dest = {
		m_rect.x,
		m_rect.y,
		m_rect.width,
		m_rect.height
	};
	
	SDL_RenderTextureRotated(renderer, m_texture, &src, &dest, 0.0, nullptr, m_textureFlip);
}