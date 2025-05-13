#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <memory>

using unique_SDL_Window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using unique_SDL_Renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using unique_SDL_Texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
using unique_SDL_Surface = std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;

using shared_SDL_Texture = std::shared_ptr<SDL_Texture>;
using shared_TTF_Font = std::shared_ptr<TTF_Font>;
using shared_Mix_Chunk = std::shared_ptr<Mix_Chunk>;