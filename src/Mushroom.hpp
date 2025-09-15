#include "Enemy.hpp"

#include "Utils.hpp"

class Mushroom : public Enemy {
public:
	Mushroom(float x, float y, float width, float height, shared_SDL_Texture texture);

	void update(const Uint64 deltaTime) override;
private:
	const float JUMP_COOLDOWN_MIN{ 0.4f * 1000 };
	const float JUMP_COOLDOWN_MAX{ 1.1f * 1000 };

	float m_jumpCooldown{ utils::getRandom(JUMP_COOLDOWN_MIN, JUMP_COOLDOWN_MAX) };
};