#pragma once

#include <SDL3/SDL.h>

class Animation {
public:
	Animation(int row, int numFrames, float frameWidth, float frameHeight);

	// Getters
	SDL_FRect getFRect(int frameNum) const { return { frameNum * m_frameWidth, m_row * m_frameHeight, m_frameWidth, m_frameHeight }; }
	float getFrameWidth() const { return m_frameWidth; }
	float getFrameHeight() const { return m_frameHeight; }
	int getFrameCount() const { return m_numFrames; }
	// Setters
	void setFrameWidth(float width) { m_frameWidth = width; }
	void setFrameHeight(float height) { m_frameHeight = height; }
	void setFrameCount(int frameCount) { m_numFrames = frameCount; }
private:
	int m_row, m_numFrames;
	float m_frameWidth, m_frameHeight;
};