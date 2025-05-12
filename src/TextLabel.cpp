#include "TextLabel.hpp"

TextLabel::TextLabel(TTF_Font* font, const std::string& text, SDL_Color color) :
	m_font{ font }, m_text{ text }, m_color{ color } {
	updateSurface();
}

TextLabel::~TextLabel() {
	resetSurface();
	resetTexture();
}

void TextLabel::updateSurface() {
	resetSurface();
	resetTexture();

	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_text.length(), m_color);
	updateSize();
}

void TextLabel::resetSurface() {
	if (m_surface) {
		SDL_DestroySurface(m_surface);
		m_surface = nullptr;
	}
}

void TextLabel::updateSize() {
	if (m_surface) {
		m_width = static_cast<float>(m_surface->w);
		m_height = static_cast<float>(m_surface->h);
	}
	else {
		m_width = m_height = 0.0f;
	}
}

void TextLabel::resetTexture() {
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void TextLabel::render(SDL_Renderer* renderer, const SDL_FRect* dest) {
	if (!m_texture)
		m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_RenderTexture(renderer, m_texture, NULL, dest);
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