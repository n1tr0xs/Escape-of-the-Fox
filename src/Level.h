#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <memory>


#include "Entity.h"
#include "Player.h"
#include "ResourceManager.h"

class Level {
public:
	Level(SDL_Texture* texture, ResourceManager* resMgr);

	void render(SDL_Renderer* renderer);
	void update(Uint64 deltaTime);
private:
	ResourceManager* m_resourceManager;
	std::vector<std::unique_ptr<Entity>> m_entities; // Game entities
	SDL_Texture* m_texture;
	std::vector<std::vector<Uint8>> m_tileMap;
	
	void addRow(Uint8 block);
	void addRows(int rows, Uint8 block);
};