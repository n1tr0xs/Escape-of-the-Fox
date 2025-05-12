#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextLabel {
public:
	TextLabel(TTF_Font* font, const std::string& text, SDL_Color color);
	virtual ~TextLabel();

	// Renders TextLabel
	virtual void render(SDL_Renderer* renderer, const SDL_FRect* dest);
	
	// Getters
	virtual float getWidth() const { return m_width; }
	virtual float getHeight() const { return m_height; }
	std::string getText() const { return m_text; }

	// Setters
	virtual void setText(const std::string& text);
	virtual void setFont(TTF_Font* font);
	virtual void setColor(SDL_Color color);
protected:
	// Updates surface and m_width, m_height
	virtual void updateSurface();
	// Resets m_texture
	void resetTexture();
	// Resets m_surface
	void resetSurface();

	std::string m_text;
	TTF_Font* m_font;
	SDL_Color m_color;

	SDL_Texture* m_texture{ nullptr };
	SDL_Surface* m_surface{ nullptr };
	float m_width{ 0.0f };
	float m_height{ 0.0f };
};