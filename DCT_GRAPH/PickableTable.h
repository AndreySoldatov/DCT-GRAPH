#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class PickableTable
{
	std::vector<sf::RectangleShape> cells;
	std::vector<sf::Text> cells_text;
	float cell_width;
	float cell_height;
	int active_cell;
	sf::Vector2f pos;

public:

	PickableTable();
	PickableTable(sf::Vector2f pos, float cell_width, float cell_height, std::vector<std::string> const &content, sf::Font &font);

	int get_current_index();
	void process_input(sf::RenderWindow& window);
	void draw(sf::RenderWindow &window);
};

