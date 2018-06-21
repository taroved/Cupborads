#include "Game.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

sf::Color Game::get_chip_color_by_index(int i)
{
	i %= this->chip_colors.size();
	return this->chip_colors[i];
}

std::vector<int> Game::parse_numbers(std::string input)
{
	std::replace(input.begin(), input.end(), ',', ' ');
	std::stringstream ss(input);

	std::vector<int> nums;
	int num;
	while (ss >> num)
		nums.push_back(num);
	return nums;
}

void Game::load(sf::RenderWindow* window)
{
	std::ifstream file("config.txt");

	if (file.is_open())
	{
		int chip_count;
		file >> chip_count;
		std::cout << "Chips count: " << chip_count << std::endl;

		int point_count;
		file >> point_count;
		std::cout << "Points count: " << point_count << std::endl;

		// load slots
		std::vector<std::vector<int>> points;
		for (int i = 0; i < point_count; i++) {
			std::string xy_str;
			file >> xy_str;
			std::vector<int> xy = this->parse_numbers(xy_str);
			this->slots.push_back(Slot(xy[0], xy[1], window, &this->font, i + 1));
			std::cout << "Loaded slot: " << xy[0] << " " << xy[1] << std::endl;
		}

		// load chips
		std::vector<int> starts, ends;
		std::string positions_str;

		file >> positions_str;
		starts = this->parse_numbers(positions_str);

		file >> positions_str;
		ends = this->parse_numbers(positions_str);

		for (int i = 0; i < starts.size(); i++) {
			sf::Color color = this->get_chip_color_by_index(i);
			Slot* start = &this->slots[starts[i] - 1];
			Slot* end = &this->slots[ends[i] - 1];
			this->chips.push_back(new Chip(start, end, color, window));
			start->setFilled(true);
			end->setTargetColor(color);
		}
		std::cout << "Loaded chips: " << starts.size() << std::endl;

		// load lines
		int line_count;
		file >> line_count;
		for (int i = 0; i < line_count; i++) {
			std::string nums_str;
			file >> nums_str;
			std::vector<int> nums = this->parse_numbers(nums_str);
			this->lines.push_back(Line(&this->slots[nums[0] - 1], &this->slots[nums[1] - 1], window));
		}
		std::cout << "Loaded lines: " << this->lines.size() << std::endl;

		file.close();
	}
	else
	{
		std::cout << "config.txt not found" << std::endl;
	}
}

Game::Game(sf::RenderWindow* window)
{
	this->window = window;

	if (!this->font.loadFromFile("arial.ttf"))
		std::cout << "Font loading failed" << std::endl;

	this->winner_text.setFont(this->font);
	this->winner_text.setString("You are winner!");
	this->winner_text.setCharacterSize(100);
	this->winner_text.setFillColor(sf::Color::White);
	this->winner_text.setPosition(50.f, 200.f);

	this->load(window);
}

void Game::handleChipMovement()
{
	if (this->state == State::Movement) {
		// cant get pointer to vector element 
		if (this->active_chip->movementCompleted()) {
			// clear activation states
			for (Slot& slot : this->slots)
				slot.setActive(false);
			for (Line& line : this->lines)
				line.setActive(false);
			this->active_chip->setActive(false);

			// mark slot as filled
			this->active_chip->getSlot()->setFilled(true);

			this->state = State::Inactive;

			// check game end status
			int success_count = (int)this->chips.size();
			for (Chip* chip : this->chips) {
				if (chip->getIndex() == chip->getSlot()->getIndex())
					success_count--;
			}
			if (success_count == 0)
				this->state = State::Winner;
		}
	}
}

void Game::draw()
{
	if (this->state == State::Winner) {
		this->window->draw(this->winner_text);
	}
	else {
		this->handleChipMovement();

		for (Line line : this->lines)
			line.draw();
		for (Slot slot : this->slots)
			slot.draw();
		for (Chip* chip : this->chips)
			chip->draw();
		//for (Slot slot : this->slots)
		//	slot.draw_numbers();
	}
}

void Game::mouseMove(int x, int y)
{
	for (Chip* chip : this->chips)
		chip->setCurrent(chip->inside(x, y));
}

void Game::mousePressed(int x, int y)
{
	if (this->state == State::Inactive) {
		// clear activation state for slots and lines
		for (Slot& slot : this->slots)
			slot.setActive(false);
		for (Line& line : this->lines)
			line.setActive(false);

		// activate chips
		Slot* active_slot = nullptr;
		for (Chip* chip : this->chips) {
			bool active = chip->inside(x, y);
			chip->setActive(active);
			if (active) {
				active_slot = chip->start;
				this->active_chip = chip;
			}
		}

		// activate slots and lines
		if (active_slot != nullptr) {
			this->activateSlots(active_slot);

			this->state = State::Activated;
		}
	}
	else if (this->state == State::Activated)
	{
		// skip chip clicks
		for (Chip* chip : this->chips) {
			bool active = chip->inside(x, y);
			if (active) {
				return;
			}
		}
		// handle slot click
		for (Slot& slot : this->slots) {
			bool active = slot.inside(x, y);
			if (active) {
				this->active_chip->move(&slot);

				this->state = State::Movement;
			}
		}
	}
}

void Game::activateSlots(Slot* slot)
{
	for (Line& line : this->lines) {
		if (line.slots[0] == slot && !line.slots[1]->isFilled()
			|| line.slots[1] == slot && !line.slots[0]->isFilled()) {
			for (Slot* line_slot : line.slots) // for by line slots
				line_slot->setActive(true);
			line.setActive(true);
		}
	}
}

Game::~Game()
{
	for (Chip* chip : this->chips)
		delete chip;
}