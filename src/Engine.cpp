#include "Engine.hpp"
#include "GameCompleteScene.hpp"
#include "LevelScene.hpp"
#include "MenuScene.hpp"
#include "MainMenu.hpp"
#include "Utils.hpp"

Engine::Engine(const std::string& title) {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		utils::SDL_Fail("Failed to initialize SDL:");

	if (!TTF_Init())
		utils::SDL_Fail("Couldn't init TTF.");

	SDL_WindowFlags flags = 0;
	//SDL_WindowFlags flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS;
	m_window.reset(SDL_CreateWindow(title.c_str(), RENDERER_WIDTH_IN_PIXELS, RENDERER_HEIGHT_IN_PIXELS, flags));
	if (!m_window)
		utils::SDL_Fail("Couldn't create window.");

	m_renderer.reset(SDL_CreateRenderer(m_window.get(), NULL));
	if (!m_renderer)
		utils::SDL_Fail("Couldn't create renderer.");

	// Creating "virtual screen"
	m_renderTexture.reset(SDL_CreateTexture(m_renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RENDERER_WIDTH_IN_PIXELS, RENDERER_HEIGHT_IN_PIXELS));

	// Creating ResourceManager
	m_resourceManager = std::make_unique<ResourceManager>(m_renderer.get());

	// Audio system initialization
	/*m_audioDeviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!m_audioDeviceID)
		utils::SDL_Fail("Couldn't init Audio device.");
	if (!Mix_OpenAudio(m_audioDeviceID, NULL))
		utils::SDL_Fail("Couldn't open audio device.");*/

	// Creating MenuScene
	m_currentScene = createMenuScene();

	m_running = true;
}

Engine::~Engine() {
	
	m_currentScene.reset();
	m_resourceManager.reset();

	SDL_CloseAudioDevice(m_audioDeviceID);
	//Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

std::unique_ptr<Scene> Engine::createMenuScene() {
	return std::make_unique<MainMenu>(m_resourceManager.get());
}

void Engine::run() {
	Uint64 lastTime = SDL_GetTicks();
	while (m_running) {
		const Uint64 startTicks = SDL_GetTicks();
		const Uint64 deltaTime = startTicks - lastTime;
		lastTime = startTicks;

		processEvents();
		update(deltaTime);
		render();
		
		const Uint64 frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < m_minFrameTicks) SDL_Delay(m_minFrameTicks - frameTicks);
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

void Engine::update(const Uint64 deltaTime) {
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
			m_currentScene = createMenuScene();
			break;
		case SceneResult::QuitToMainMenu:
			m_currentLevel = 0;
			m_currentScene = createMenuScene();
			break;
		}
	}
}

void Engine::render() {
	// Rendering to "virtual screen"
	SDL_SetRenderTarget(m_renderer.get(), m_renderTexture.get());
	SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(m_renderer.get());

	if (m_currentScene)
		m_currentScene->render(m_renderer.get());

	// Rendering "virtual screen" to real screen
	SDL_SetRenderTarget(m_renderer.get(), nullptr);
	SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
	SDL_RenderClear(m_renderer.get());

	// Calculating the scale
	int w, h;
	SDL_GetWindowSize(m_window.get(), &w, &h);
	float scaleX = (float)w / RENDERER_WIDTH_IN_PIXELS;
	float scaleY = (float)h / RENDERER_HEIGHT_IN_PIXELS;
	float scale = std::min(scaleX, scaleY);

	// Calculating destination rect
	float destW = RENDERER_WIDTH_IN_PIXELS * scale;
	float destH = RENDERER_HEIGHT_IN_PIXELS * scale;
	// Calculating offset for destination rect to be centered
	float offsetX = (w - destW) / 2;
	float offsetY = (h - destH) / 2;

	SDL_FRect destRect = { offsetX, offsetY, destW, destH };
	SDL_RenderTexture(m_renderer.get(), m_renderTexture.get(), nullptr, &destRect);

	SDL_RenderPresent(m_renderer.get());
}
