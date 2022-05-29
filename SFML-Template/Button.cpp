
#include "Button.h"
#include "main.h"

Button::Button(float x, float y, float w, float h, const char* str, void (*functionPointer)(void)) 
	:x(x), y(y), w(w), h(h)
{
	this->box = AABB(x + (w / 2), y + (h / 2), w, h);
	this->FP = functionPointer;

	sf::Vector2f pos(x, y);
	sf::Vector2f size(w, h);

	shape = sf::RectangleShape(size);
	shape.setPosition(pos);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(sf::Color::Black);

	txt = sf::Text();
	txt.setPosition(x, y);
	txt.setString(str);
	txt.setCharacterSize(24);
	txt.setFont(font);
	txt.setFillColor(sf::Color::Red);
	txt.setStyle(sf::Text::Bold);
}
Button::~Button() 
{

}
void Button::OnClick() 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		FP();
	}
}

sf::RectangleShape Button::getShape()
{
	return shape;
}
AABB Button::getAABB()
{
	return box;
}

void Button::Draw(sf::RenderWindow& display) 
{
	display.draw(shape);
	display.draw(txt);
}