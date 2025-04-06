#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Animation.h"

// Entity rect
struct Rect {
	float x;
	float y;
	float width;
	float height;
};

class Entity {
public:
	// Constuctor
	Entity(float x, float y, float width, float height, SDL_Texture* texture);
	
	// Renders Entity
	virtual void render(SDL_Renderer* renderer);
	// Updates Animation frame
	virtual void updateAnimationFrame(Uint64 deltaTime);
	// Updates Entity state
	virtual void update(Uint64 deltaTime)=0;
	

protected:
	virtual void addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight);
	Rect m_rect; // Entity position and size
	SDL_Texture* m_texture; // Animation texture sheet
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations; // Entity animations
	std::shared_ptr<Animation> m_current_animation; // Current entity animation

	float m_frame_timer = 0; // Frame timer
	float m_frame_duration = 100; // Frame duration
	int m_current_frame_index = 0; // Index for current frame in animation

	SDL_FlipMode m_texture_flip = SDL_FLIP_NONE;
};