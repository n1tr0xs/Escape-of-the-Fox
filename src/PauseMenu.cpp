#pragma once

#include "PauseMenu.hpp"

PauseMenu::PauseMenu(ResourceManager* resourceManager) :
	MenuScene(resourceManager) {
	addButton("Continue", SceneResult::Continue);
	addButton("Quit to Menu", SceneResult::QuitToMenu);
}
