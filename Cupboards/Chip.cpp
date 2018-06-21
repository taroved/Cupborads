#include "Chip.h"

Chip::Chip(Slot* start, Slot* end, sf::Color color, sf::RenderWindow* window)
{
	this->start = start;
	this->end = end;
	this->color = color;
	this->window = window;
	this->rectangle.setSize(sf::Vector2f((float)this->rect_size, (float)this->rect_size));
	this->rectangle.setPosition(fit((float)start->x, (float)this->rect_size), fit((float)start->y, (float)this->rect_size));
	this->rectangle.setFillColor(color);

	this->index = end->getIndex();
}

void Chip::moveRectangle()
{
	if (this->moving) {
		sf::Time elapsed = this->clock.getElapsedTime();

		if (elapsed > this->movement_time) {
			this->start->setFilled(false);

			this->start = this->target_slot;
			this->rectangle.setPosition(fit((float)start->x, (float)this->rect_size), fit((float)start->y, (float)this->rect_size));

			this->moving = false;
		}
		else {
			// move code
			sf::Vector2f from((float)this->start->x, (float)this->start->y);
			sf::Vector2f to((float)this->target_slot->x, (float)this->target_slot->y);
			float spend = this->clock.getElapsedTime() / this->movement_time;
			sf::Vector2f cur_point(from.x + (to.x - from.x) * spend, from.y + (to.y - from.y) * spend);
			this->rectangle.setPosition(fit(cur_point.x, (float)this->rect_size), fit(cur_point.y, (float)this->rect_size));
		}
	}
}

void Chip::draw()
{
	this->moveRectangle();

	this->rectangle.setFillColor(current || active ? sf::Color::White : this->color);
	this->window->draw(this->rectangle);
}

void Chip::setCurrent(bool current)
{
	this->current = current;
}

bool Chip::getCurrent()
{
	return this->current;
}

void Chip::setActive(bool active)
{
	this->active = active;
}

bool Chip::inside(int x, int y)
{
	sf::Vector2f pos = this->rectangle.getPosition();
	sf::Vector2f size = this->rectangle.getSize();
	return pos.x < x && pos.y < y && pos.x + size.x > x && pos.y + size.y > y;
}

Slot* Chip::getSlot()
{
	return this->start;
}

void Chip::move(Slot* slot)
{
	this->clock.restart();
	this->moving = true;
	this->target_slot = slot;
}

bool Chip::movementCompleted()
{
	return !this->moving;
}

int Chip::getIndex()
{
	return this->index;
}