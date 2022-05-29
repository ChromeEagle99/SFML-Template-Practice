#include <SFML/Graphics.hpp>
#include "GameStateManager.h"
#include "GameStateList.h"
#include "main.h"
#include "Button.h"
#include <iostream>
float g_dt;
sf::RenderWindow* window;
sf::RenderWindow* controlWindow;
sf::Event* env;
sf::Font font;
int main()
{
    
    if (!font.loadFromFile("Assets/Font/arial.ttf"))
    {
        std::cout << "Unable to load font " << std::endl;
    }


    //float g_dt;
    // Window width and height
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 800;
    const char* windowTitle = "SFML Template";
    // Create a window
    sf::RenderWindow s(sf::VideoMode(300, windowHeight), windowTitle, sf::Style::Titlebar);

    sf::RenderWindow w(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Close | sf::Style::Titlebar);
    window = &w;
    controlWindow = &s;
    sf::Clock deltaClock;
    w.setKeyRepeatEnabled(false);
    //unsigned int gridWidth = 100;
    //unsigned int gridHeight = 100;
    sf::Vector2i mainWindowPos = w.getPosition();
    mainWindowPos.x -= 300;
    s.setPosition(mainWindowPos);

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
                //if (event.type == sf::Event::mov)
                //{

                //}

            }

            g_dt = deltaClock.getElapsedTime().asSeconds();

			fpUpdate();

            window->clear();
            controlWindow->clear(sf::Color::White);
			fpDraw();
            window->display();
            controlWindow->display();

		}
		fpFree();
		if (GSM_next != GS_RESTART)
			fpUnload();
        GSM_previous = GSM_current;
        GSM_current = GSM_next;

	}

    return 0;
}