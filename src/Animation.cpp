#include "Animation.hpp"

Animation::Animation(int row, int numFrames, float frameWidth, float frameHeight) :
	m_row{ row }, m_numFrames{ numFrames }, m_frameWidth{ frameWidth }, m_frameHeight{ frameHeight } {}