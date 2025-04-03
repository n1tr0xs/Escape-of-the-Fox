#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include <string>

class Game {
public:
    Game(const std::string& title, int width, int height);
    ~Game();

    void run();

private:
    void processEvents();
    void update();
    void render();
    void cleanUp();
    void SDL_Fail(const std::string& message);

    bool m_running;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};

#endif // GAME_H
