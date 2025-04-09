#include "Player.h"

Player::Player(float x, float y, float width, float height, SDL_Texture* texture) : Entity(x, y, width, height, texture) {
	int fw = 256;
	int fh = 128;
	//addAnimation("idle", 0, 4, fw, fh);
	//addAnimation("running", 1, 4, fw, fh);
	//addAnimation("jumping", 2, 4, fw, fh);
	//addAnimation("crouching", 3, 4, fw, fh);
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
	float floor = 32*25;
	if (m_rect.y >= floor){  // Example ground level (y = 400)
		m_rect.y = floor;  // Snap to the ground level
		m_on_ground = true;
		m_y_velocity = 0;
	}


	updateAnimationFrame(deltaTime);
}

void Player::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
	SDL_FRect rect = {
		m_rect.x,
		m_rect.y,
		m_rect.width,
		m_rect.height
	};
	//SDL_RenderTexture(renderer, m_texture, NULL, &rect);
	SDL_RenderFillRect(renderer, &rect);
}