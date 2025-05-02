	#include "GameObject.h"

	GameObject::GameObject(float x, float y, float width, float height) :
		m_rect{ x, y, width, height } {}

	GameObject::GameObject(float width, float height) :
		m_rect{ 0.0f, 0.0f, width, height } {}

