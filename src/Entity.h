#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Animation.h"
#include "Level.h"

struct Velocity {
	float x = 0;
	float y = 0;
};

class Entity {
public:
	// Constuctor
	Entity(float x, float y, float width, float height, SDL_Texture* texture);

	// Renders Entity
	virtual void render(SDL_Renderer* renderer);
	// Updates Animation frame
	virtual void updateAnimationFrame(Uint64 deltaTime);
	// Handles events (input)
	virtual void handleEvent(const SDL_Event& event) = 0;
	// Updates Entity state
	virtual void update(Uint64 deltaTime, Level* level) = 0;
	
	// getters
	SDL_FRect getRect() const { return m_rect; };
	float getX() const { return m_rect.x; };
	float getY() const { return m_rect.y; };
	float getWidth() const { return m_rect.w; };
	float getHeight() const { return m_rect.h; };

protected:
	virtual void addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight);

	SDL_FRect m_rect; // Entity position and size
	SDL_Texture* m_texture; // Animation texture sheet

	std::unordered_map<std::string, std::unique_ptr<Animation>> m_animations; // Entity animations
	Animation* m_currentAnimation; // Current entity animation

	float m_frameTimer = 0; // Frame timer
	float m_frameDuration = 100; // Frame duration
	int m_currentFrameIndex = 0; // Index for current frame in animation

	SDL_FlipMode m_textureFlip = SDL_FLIP_NONE;

	Velocity m_velocity;
};