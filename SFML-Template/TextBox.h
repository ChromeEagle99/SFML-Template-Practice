#pragma once
#include "AABB.h"
#include <SFML/Graphics.hpp>

class TextBox
{
public:

	TextBox(float, float, float, float, const char*, void (*)(void));
	~TextBox();
	void (*FP)(void);
	void OnClick();
	void Draw(sf::RenderWindow&);
	sf::RectangleShape getShape();
	AABB getAABB();


	bool isSelected;

private:
	float x, y;
	float w, h;
	AABB box;
	sf::RectangleShape shape;
	sf::Text shadowText;
	sf::Text txt;
	
};

