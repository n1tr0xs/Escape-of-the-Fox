#pragma once

#include "Entity.h"
#include "Level.h"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);
	
	void update(Uint64 deltaTime, Level* level) override;
	void render(SDL_Renderer* renderer) override;
private:
	bool m_on_ground = false;
	float vx = 0.0f;
	float vy = 0.0f;
};