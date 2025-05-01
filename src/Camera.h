#pragma once

#include <SDL3/SDL.h>

class Camera {
public:
	Camera(float width, float height);
	// Changes current position to be centered on target with boundaries mapWidth and mapHeight
	void follow(const SDL_FRect& target, float mapWidth, float mapHeight);
	
	// Getters
	SDL_FRect getRect() const { return m_rect; };
	float getX() const { return m_rect.x; };
	float getY() const { return m_rect.y; };
	float getWidth() const { return m_rect.w; };
	float getHeight() const { return m_rect.h; };
private:
	SDL_FRect m_rect;
};