#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextLabel {
public:
	TextLabel(TTF_Font* font, const std::string& text, SDL_Color color);
	~TextLabel();

	// Renders TextLabel
	void render(SDL_Renderer* renderer, const SDL_FRect* dest);
	
	// Getters
	float getWidth() const { return m_width; }
	float getHeight() const { return m_height; }
	std::string getText() const { return m_text; }
	// Setter
	// Setters
	void setText(const std::string& text);
	void setFont(TTF_Font* font);
	void setColor(SDL_Color color);
private:
	void updateSurface();

	std::string m_text;
	TTF_Font* m_font;
	SDL_Color m_color;

	SDL_Surface* m_surface{ nullptr };
	float m_width{ 0.0f };
	float m_height{ 0.0f };
};