#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Table
{
private:
	std::vector<sf::RectangleShape> m_Sides{};
	sf::RectangleShape m_table{sf::Vector2f(0,0)};
public:
	Table(int value);
	sf::RectangleShape GetSide(int side);
	void Render(sf::RenderWindow& window);
};

