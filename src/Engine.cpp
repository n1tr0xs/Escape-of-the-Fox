#include "Engine.h"
#include "LevelScene.h"
#include "MenuScene.h"
#include "GameCompleteScene.h"

Engine::Engine(const std::string& title) {
	if (!SDL_Init(SDL_INIT_VIDEO))
		SDL_Fail("Failed to initialize SDL:");
	
	if (!TTF_Init())
		SDL_Fail("Couldn't init TTF.");
	
	if (!SDL_CreateWindowAndRenderer(title.c_str(), RENDERER_WIDTH_IN_PIXELS, RENDERER_HEIGHT_IN_PIXELS, 0/*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS*/, &m_window, &m_renderer))
		SDL_Fail("Couldn't create window and renderer.");
	
	// Creating ResourceManager
	m_resourceManager = std::make_unique<ResourceManager>(m_renderer);

	// Creating "virtual screen"
	m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RENDERER_WIDTH_IN_PIXELS, RENDERER_HEIGHT_IN_PIXELS);

	// Creating MenuScene
	m_currentScene = std::make_unique<MenuScene>(m_resourceManager.get());

	m_running = true;
}

Engine::~Engine() {
	SDL_Log("Destructing Engine.");
	if (m_renderTexture) {
		SDL_Log("\tDestructing m_renderTexture.");
		SDL_DestroyTexture(m_renderTexture);
		m_renderTexture = nullptr;
	}
	if (m_renderer) {
		SDL_Log("\tDestructing m_renderer.");
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (m_window) {
		SDL_Log("\tDestructing m_window.");
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	m_resourceManager.reset();

	TTF_Quit();
	SDL_Quit();
}

void Engine::SDL_Fail(const std::string& message) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());
	delete this;
}

void Engine::run() {
	Uint64 lastTime = SDL_GetTicks();
	while (m_running) {
		Uint64 currentTime = SDL_GetTicks();
		Uint64 deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processEvents();
		update(deltaTime);
		render();
	}
}

void Engine::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			m_running = false;
		}
		m_currentScene->handleEvent(event);
	}
}

void Engine::update(Uint64 deltaTime) {
	if (m_currentScene) {
		m_currentScene->update(deltaTime);
		SceneResult sceneResult = m_currentScene->getResult();
		switch (sceneResult) {
			case SceneResult::None:
				break;
			case SceneResult::StartGame:
				m_currentLevel = 1; // first level
				m_currentScene = std::make_unique<LevelScene>(m_resourceManager.get(), m_currentLevel);
				break;
			case SceneResult::Quit:
				m_running = false;
				break;
			case SceneResult::Victory:
				++m_currentLevel; 
				if (m_currentLevel <= m_maxLevel) // next level
					m_currentScene = std::make_unique<LevelScene>(m_resourceManager.get(), m_currentLevel);
				else // game won
					m_currentScene = std::make_unique<GameCompleteScene>(m_resourceManager.get());
				break;
			case SceneResult::GameOver:
				m_currentLevel = 0;
				m_currentScene = std::make_unique<MenuScene>(m_resourceManager.get());
			default:
				break;
		}
	}
}

void Engine::render() {
	// Rendering to "virtual screen"
	SDL_SetRenderTarget(m_renderer, m_renderTexture);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	if (m_currentScene)
		m_currentScene->render(m_renderer);

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
