#pragma once

#include <SFML/Graphics.hpp>
#include "Part.h"
#include "Slot.h"

class Line : Part
{
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;

	const float PI = 3.14159265358979323846f;

	bool active = false;

public:

	std::vector<Slot*> slots;

	Line(Slot* slot1, Slot* slot2, sf::RenderWindow* window);

	void draw();

	void setActive(bool active);
};