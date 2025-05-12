#include "TextLabel.hpp"

TextLabel::TextLabel(TTF_Font* font, const std::string& text, SDL_Color color) :
	m_font{ font }, m_text{ text }, m_color{ color } {
	updateSurface();
}

TextLabel::~TextLabel() {
	if (m_surface) SDL_DestroySurface(m_surface);
}


void TextLabel::updateSurface() {
	if (m_surface) SDL_DestroySurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_text.length(), m_color);
	if (m_surface) {
		m_width = static_cast<float>(m_surface->w);
		m_height = static_cast<float>(m_surface->h);
	}
	else {
		m_width = m_height = 0.0f;
	}
}

void TextLabel::render(SDL_Renderer* renderer, const SDL_FRect* dest) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_RenderTexture(renderer, texture, NULL, dest);
	SDL_DestroyTexture(texture);
}

void TextLabel::setText(const std::string& text) {
	m_text = text;
	updateSurface();
}

void TextLabel::setFont(TTF_Font* font) {
	m_font = font;
	updateSurface();
}

void TextLabel::setColor(SDL_Color color) {
	m_color = color;
	updateSurface();
}