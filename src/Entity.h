#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Animation.h"
#include "Level.h"

class Entity {
public:
	// Constuctor
	Entity(float x, float y, float width, float height, SDL_Texture* texture);
	
	// Renders Entity
	virtual void render(SDL_Renderer* renderer, Camera* camera);
	// Updates Animation frame
	virtual void updateAnimationFrame(Uint64 deltaTime);
	// Updates Entity state
	virtual void update(Uint64 deltaTime, Level* level) = 0;
	// Returns SDL_FRect of entity
	SDL_FRect getRect() const;

protected:
	virtual void addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight);
	SDL_FRect m_rect; // Entity position and size
	SDL_Texture* m_texture; // Animation texture sheet
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations; // Entity animations
	std::shared_ptr<Animation> m_currentAnimation; // Current entity animation

	float m_frameTimer = 0; // Frame timer
	float m_frameDuration = 100; // Frame duration
	int m_currentFrameIndex = 0; // Index for current frame in animation

	SDL_FlipMode m_textureFlip = SDL_FLIP_NONE;
};