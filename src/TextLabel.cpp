#include "TextLabel.hpp"

TextLabel::TextLabel(shared_TTF_Font font, const std::string& text, SDL_Color color) :
	m_font{ font }, m_text{ text }, m_color{ color } {
	updateSurface();
}

void TextLabel::updateSurface() {
	resetTexture();
	resetSurface();

	m_surface.reset(TTF_RenderText_Solid(m_font.get(), m_text.c_str(), m_text.length(), m_color));
	updateSize();
}

void TextLabel::resetSurface() {
	m_surface.reset();
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
	m_texture.reset();
}

void TextLabel::render(SDL_Renderer* renderer, const SDL_FRect* dest) {
	if (!m_texture)
		m_texture.reset(SDL_CreateTextureFromSurface(renderer, m_surface.get()));
	SDL_RenderTexture(renderer, m_texture.get(), NULL, dest);
}

void TextLabel::setText(const std::string& text) {
	m_text = text;
	updateSurface();
}

void TextLabel::setFont(shared_TTF_Font font) {
	m_font = font;
	updateSurface();
}

void TextLabel::setColor(SDL_Color color) {
	m_color = color;
	updateSurface();
}