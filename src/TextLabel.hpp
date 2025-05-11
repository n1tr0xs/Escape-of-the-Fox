#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextLabel {
public:
	TextLabel(const std::string& text);

	// Renders TextLabel
	void render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor);
	// Getters
	std::string getText() const { return m_text; }
	// Setter
	void setText(const std::string& text) { m_text = text; }
private:
	std::string m_text;
};