#pragma once

#include <SDL3/SDL.h>

class Camera {
public:
	Camera(float width, float height);
	// Changes current position to be centered on target with boundaries mapWidth and mapHeight
	void follow(const SDL_FRect& target, float mapWidth, float mapHeight);
	
	float getX() const; // Returns x of the camera top left corner
	float getY() const; // Returns y of the camera top left corner
	float getWidth() const; // Returns width of the camera
	float getHeight() const; // Returns height of the camera
	SDL_FRect getRect() const; // Returns SDL_FRect of the camera
private:
	SDL_FRect m_rect;
};