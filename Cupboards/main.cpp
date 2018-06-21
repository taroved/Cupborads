#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cupboard game");

	Game game(&window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::MouseMoved:
					game.mouseMove(event.mouseMove.x, event.mouseMove.y);
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
						game.mousePressed(event.mouseButton.x, event.mouseButton.y);
					break;
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		game.draw();
		window.display();
	}

	return 0;
}