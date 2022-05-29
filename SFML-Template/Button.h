#pragma once

#include "AABB.h"
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(float, float, float, float, const char*, void (*)(void));
	~Button();
	void (*FP)(void);
	void OnClick();
	void Draw(sf::RenderWindow&);
	sf::RectangleShape getShape();
	AABB getAABB();

private:
	float x, y;
	float w, h;
	AABB box;
	sf::RectangleShape shape;
	sf::Text txt;
	
};

