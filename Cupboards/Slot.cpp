#include "Slot.h"
#include "Chip.h"

Slot::Slot(int x, int y, sf::RenderWindow* window, sf::Font* font, int index) {
	this->x = x;
	this->y = y;

	this->window = window;
	this->rectangle.setSize(sf::Vector2f(10.f, 10.f));
	this->rectangle.setPosition(fit((float)x, 10.f), fit((float)y, 10.f));
	this->rectangle.setFillColor(sf::Color::Red);

	this->text.setFont(*font);
	this->text.setString(std::to_string(index));
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(fit((float)x, 24.f), fit((float)y, 24.f));

	this->index = index;
}


void Slot::setTargetColor(sf::Color color)
{
	this->color = color;
	this->target = true;

	float empty_size = (float)Chip::rect_size + 2.f;
	this->empty_rectangle.setSize(sf::Vector2f(empty_size, empty_size));
	this->empty_rectangle.setPosition(fit((float)x, empty_size), fit((float)y, empty_size));
	this->empty_rectangle.setFillColor(sf::Color::Black);

	float border_size = (float)Chip::rect_size + 4.f;
	this->border_rectangle.setSize(sf::Vector2f(border_size, border_size));
	this->border_rectangle.setPosition(fit((float)x, border_size), fit((float)y, border_size));
	this->border_rectangle.setFillColor(color);
}

void Slot::draw()
{
	this->rectangle.setFillColor(active ? sf::Color::White : sf::Color::Red);
	this->window->draw(this->rectangle);
	if (target) {
		this->window->draw(this->border_rectangle);
		this->window->draw(this->empty_rectangle);
	}
}

void Slot::draw_numbers()
{
	this->window->draw(this->text);
}

void Slot::setActive(bool active)
{
	this->active = active;
}

bool Slot::isActive()
{
	return this->active;
}

bool Slot::inside(int x, int y)
{
	sf::Vector2f pos(fit((float)this->x, (float)Chip::rect_size), fit((float)this->y, (float)Chip::rect_size));
	sf::Vector2f size((float)Chip::rect_size, (float)Chip::rect_size);
	return pos.x < x && pos.y < y && pos.x + size.x > x && pos.y + size.y > y;
}

void Slot::setFilled(bool filled)
{
	this->filled = filled;
}

bool Slot::isFilled()
{
	return this->filled;
}

bool Slot::isTarget()
{
	return this->target;
}

int Slot::getIndex()
{
	return this->index;
}