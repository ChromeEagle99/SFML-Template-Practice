#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../main.h"
#include "../AABB.h"


struct Node 
{
	sf::RectangleShape* rect;
	bool isClicked;
	int index;
};

bool mousePressed = false;
//std::vector<sf::RectangleShape*> rectangleVector;
std::vector<Node*> rectangleVector;
float size;
size_t grid_size;
void scene1_load()
{
	//std::cout << "Scene 1 Load" << std::endl;
	int index = 0;
	
	grid_size = 30;
	size = window->getSize().x / grid_size;
	for (size_t row = 0; row < grid_size; row++)
	{
		for (size_t col = 0; col < grid_size; col++)
		{
			index = (row + 1 )* (col + 1);
			Node* node = new Node();
			node->isClicked= false;

			sf::RectangleShape* rect = new sf::RectangleShape();
			rect->setSize({ size,size });
			rect->setPosition(col * size, row * size);
			rect->setOutlineColor(sf::Color::Black);
			rect->setOutlineThickness(5.0f);
			rect->setFillColor(sf::Color(0xD3D3D3FF));


			node->rect = rect;
			node->index = index;
			rectangleVector.push_back(node);
		}
	}
	std::cout << "Rectangles created: " << index << std::endl;
}
void scene1_init()
{
	//std::cout << "Scene 1 Initialise" << std::endl;

}
void scene1_update()
{
	//std::cout << "Scene 1 Update" << std::endl;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	int xIndex = mousePosition.x / size;
	int yIndex = mousePosition.y / size;

	int index = xIndex + (grid_size * yIndex);


	if (env->type == sf::Event::MouseButtonPressed) 
	{
		if (env->mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "aaaa" << std::endl;
			rectangleVector[index]->isClicked = !rectangleVector[index]->isClicked;
			rectangleVector[index]->isClicked = true;
		}
	}


	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed)
	//{
	//	mousePressed = true;
	//	std::cout << "aaaa" << std::endl;
	//	rectangleVector[index]->isClicked = !rectangleVector[index]->isClicked;
	//}
	//else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	std::cout << "wwwwwwwwwwww" << std::endl;

	//	mousePressed = false;
	//}

	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		AABB box(rectangleVector[i]->rect->getPosition().x + (rectangleVector[i]->rect->getSize().x / 2),
				rectangleVector[i]->rect->getPosition().y + (rectangleVector[i]->rect->getSize().y / 2),
				rectangleVector[i]->rect->getSize().x,
				rectangleVector[i]->rect->getSize().y);


		//if (pointVsRectCheck(mousePosition.x, mousePosition.y, box))
		//{
		//	//std::cout << "aa" << std::endl;

		//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed)
		//	{
		//		mousePressed = true;
		//		std::cout << "x: " << mousePosition.x << std::endl;
		//		std::cout << "y: " << mousePosition.y << std::endl;

		//		rectangleVector[i]->isClicked = !rectangleVector[i]->isClicked;

		//	}
		//}

		if (rectangleVector[i]->isClicked)
		{
			rectangleVector[i]->rect->setFillColor(sf::Color(0x565656FF));
		}
		else
		{
			rectangleVector[i]->rect->setFillColor(sf::Color(0xD3D3D3FF));
		}

		if (pointVsRectCheck(mousePosition.x, mousePosition.y, box))
		{
			rectangleVector[i]->rect->setFillColor(sf::Color(0xFF0000FF));
		}

		mousePressed = false;
	}

}
void scene1_draw()
{
	//std::cout << "Scene 1 Draw" << std::endl;
	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		//window.draw
		window->draw(*rectangleVector[i]->rect);
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
