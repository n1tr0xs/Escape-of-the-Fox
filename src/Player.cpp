#include "Player.h"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) : Entity(x, y, width, height, texture) {
	int fw = 256;
	int fh = 256;
	addAnimation("idle", 0, 4, fw, fh);
	addAnimation("running", 1, 4, fw, fh);
	addAnimation("jumping", 2, 4, fw, fh);
	addAnimation("crouching", 3, 4, fw, fh);
	m_current_animation = m_animations["idle"];
}

void Player::update(Uint64 deltaTime) {
	const auto state = SDL_GetKeyboardState(NULL);
	
	m_current_animation = m_animations[m_on_ground ? "idle" : "jumping"];

	if (state[SDL_SCANCODE_SPACE] && m_on_ground) {
		m_y_velocity = m_jump_strength;
		m_on_ground = false;
		m_current_animation = m_animations["jumping"];
	}
	if (state[SDL_SCANCODE_A]) {
		m_rect.x -= m_x_vel * deltaTime;
		m_current_animation = m_animations[m_on_ground ? "running" : "jumping"];
		m_texture_flip = SDL_FLIP_HORIZONTAL;
	}
	if (state[SDL_SCANCODE_D]) {
		m_rect.x += m_x_vel * deltaTime;
		m_current_animation = m_animations[m_on_ground ? "running" : "jumping"];
		m_texture_flip = SDL_FLIP_NONE;
	}
	if (state[SDL_SCANCODE_S]) {
		m_current_animation = m_animations["crouching"];
	}

	// Update vertical velocity (gravity)
	if (!m_on_ground) {
		m_y_velocity += 0.01f * deltaTime;  // Gravity (constant fall speed)
	}

	// Apply vertical movement
	m_rect.y += m_y_velocity * deltaTime;

	// Check if player has landed on the ground (simple ground check)
	if (m_rect.y >= 400.0f) {  // Example ground level (y = 400)
		m_rect.y = 400.0f;  // Snap to the ground level
		m_on_ground = true;
		m_y_velocity = 0;
	}


	updateAnimationFrame(deltaTime);
}
