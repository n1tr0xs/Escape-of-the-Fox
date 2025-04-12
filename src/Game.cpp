#include "Game.h"

Game::Game(const std::string& title) {
	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Fail("Failed to initialize SDL:");
	
	if (!SDL_CreateWindowAndRenderer(title.c_str(), 0, 0, SDL_WINDOW_FULLSCREEN|SDL_WINDOW_BORDERLESS, &m_window, &m_renderer))
		SDL_Fail("Couldn't create window and renderer.");
	
	m_renderTexture = SDL_CreateTexture(
		m_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		RENDERER_WIDTH_IN_PIXELS,
		RENDERER_HEIGHT_IN_PIXELS
	);

	m_resourceManager = std::make_unique<ResourceManager>();

	// Loading Player texture
	SDL_Texture* texture = m_resourceManager->loadTexture("assets/fox.png", m_renderer);
	m_entities.emplace_back(std::make_unique<Player>(0, 0, TILE_SIZE*4, TILE_SIZE*2, texture));
	// Creating Level
	SDL_Texture* levelTexture = m_resourceManager->loadTexture("assets/back.png", m_renderer);
	level = std::make_unique<Level>(levelTexture);

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
	if (m_renderTexture) {
		SDL_DestroyTexture(m_renderTexture);
		m_renderTexture = nullptr;
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
	}
	const bool* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		m_running = false;
	}
}

void Game::update(Uint64 deltaTime) {
	level->update(deltaTime);
	for (const auto& entity : m_entities) {
		entity->update(deltaTime, level.get());
	}
}

void Game::render() {
	// Rendering to "virtual screen"
	SDL_SetRenderTarget(m_renderer, m_renderTexture);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	
	level->render(m_renderer);
	for (const auto& entity : m_entities) {
		entity->render(m_renderer);
	}

	// Rendering "virtual screen" to real screen
	SDL_SetRenderTarget(m_renderer, nullptr);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	// Calculating the scale
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	float scaleX = (float)w / RENDERER_WIDTH_IN_PIXELS;
	float scaleY = (float)h / RENDERER_HEIGHT_IN_PIXELS;
	float scale = std::min(scaleX, scaleY);

	// Calculating destination rect
	int destW = RENDERER_WIDTH_IN_PIXELS * scale;
	int destH = RENDERER_HEIGHT_IN_PIXELS * scale;
	// Calculating offset for destination rect to be centered
	int offsetX = (w - destW) / 2;
	int offsetY = (h - destH) / 2;

	SDL_FRect destRect = { offsetX, offsetY, destW, destH };
	SDL_RenderTexture(m_renderer, m_renderTexture, nullptr, &destRect);

	SDL_RenderPresent(m_renderer);
}
