#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);
	
	void update(Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;
private:
	float m_x_vel = .5;
	float m_jump_strength = -2.6;
	float m_y_velocity = 0;
	bool m_on_ground = false;
};