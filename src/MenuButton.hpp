#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Scene.hpp"
#include "TextLabel.hpp"

class MenuButton : public TextLabel {
public:
	MenuButton(shared_TTF_Font font, const std::string& text, SceneResult result, SDL_Color color, SDL_Color selectedColor);

	// Selects button
	void select();
	// Unselects button
	void unSelect();

	// Getters
	SceneResult getResult() const { return m_result; }

	// Setters
	void setSelectedColor(SDL_Color color);
	void setResult(SceneResult result) { m_result = result; }
private:
	virtual void updateSurface() override;
	
	bool m_isSelected{ false };
	SDL_Color m_selectedColor;
	SceneResult m_result;
};