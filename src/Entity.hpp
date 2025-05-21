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

enum class MovingDirection {
	None,
	Right,
	Left,
	Top,
	Bottom,
};

class Entity : public GameObject {
public:
	Entity(float x, float y, float width, float height, shared_SDL_Texture texture);

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
	virtual float getSpeedX() const { return m_speed.x; }
	virtual float getSpeedY() const { return m_speed.y; }
	virtual float getGravityForce() const { return m_gravityForce; }
	virtual float getJumpStrength() const { return m_jumpStrength; }
	virtual MovingDirection getHorizontalMovingDirection() const { return m_horizontalDirection; }
	virtual MovingDirection getVerticalMovingDirection() const { return m_verticalDirection; }

	// Setters
	virtual void setVelocityX(const float vel) { m_velocity.x = vel; }
	virtual void setVelocityY(const float vel) { m_velocity.y = vel; }
	virtual void setSpeedX(const float speed) { m_speed.x = speed; }
	virtual void setSpeedY(const float speed) { m_speed.y = speed; }
	virtual void setOnGround(const bool flag) { m_isOnGround = flag; }
	virtual void setGravityForce(const float gravity) { m_gravityForce = gravity; }
	virtual void setJumpStrength(const float jumpStrength) { m_jumpStrength = jumpStrength; }
	virtual void setHorizontalMovingDirection(const MovingDirection direction) { m_horizontalDirection = direction; }
	virtual void setVerticalMovingDirection(const MovingDirection direction) { m_verticalDirection = direction; }
protected:

	// Updates animation frame
	virtual void updateAnimationFrame(Uint64 deltaTime);

	// Animation texture sheet
	shared_SDL_Texture m_texture;
	// Entity maximum speed
	Vector2d m_speed;
	// Entity current velocity
	Vector2d m_velocity;
	// Gravity force for entity
	float m_gravityForce = 0.02f;
	// Entity horizontal moving direction
	MovingDirection m_horizontalDirection{ MovingDirection::None };
	// Entity vertical moving direction
	MovingDirection m_verticalDirection{ MovingDirection::None };
	// Entity jump strength
	float m_jumpStrength = .15f * TILE_SIZE;

	// Is jump key pressed ?
	bool m_jumpPressed{ false };
	// Is entity on ground ?
	bool m_isOnGround{ true };

	// Entity animations
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations;
	// Current entity animation
	std::weak_ptr<Animation> m_currentAnimation;
	// Entity frame info
	FrameInfo m_frameInfo{ 0, 0, 100 };
	// Does texture need fliped on rendering ?
	SDL_FlipMode m_textureFlip{ SDL_FLIP_NONE };
};