#pragma once

#include "Entity.h"
#include "Level.h"

class Player : public Entity {
public:
	Player(float x, float y, float width, float height, SDL_Texture* texture);

	void handleEvent(const SDL_Event& event) override;
	void update(Uint64 deltaTime, Level* level) override;
	void render(SDL_Renderer* renderer, SDL_FRect cameraRect);
private:
	bool m_movingLeft = false;
	bool m_movingRight = false;
	bool m_jumpPressed = false;
	bool m_isOnGround = false;

	void resolveHorizontalCollision(Uint64 deltaTime, Level* level);
	void resolveVerticalCollision(Uint64 deltaTime, Level* level);
};