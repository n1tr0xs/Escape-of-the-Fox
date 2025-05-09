#include "MenuButton.hpp"

MenuButton::MenuButton(TTF_Font* font, const std::string& text, SceneResult result, SDL_Color color, SDL_Color selectedColor) :
	m_font{ font }, m_text{ text }, m_result{ result }, m_color{ color }, m_selectedColor{ selectedColor } {
	updateSurface();
}

MenuButton::~MenuButton() {
	if (m_surface) SDL_DestroySurface(m_surface);
}

void MenuButton::updateSurface() {
	if (m_surface) SDL_DestroySurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_text.length(), m_isSelected ? m_selectedColor : m_color);
	m_width = static_cast<float>(m_surface->w);
	m_height = static_cast<float>(m_surface->h);
}

void MenuButton::render(SDL_Renderer* renderer, const SDL_FRect* dest) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_RenderTexture(renderer, texture, NULL, dest);
	SDL_DestroyTexture(texture);
}

void MenuButton::select() {
	m_isSelected = true;
	updateSurface();
}

void MenuButton::unSelect() {
	m_isSelected = false;
	updateSurface();
}

void MenuButton::setText(const std::string& text) {
	m_text = text;
	updateSurface();
}

void MenuButton::setFont(TTF_Font* font) {
	m_font = font;
	updateSurface();
}

void MenuButton::setColor(SDL_Color color) {
	m_color = color;
	updateSurface();
}

void MenuButton::setSelectedColor(SDL_Color color) {
	m_selectedColor = color;
	updateSurface();
}