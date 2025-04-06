#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, SDL_Texture* texture) :
	m_rect{ x, y, width, height }, m_texture(texture) {
}

void Entity::updateAnimationFrame(Uint64 deltaTime) {
	if (!m_current_animation)
		return;

	m_frame_timer += deltaTime;

	if (m_frame_timer >= m_frame_duration) {
		m_frame_timer = 0.0f;
		m_current_frame_index = (m_current_frame_index + 1) % m_current_animation->getFrameCount();
	}
}

void Entity::addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight) {
	m_animations[name] = std::make_shared<Animation>(row, numFrames, frameWidth, frameHeight);
}

void Entity::render(SDL_Renderer* renderer) {
	const auto& src = m_current_animation->getFRect(m_current_frame_index);
	SDL_FRect dest = {
		m_rect.x,
		m_rect.y,
		m_rect.width,
		m_rect.height
	};
	
	SDL_RenderTextureRotated(renderer, m_texture, &src, &dest, 0.0, nullptr, m_texture_flip);
}