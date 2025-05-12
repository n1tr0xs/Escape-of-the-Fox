#include "MainMenu.hpp"

MainMenu::MainMenu(ResourceManager* resourceManager) :
	MenuScene(resourceManager) {
	addButton("Start game", SceneResult::StartGame);
	addButton("Quit", SceneResult::Quit);
	addMusic("menu.mp3");

}