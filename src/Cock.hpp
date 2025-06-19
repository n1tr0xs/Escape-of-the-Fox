#include "Enemy.hpp"

class Cock : public Enemy {
public:
	Cock(float x, float y, float width, float height, shared_SDL_Texture texture);

	void update(const Uint64 deltaTime) override;
private:
	float m_leftEdgeX;
	float m_rightEdgeX;
};