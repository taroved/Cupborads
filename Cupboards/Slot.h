#pragma once

#include <SFML/Graphics.hpp>
#include "Part.h"

class Slot : Part
{
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;
	sf::RectangleShape empty_rectangle;
	sf::RectangleShape border_rectangle;
	sf::Text text;

	bool active = false;
	bool filled = false;
	bool target = false;
	sf::Color color;

	int index = 0;

public:

	int x, y;

	Slot(int x, int y, sf::RenderWindow* window, sf::Font* font, int index);

	void draw();

	void draw_numbers();

	void setActive(bool active);

	bool isActive();

	bool inside(int x, int y);

	void setFilled(bool filled);

	bool isFilled();

	void setTargetColor(sf::Color color);

	bool isTarget();

	int getIndex();
};