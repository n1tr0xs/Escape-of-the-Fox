#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

#include "Animation.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

struct Velocity {
	float x = 0;
	float y = 0;
};

struct FrameInfo {
	int index = 0;
	float timer = 0;
	float duration = 0;
};

class Entity: public GameObject {
public:
	Entity(float x, float y, float width, float height, SDL_Texture* texture);

	virtual void render(SDL_Renderer* renderer); // Renders Entity
	virtual void render(SDL_Renderer* renderer, SDL_FRect cameraRect); // Renders Entity regarding to cameraRect
	virtual void handleEvent(const SDL_Event& event) = 0; // Handles events (input)
	virtual void update(const Uint64 deltaTime, Level* level) = 0; // Updates Entity state
	
	virtual void addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight); // Adds an animation
	virtual bool setAnimation(const std::string& name); // Sets current animation

	virtual float getVelocityX() const { return m_velocity.x; }
	virtual float getVelocityY() const { return m_velocity.y; }

	virtual void setVelocityX(const float vel) { m_velocity.x = vel; }
	virtual void setVelocityY(const float vel) { m_velocity.y = vel; }
protected:
	void resolveVerticalCollision(Uint64 deltaTime, Level* level);

	virtual void updateAnimationFrame(Uint64 deltaTime); // Updates animation frame

	SDL_Texture* m_texture; // Animation texture sheet
	Velocity m_velocity; // Entity velocity

	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations; // Entity animations
	std::weak_ptr<Animation> m_currentAnimation; // Current entity animation
	FrameInfo m_frameInfo{ 0, 0, 100 }; // Entity frame info

	SDL_FlipMode m_textureFlip = SDL_FLIP_NONE;

	bool m_movingLeft = false;
	bool m_movingRight = false;
	bool m_jumpPressed = false;
	bool m_isOnGround = false;
};