#pragma once

#include <SDL3/SDL.h>

class Animation {
public:
	Animation(int row, int numFrames, float frameWidth, float frameHeight);

	// Getters
	const SDL_FRect getFRect(int frameNum) const;
	int getFrameCount() const { return m_numFrames; }
private:
	int m_row, m_numFrames;
	float m_frameWidth, m_frameHeight;
};