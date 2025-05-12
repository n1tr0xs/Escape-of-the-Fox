#include "MenuButton.hpp"

MenuButton::MenuButton(TTF_Font* font, const std::string& text, SceneResult result, SDL_Color color, SDL_Color selectedColor) :
	TextLabel(font, text, color), m_result{ result }, m_selectedColor{ selectedColor } {
	updateSurface();
}

void MenuButton::updateSurface() {
	if (m_surface) SDL_DestroySurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_text.length(), m_isSelected ? m_selectedColor : m_color);
	if(m_surface){
		m_width = static_cast<float>(m_surface->w);
		m_height = static_cast<float>(m_surface->h);
	}
	else {
		m_width = m_height = 0;
	}
}

void MenuButton::select() {
	m_isSelected = true;
	updateSurface();
}

void MenuButton::unSelect() {
	m_isSelected = false;
	updateSurface();
}

void MenuButton::setSelectedColor(SDL_Color color) {
	m_selectedColor = color;
	updateSurface();
}