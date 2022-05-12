#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../main.h"
#include "../AABB.h"


struct Node 
{
	sf::RectangleShape* rect;
	bool isObstacle;
	int index;
	bool start;
	bool end;
};

bool keyPressed = false;
std::vector<Node*> rectangleVector;
float size;
size_t grid_size;
int vectorIndex = 0;
bool isStartPlaced = false;
bool isEndPlaced = false;


void scene1_load()
{
	//std::cout << "Scene 1 Load" << std::endl;
	
	
	grid_size = 30;
	size = window->getSize().x / grid_size;
	for (size_t row = 0; row < grid_size; row++)
	{
		for (size_t col = 0; col < grid_size; col++)
		{
			vectorIndex = (row + 1 )* (col + 1);
			Node* node = new Node();
			node->isObstacle= false;
			node->start= false;
			node->end= false;

			sf::RectangleShape* rect = new sf::RectangleShape();
			rect->setSize({ size,size });
			rect->setPosition(col * size, row * size);
			rect->setOutlineColor(sf::Color::Black);
			rect->setOutlineThickness(5.0f);
			rect->setFillColor(sf::Color(0xD3D3D3FF));


			node->rect = rect;
			node->index = vectorIndex;
			rectangleVector.push_back(node);
		}
	}
	std::cout << "Rectangles created: " << vectorIndex << std::endl;
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
	if (index < 0) index = 0;
	if (index >= vectorIndex) index = vectorIndex;



	if (!rectangleVector[index]->isObstacle) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (!isStartPlaced && !rectangleVector[index]->start)
			{
				rectangleVector[index]->start = true;
				isStartPlaced = true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (!isEndPlaced && !rectangleVector[index]->end)
			{
				rectangleVector[index]->end = true;
				isEndPlaced = true;
			}
		}	
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !rectangleVector[index]->start && !rectangleVector[index]->end)
	{
		rectangleVector[index]->isObstacle = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rectangleVector[index]->start && !rectangleVector[index]->end)
	{
		rectangleVector[index]->isObstacle = false;
	}

	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		AABB box(rectangleVector[i]->rect->getPosition().x + (rectangleVector[i]->rect->getSize().x / 2),
				rectangleVector[i]->rect->getPosition().y + (rectangleVector[i]->rect->getSize().y / 2),
				rectangleVector[i]->rect->getSize().x,
				rectangleVector[i]->rect->getSize().y);


		rectangleVector[i]->rect->setFillColor(sf::Color(0xD3D3D3FF));


		if (rectangleVector[i]->isObstacle)
		{
			rectangleVector[i]->rect->setFillColor(sf::Color(0x565656FF));
			continue;
		}


		if (rectangleVector[i]->start)
			rectangleVector[i]->rect->setFillColor(sf::Color(0xFF0000FF));
		else if (rectangleVector[i]->end)
			rectangleVector[i]->rect->setFillColor(sf::Color(0x0000FFFF));

		if (pointVsRectCheck(mousePosition.x, mousePosition.y, box))
		{
			rectangleVector[i]->rect->setFillColor(sf::Color(0xFF0000FF));
		}
	}

}
void scene1_draw()
{
	//std::cout << "Scene 1 Draw" << std::endl;
	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
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
