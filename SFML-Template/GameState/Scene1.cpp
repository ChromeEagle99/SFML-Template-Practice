#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../main.h"

std::vector<sf::RectangleShape*> rectangleVector;


void scene1_load()
{
	//std::cout << "Scene 1 Load" << std::endl;
	int index = 0;
	
	size_t grid_size = 20;
	float size = window->getSize().x / grid_size;
	for (size_t row = 0; row < grid_size; row++)
	{
		for (size_t col = 0; col < grid_size; col++)
		{
			index = (row + 1 )* (col + 1);

			sf::RectangleShape* rect = new sf::RectangleShape();
			rect->setSize({ size,size });
			rect->setPosition(col * size, row * size);
			rect->setOutlineColor(sf::Color::Black);
			rect->setOutlineThickness(5.0f);
			rect->setFillColor(sf::Color(0xD3D3D3FF));

			rectangleVector.push_back(rect);
		}
	}
	std::cout << index << std::endl;
}
void scene1_init()
{
	//std::cout << "Scene 1 Initialise" << std::endl;

}
void scene1_update()
{
	//std::cout << "Scene 1 Update" << std::endl;

}
void scene1_draw()
{
	//std::cout << "Scene 1 Draw" << std::endl;
	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		//window.draw
		window->draw(*rectangleVector[i]);
	}
	//std::cout << rectangleVector.size() << std::endl;
}
void scene1_free()
{
	//std::cout << "Scene 1 Free" << std::endl;

}
void scene1_unload()
{
	//std::cout << "Scene 1 Unload" << std::endl;
	if (!rectangleVector.empty())
	{
		for (size_t i = 0; i < rectangleVector.size(); i++)
		{
			//window.draw
			delete rectangleVector[i];
		}
	}

}
