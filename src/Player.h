#pragma once

#include "Entity.h"
#include "Level.h"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);

	void handleEvent(const SDL_Event& event) override;
	void update(Uint64 deltaTime, Level* level) override;
};