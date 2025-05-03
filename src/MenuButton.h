#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Scene.h"

class MenuButton {
public:
	MenuButton(TTF_Font* font, const std::string& text, SceneResult result, SDL_Color color, SDL_Color selectedColor);
	~MenuButton();

	void render(SDL_Renderer* renderer, const SDL_FRect* dest);

	void select();
	void unSelect();

	// Getters
	SceneResult getResult() const { return m_result; }
	float getWidth() const { return m_width; }
	float getHeight() const { return m_height; }

	// Setters
	void setText(const std::string& text);
	void setFont(TTF_Font* font);
	void setColor(SDL_Color color);
	void setSelectedColor(SDL_Color color);
	void setResult(SceneResult result) { m_result = result; }
private:
	void updateSurface();

	std::string m_text;
	TTF_Font* m_font = nullptr;
	SceneResult m_result;

	SDL_Color m_color;
	SDL_Color m_selectedColor;

	bool m_isSelected = false;

	SDL_Surface* m_surface = nullptr;
	float m_width = 0.0f;
	float m_height = 0.0f;
};