#include "Ball.h"

Ball::Ball(sf::Vector2f position,sf::Color colour)
{
	m_velocityX = 0;
	m_velocityY = 0;
	m_position = position;
	m_circle.setPosition(position);
	m_circle.setFillColor(colour);
	m_circle.setRadius(20);
}

void Ball::SetVelocity(sf::Vector2i initial, sf::Vector2i location)
{
	m_velocityX = (location.x - initial.x);
	m_velocityY = (location.y - initial.y);

	float length = sqrt(pow(m_velocityX, 2) + pow(m_velocityY, 2));

	m_velocityX = m_velocityX / length;//make the velocities into unit vectors
	m_velocityY = m_velocityY / length;
}

void Ball::SetVelocityCollision(sf::Vector2f velocity)
{
	m_velocityX = velocity.x;
	m_velocityY = velocity.y;
}

float Ball::GetVelocity(int flag)
{
	if (flag == 0)
	{
		return m_velocityX;
	}
	else
	{
		return m_velocityY;
	}
}

void Ball::Render(sf::RenderWindow& window)
{
	window.draw(m_circle);
}

void Ball::Move()
{
	if (abs(m_velocityX) <= 0.001f)
	{
		m_velocityX = 0.0f;
	}
	if (abs(m_velocityY) <= 0.001f)
	{
		m_velocityY = 0.0f;
	}
	m_velocityX = m_velocityX * 0.9994;//apply fricition
	m_velocityY = m_velocityY * 0.9994;
	m_position.x += m_velocityX;
	m_position.y += m_velocityY;
	m_circle.setPosition(m_position);
}

void Ball::SetPosition(sf::Vector2f Coords)
{
	m_position = Coords;
}

sf::Vector2f Ball::GetPosition()
{
	return m_position;
}

void Ball::Bounce(int flag)//invert the direction when it bounces off a flat plain
{
	if (flag == 0)
	{
		m_velocityX = -m_velocityX;
	}
	else
	{
		m_velocityY = -m_velocityY;
	}
}

