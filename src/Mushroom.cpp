#include "Mushroom.hpp"

Mushroom::Mushroom(float x, float y, float width, float height, shared_SDL_Texture texture) :
	Enemy(x, y, width, height, texture) {

	setJumpStrength(0.1f * TILE_SIZE);
}

void Mushroom::update(const Uint64 deltaTime) {
	if (getIsOnGround()) {
		m_jumpCooldown -= deltaTime;
		if (m_jumpCooldown <= 0.0f) {
			setVelocityY(-getJumpStrength());
			setIsOnGround(false);
			m_jumpCooldown = utils::getRandom(JUMP_COOLDOWN_MIN, JUMP_COOLDOWN_MAX);
		}
	}
	else {
		setVelocityY(getVelocityY() + getGravityForce() * deltaTime);
	}
}