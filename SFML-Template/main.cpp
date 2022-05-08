#include <SFML/Graphics.hpp>
#include "GameStateManager.h"
#include "GameStateList.h"
#include "main.h"

float g_dt;
sf::RenderWindow* window;
sf::Event* env;

int main()
{
    //float g_dt;
    // Window width and height
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 800;
    const char* windowTitle = "SFML Template";
    // Create a window
    sf::RenderWindow w(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Close | sf::Style::Titlebar);
    window = &w;
    sf::Clock deltaClock;

    //unsigned int gridWidth = 100;
    //unsigned int gridHeight = 100;

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //for (size_t i = 0; i < 20; i++)
    //{
    //    for (size_t j = 0; j < 20; j++) 
    //    {
    //        sf::RectangleShape shape(sf::Vector2f(20, 20));
    //        shape.setFillColor(sf::Color::Green);
    //    }
    //}
    
	while (GSM_current != GS_QUIT)
	{
		if (GSM_current == GS_RESTART)
		{
			GSM_current = GSM_previous;
			GSM_next = GSM_previous;
		}
		else
		{
			GSM_Update();
			fpLoad();
		}
		fpInitialize();

		//the game loop
		while (GSM_current == GSM_next)
		{
            sf::Event event;
            env = &event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)  GSM_next = GS_QUIT;
            }

            g_dt = deltaClock.getElapsedTime().asSeconds();

			fpUpdate();

            window->clear();
			fpDraw();
            window->display();

		}
		fpFree();
		if (GSM_next != GS_RESTART)
			fpUnload();
        GSM_previous = GSM_current;
        GSM_current = GSM_next;

	}

    return 0;
}