#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
class Ball
{
private:
	sf::Vector2f m_position{};
	float m_velocityX{};
	float m_velocityY{};
	sf::CircleShape m_circle{};
public:
	Ball(sf::Vector2f position,sf::Color colour);
	void SetVelocity(sf::Vector2i initial, sf::Vector2i location);
	void SetVelocityCollision(sf::Vector2f velocity);
	float GetVelocity(int flag);
	void Render(sf::RenderWindow& window);
	void Move();
	void SetPosition(sf::Vector2f Coords);
	sf::Vector2f GetPosition();
	void Bounce(int flag);
};

