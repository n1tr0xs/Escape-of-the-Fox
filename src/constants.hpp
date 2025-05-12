#pragma once

constexpr const int TILE_SIZE = 32; // Tile size in pixels
constexpr const int RENDERER_HEIGHT_IN_TILES = 20; // Renderer height in tiles
constexpr const int RENDERER_WIDTH_IN_TILES = 32;  // Renderer width in tiles
constexpr const int RENDERER_HEIGHT_IN_PIXELS = RENDERER_HEIGHT_IN_TILES * TILE_SIZE; // Renderer height in pixels
constexpr const int RENDERER_WIDTH_IN_PIXELS = RENDERER_WIDTH_IN_TILES * TILE_SIZE; // Renderer width in pixels

constexpr const char* ASSET_PATH = "assets/{}";
constexpr const char* LEVEL_ASSET_PATH = "assets/level_{:02d}/{}";

constexpr int BACKGROUND_MUSIC_CHANNEL = 0;

#ifdef _DEBUG
#define DEBUG_LOG(x) SDL_Log(x)
#else
#define DEBUG_LOG(x)
#endif