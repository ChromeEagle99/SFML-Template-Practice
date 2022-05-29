#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../GameStateManager.h"
#include "../GameStateList.h"
#include "../main.h"
#include "../AABB.h"
#include "../Button.h"
#include "../TextBox.h"

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
size_t grid_size = 30;
int vectorIndex = 0;
bool isStartPlaced = false;
bool isEndPlaced = false;



std::vector<Button> btnList;

void scene1_load()
{

	Button btnTest(40, 50, 200, 50, "Restart Scene", []()
		{
			GSM_next = GS_RESTART;
			std::cout << "Restart " << std::endl;
		});


	Button btnIncreaseGridSize(40, 120, 40, 50, " +", []()
		{
			grid_size++;
			GSM_next = GS_RESTART;
		});

	Button btnResetGridSize(100, 115, 80, 60, " Reset\nSize", []()
		{
			grid_size = 30;;
			GSM_next = GS_RESTART;
		});

	Button btnDecreaseGridSize(200, 120, 40, 50, " -", []()
		{
			grid_size--;
			if (grid_size <= 0) grid_size = 1;
			GSM_next = GS_RESTART;
		});

	btnList.push_back(btnTest);
	btnList.push_back(btnIncreaseGridSize);
	btnList.push_back(btnResetGridSize);
	btnList.push_back(btnDecreaseGridSize);

}
void scene1_init()
{
	isStartPlaced = isEndPlaced = false;
	//window->requestFocus();
	size = window->getSize().x / grid_size;
	for (size_t row = 0; row < grid_size; row++)
	{
		for (size_t col = 0; col < grid_size; col++)
		{
			vectorIndex = (row + 1) * (col + 1);
			Node* node = new Node();
			node->isObstacle = false;
			node->start = false;
			node->end = false;

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
	std::cout << "grid_size: " << grid_size << std::endl;
}
void scene1_update()
{
	if (controlWindow->hasFocus())
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*controlWindow);
		sf::Vector2f worldPos = controlWindow->mapPixelToCoords(mousePosition);

		for (size_t i = 0; i < btnList.size(); i++)
		{
			AABB box = btnList[i].getAABB();
			if (pointVsRectCheck(worldPos.x, worldPos.y, box))
			{
				btnList[i].OnClick();
			}
		}
	}


	if (window->hasFocus())
	{
		bool outOfWindowCheck = false;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition);


		static int yuyu = 0;
		if (mousePosition.x < 0 || mousePosition.x > window->getSize().x || 
			mousePosition.y < 0 || mousePosition.y > window->getSize().y)
		{
			outOfWindowCheck = true;

		}
		if (outOfWindowCheck) return;


		int xIndex = worldPos.x / size;
		int yIndex = worldPos.y / size;
		int index = xIndex + (grid_size * yIndex);


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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			GSM_next = GS_RESTART;
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
			{
				rectangleVector[i]->rect->setFillColor(sf::Color(0xFF0000FF));
				continue;
			}
			else if (rectangleVector[i]->end)
			{
				rectangleVector[i]->rect->setFillColor(sf::Color(0x0000FFFF));
				continue;
			}

			if (pointVsRectCheck(worldPos.x, worldPos.y, box))
			{
				rectangleVector[i]->rect->setFillColor(sf::Color(0xFF0000FF));
			}
		}
	}
}
void scene1_draw()
{
	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		window->draw(*rectangleVector[i]->rect);
	}

	for (size_t i = 0; i < btnList.size(); i++)
	{
		btnList[i].Draw(*controlWindow);
	}

}
void scene1_free()
{
	for (size_t i = 0; i < rectangleVector.size(); i++)
	{
		delete[] rectangleVector[i]->rect;
		delete[] rectangleVector[i];
	}
	rectangleVector.clear();
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
