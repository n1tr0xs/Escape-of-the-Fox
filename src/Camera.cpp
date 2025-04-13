#include "Camera.h"

Camera::Camera(float width, float height) {
	view = { 0, 0, width, height };
}

void Camera::follow(const SDL_FRect& target, float mapWidth, float mapHeight) {
	view.x = target.x + target.w / 2 - view.w / 2;
	view.y = target.y + target.h / 2 - view.h / 2;
	if (view.x < 0)
		view.x = 0;
	if (view.y < 0)
		view.y = 0;
	if (view.x + view.w > mapWidth)
		view.x = mapWidth - view.w;
	if (view.y + view.h > mapHeight)
		view.y = mapHeight - view.h;
}