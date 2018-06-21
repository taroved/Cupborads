#pragma once

#include "Slot.h"
#include "Chip.h"
#include "Line.h"

class Game
{

private:
	std::vector<Slot> slots;
	std::vector<Chip*> chips;
	std::vector<Line> lines;

	sf::RenderWindow* window;

	std::vector<sf::Color> chip_colors = {
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Cyan
	};

	sf::Font font;
	sf::Text winner_text;

	sf::Color get_chip_color_by_index(int i);

	std::vector<int> parse_numbers(std::string input);

	void load(sf::RenderWindow* window);

	enum State
	{
		Inactive,
		Activated,
		Movement,
		Winner
	};

	State state = State::Inactive;

	Chip* active_chip = nullptr;


	void handleChipMovement();

	void activateSlots(Slot* slot);

public:

	Game(sf::RenderWindow* window);

	void draw();

	void mouseMove(int x, int y);

	void mousePressed(int x, int y);

	~Game();
};