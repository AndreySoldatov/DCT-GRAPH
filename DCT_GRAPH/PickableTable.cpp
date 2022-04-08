#include "PickableTable.h"

PickableTable::PickableTable()
{
}

PickableTable::PickableTable(sf::Vector2f pos, float cell_width, float cell_height, std::vector<std::string> const& content, sf::Font& font)
{
	this->pos = pos;
	this->cell_height = cell_height;
	this->cell_width = cell_width;

	active_cell = 0;

	for (int i = 0; i < content.size(); i++) {
		sf::RectangleShape tmp_rect;
		tmp_rect.setPosition(pos.x, pos.y + ((float)i * cell_height));
		tmp_rect.setSize(sf::Vector2f(cell_width, cell_height));
		tmp_rect.setFillColor(sf::Color(40, 40, 40));
		tmp_rect.setOutlineColor(sf::Color(200, 200, 200));
		tmp_rect.setOutlineThickness(3.0f);

		cells.push_back(tmp_rect);

		sf::Text tmp_text;
		
		tmp_text.setString(content[i]);
		tmp_text.setFont(font);
		tmp_text.setPosition(pos.x + (cell_width * 0.1f), pos.y + ((float)i * cell_height) + (cell_width * 0.05f));
		tmp_text.setCharacterSize(cell_height / 2.0f);
		tmp_text.setFillColor(sf::Color(200, 200, 200));

		cells_text.push_back(tmp_text);
	}

	cells[active_cell].setFillColor(sf::Color(200, 200, 200));
	cells_text[active_cell].setFillColor(sf::Color(40, 40, 40));
}

int PickableTable::get_current_index()
{
	return active_cell;
}

void PickableTable::process_input(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		for (size_t i = 0; i < cells.size(); i++)
		{
			if (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + cell_width) {
				if (mouse_pos.y >= (float)i * cell_height + pos.y && mouse_pos.y <= ((float)i * cell_height) + cell_height + pos.y) {
					cells[active_cell].setFillColor(sf::Color(40, 40, 40));
					cells_text[active_cell].setFillColor(sf::Color(200, 200, 200));

					active_cell = i;

					cells[active_cell].setFillColor(sf::Color(200, 200, 200));
					cells_text[active_cell].setFillColor(sf::Color(40, 40, 40));
				}
			}
		}
	}
}

void PickableTable::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < cells.size(); i++)
	{
		window.draw(cells[i]);
		window.draw(cells_text[i]);
	}
}
