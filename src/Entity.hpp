#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

#include "Animation.hpp"
#include "GameObject.hpp"
#include "Level.hpp"

struct Vector2d {
	float x{ 0 };
	float y{ 0 };
};

struct FrameInfo {
	int index{ 0 };
	float timer{ 0 };
	float duration{ 0 };
};

class Entity : public GameObject {
public:
	Entity(float x, float y, float width, float height, SDL_Texture* texture);

	// Renders Entity
	virtual void render(SDL_Renderer* renderer);
	// Renders Entity regarding to cameraRect
	virtual void render(SDL_Renderer* renderer, SDL_FRect cameraRect);
	// Handles events (input)
	virtual void handleEvent(const SDL_Event& event) = 0;
	// Updates Entity state
	virtual void update(const Uint64 deltaTime) = 0;

	// Adds an animation
	virtual void addAnimation(const std::string& name, const int row, const int numFrames, const float frameWidth, const float frameHeight);
	// Sets current animation
	virtual bool setAnimation(const std::string& name);

	// Getters
	virtual float getVelocityX() const { return m_velocity.x; }
	virtual float getVelocityY() const { return m_velocity.y; }

	// Setters
	virtual void setVelocityX(const float vel) { m_velocity.x = vel; }
	virtual void setVelocityY(const float vel) { m_velocity.y = vel; }
	virtual void setOnGround(const bool flag) { m_isOnGround = flag; }
protected:

	// Updates animation frame
	virtual void updateAnimationFrame(Uint64 deltaTime);

	// Animation texture sheet
	SDL_Texture* m_texture;
	// Entity velocity
	Vector2d m_velocity;

	// Entity animations
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations;
	// Current entity animation
	std::weak_ptr<Animation> m_currentAnimation;
	// Entity frame info
	FrameInfo m_frameInfo{ 0, 0, 100 };

	SDL_FlipMode m_textureFlip{ SDL_FLIP_NONE };

	bool m_movingLeft{ false };
	bool m_movingRight{ false };
	bool m_jumpPressed{ false };
	bool m_isOnGround{ true };
};