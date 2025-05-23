#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "smart_SDL.hpp"

class TextLabel {
public:
	TextLabel(shared_TTF_Font font, const std::string& text, SDL_Color color);	

	// Renders TextLabel
	virtual void render(SDL_Renderer* renderer, const SDL_FRect* dest);

	// Getters
	virtual float getWidth() const { return m_width; }
	virtual float getHeight() const { return m_height; }
	std::string getText() const { return m_text; }

	// Setters
	virtual void setText(const std::string& text);
	virtual void setFont(shared_TTF_Font font);
	virtual void setColor(SDL_Color color);
protected:
	// Updates surface and m_width, m_height
	virtual void updateSurface();
	// Updates m_width, m_height
	void updateSize();

	std::string m_text;
	shared_TTF_Font m_font;
	SDL_Color m_color;

	unique_SDL_Texture m_texture{ nullptr, [](SDL_Texture* p) {if (p) SDL_DestroyTexture(p); p = nullptr;} };
	unique_SDL_Surface m_surface{ nullptr, [](SDL_Surface* p) {if (p) SDL_DestroySurface(p); p = nullptr;} };
	float m_width{ 0.0f };
	float m_height{ 0.0f };
};