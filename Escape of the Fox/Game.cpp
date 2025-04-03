#include "Game.h"

Game::Game(const std::string& title, int width, int height) : 
    m_window(nullptr), 
    m_renderer(nullptr),
    m_running(false) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Fail("Failed to initialize SDL:");
    }

    m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
    if (!m_window) {
        SDL_Fail("Window couldn't be created!");
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_Fail("Renderer couldn't be created!");
    }

    m_running = true;
}

Game::~Game() {
    cleanUp();
}

// Error logging and cleanup
void Game::SDL_Fail(const std::string& message) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());
    cleanUp();
    exit(1);
}

// Main game loop
void Game::run() {
    while (m_running) {
        processEvents();
        update();
        render();
    }
}

// Handle user input
void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
    }
}

// Update game logic
void Game::update() {
}

// Render the game
void Game::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

// Cleanup SDL resources
void Game::cleanUp() {
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
