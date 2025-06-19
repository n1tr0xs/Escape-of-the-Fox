#include "Enemy.hpp"

class Cock : public Enemy {
public:
	Cock(float x, float y, float width, float height, shared_SDL_Texture texture);

	void update(const Uint64 deltaTime) override;
private:
	float m_leftEdgeX;
	float m_rightEdgeX;

	// Dash constants
	const float DASH_COOLDOWN = { 2.0f * 1000 };
	const float DASH_DURATION = { 250.0f };
	const float DASH_SPEED = { TILE_SIZE/32.0f };

	// Dash runtime vars
	bool m_isDashing{ false };
	float m_dashCooldown{ DASH_COOLDOWN };
	float m_dashDuration{ 0.0f };
};