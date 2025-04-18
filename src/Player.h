#pragma once

#include "Entity.h"
#include "Level.h"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);

	void update(Uint64 deltaTime, Level* level) override;
	void render(SDL_Renderer* renderer, Camera* camera) override;
private:
	bool m_isOnGround = false;
	float vx = 0.0f;
	float vy = 0.0f;

	void resolveHorizontalCollision(Uint64 deltaTime, Level* level);
	void resolveVerticalCollision(Uint64 deltaTime, Level* level);
};