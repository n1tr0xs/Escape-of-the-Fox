#include "Game.h"

Game::Game(const std::string& title, int width, int height) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Fail("Failed to initialize SDL:");
	}

	m_window = SDL_CreateWindow(title.c_str(), width, height, 0);
	if (!m_window) {
		SDL_Fail("Window couldn't be created!");
	}

	m_renderer = SDL_CreateRenderer(m_window, nullptr);
	if (!m_renderer) {
		SDL_Fail("Renderer couldn't be created!");
	}

	m_resourceManager = std::make_unique<ResourceManager>();

	// Loading Player texture
	m_resourceManager->loadTexture("assets/fox.png", m_renderer);
	
	// Creating Level
	SDL_Texture* levelTexture = m_resourceManager->loadTexture("assets/back.png", m_renderer);
	level = std::make_unique<Level>(levelTexture, m_resourceManager.get());

	m_running = true;
}

Game::~Game() {
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (m_window) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	SDL_Quit();
}

void Game::SDL_Fail(const std::string& message) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());
	delete this;
}

void Game::run() {
	Uint64 lastTime = SDL_GetTicks();
	Uint64 currentTime, deltaTime;
	while (m_running) {
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			m_running = false;
		}
		const auto state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			m_running = false;
		}
	}
}

void Game::update(Uint64 deltaTime) {
	level->update(deltaTime);
}

void Game::render() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	level->render(m_renderer);
	SDL_RenderPresent(m_renderer);
}
