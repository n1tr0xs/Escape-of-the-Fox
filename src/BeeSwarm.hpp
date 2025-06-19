#include "Enemy.hpp"

class BeeSwarm : public Enemy {
public:
	BeeSwarm(float x, float y, float width, float height, shared_SDL_Texture texture);

	void update(const Uint64 deltaTime) override;
private:
	// Left top coordinate of movement rect
	Vector2d m_leftTop;
	// Right bottom coordinate of movement rect
	Vector2d m_rightBottom;
};