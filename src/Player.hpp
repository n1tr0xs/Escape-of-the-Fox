#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);

	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
};