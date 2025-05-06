#include "Animation.hpp"

Animation::Animation(int row, int numFrames, float frameWidth, float frameHeight) :
	m_row(row), m_numFrames(numFrames), m_frameWidth(frameWidth), m_frameHeight(frameHeight) {}


const SDL_FRect Animation::getFRect(int frameNum) const {
	return { frameNum * m_frameWidth, m_row * m_frameHeight, m_frameWidth, m_frameHeight };
}