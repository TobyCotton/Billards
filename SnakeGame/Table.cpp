#include "Table.h"
#include <iostream>

Table::Table(int value)
{
    sf::RectangleShape first{ sf::Vector2f(0,0) };
    sf::RectangleShape second{ sf::Vector2f(960,0) };
    sf::RectangleShape third{ sf::Vector2f(0,585) };
    sf::RectangleShape fourth{ sf::Vector2f(0,0) };

    first.setPosition(0, 0);
    second.setPosition(960, 0);
    third.setPosition(0, 585);
    fourth.setPosition(0, 0);

    m_table.setSize(sf::Vector2f(1000, 625));
    first.setSize(sf::Vector2f(1000, 40));
    second.setSize(sf::Vector2f(40, 625));
    third.setSize(sf::Vector2f(1000, 40));
    fourth.setSize(sf::Vector2f(40, 625));

    m_table.setFillColor(sf::Color::Green);
    first.setFillColor(sf::Color::Blue);
    second.setFillColor(sf::Color::Blue);
    third.setFillColor(sf::Color::Blue);
    fourth.setFillColor(sf::Color::Blue);

    m_Sides.push_back(first);
    m_Sides.push_back(second);
    m_Sides.push_back(third);
    m_Sides.push_back(fourth);
}

sf::RectangleShape Table::GetSide(int side)
{

    return sf::RectangleShape();
}
void Table::Render(sf::RenderWindow& window)
{
    window.draw(m_table);
    for (int i = 0; i < m_Sides.size(); i++)
    {
        window.draw(m_Sides[i]);
    }
}
