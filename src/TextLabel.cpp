#include "TextLabel.hpp"

TextLabel::TextLabel(const std::string& text) :
	m_text{ text } {}

void TextLabel::render(SDL_Renderer* renderer, TTF_Font* font, SDL_FRect rect, SDL_Color textColor) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, m_text.c_str(), m_text.length(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderTexture(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}
