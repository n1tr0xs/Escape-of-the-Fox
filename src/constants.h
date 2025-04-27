#pragma once

constexpr int TILE_SIZE = 32; // Tile size in pixels
constexpr int RENDERER_HEIGHT_IN_TILES = 20; // Renderer height in tiles
constexpr int RENDERER_WIDTH_IN_TILES = 32;  // Renderer width in tiles
constexpr int RENDERER_HEIGHT_IN_PIXELS = RENDERER_HEIGHT_IN_TILES * TILE_SIZE; // Renderer height in pixels
constexpr int RENDERER_WIDTH_IN_PIXELS = RENDERER_WIDTH_IN_TILES * TILE_SIZE; // Renderer width in pixels

constexpr char ASSET_PATH[] = "assets/{}";
constexpr char LEVEL_ASSET_PATH[] = "assets/level_{:02d}/{}";