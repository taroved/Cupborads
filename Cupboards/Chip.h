#pragma once

#include <SFML/Graphics.hpp>
#include "Part.h"
#include "Slot.h"

class Chip : Part
{
	sf::Color color;

	sf::RenderWindow* window;
	sf::RectangleShape rectangle;

	bool current = false;
	bool active = false;

	sf::Clock clock;
	bool moving = false;
	Slot* target_slot = nullptr;
	const sf::Time movement_time = sf::seconds(0.5f);

	int index = 0;

public:

	static const int rect_size = 50;

	Slot* start;
	Slot* end;

	Chip(Slot* start, Slot* end, sf::Color color, sf::RenderWindow* window);

	void moveRectangle();

	void draw();

	void setCurrent(bool current);

	bool getCurrent();

	void setActive(bool active);

	bool inside(int x, int y);

	Slot* getSlot();

	void move(Slot* slot);

	bool movementCompleted();

	int getIndex();
};