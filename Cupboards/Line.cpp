#include "Line.h"

Line::Line(Slot* slot1, Slot* slot2, sf::RenderWindow* window)
{
	this->slots.push_back(slot1);
	this->slots.push_back(slot2);

	this->window = window;

	//+++ calculation of line rotation
	float a = (float)(slot2->x - slot1->x);
	float b = (float)(slot2->y - slot1->y);

	// gipotenuza
	float length = std::pow(std::pow(std::abs(a), 2.f) + std::pow(std::abs(b), 2.f), 0.5f);

	// rotation from arccosinus
	float rotation = std::acos(a / length) / PI * 180.f;

	if (b < 0) // cos has same values for 2 angles
		rotation = -rotation;
	//--- calculation of line rotation

	float width = 1;
	this->rectangle.setSize(sf::Vector2f(length, width));
	this->rectangle.setPosition((float)slot1->x, fit((float)slot1->y, width));
	this->rectangle.setRotation(rotation);
	this->rectangle.setFillColor(sf::Color::Red);
}

void Line::draw()
{
	this->rectangle.setFillColor(active ? sf::Color::White : sf::Color::Red);
	this->window->draw(this->rectangle);
}

void Line::setActive(bool active)
{
	this->active = active;
}
