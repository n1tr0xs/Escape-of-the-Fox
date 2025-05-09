#pragma once

#include <SDL3/SDL.h>

class GameObject {
public:
	GameObject(float x, float y, float width, float height);
	GameObject(float width, float height);

	GameObject(GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;

	// Getters
	SDL_FRect getRect() const { return m_rect; }
	float getX() const { return m_rect.x; }
	float getY() const { return m_rect.y; }
	float getWidth() const { return m_rect.w; }
	float getHeight() const { return m_rect.h; }

	// Setters
	void setRect(const SDL_FRect& rect) { m_rect = rect; }
	void setRect(float x, float y, float width, float height) { m_rect = { x, y, width, height }; }
	void setX(float x) { m_rect.x = x; }
	void setY(float y) { m_rect.y = y; }
	void setWidth(float width) { m_rect.w = width; }
	void setHeight(float height) { m_rect.h = height; }
protected:
	SDL_FRect m_rect;
};

