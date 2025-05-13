#include "MenuButton.hpp"

MenuButton::MenuButton(shared_TTF_Font font, const std::string& text, SceneResult result, SDL_Color color, SDL_Color selectedColor) :
	TextLabel(font, text, color), m_result{ result }, m_selectedColor{ selectedColor } {
	updateSurface();
}

void MenuButton::updateSurface() {
	resetSurface();
	resetTexture();

	m_surface.reset(TTF_RenderText_Solid(m_font.get(), m_text.c_str(), m_text.length(), m_isSelected ? m_selectedColor : m_color));
	updateSize();
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