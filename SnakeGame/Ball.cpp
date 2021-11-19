#include "Ball.h"

Ball::Ball(sf::Vector2f position)
{
	m_velocityX = 0;
	m_velocityY = 0;
	m_position = position;
	m_circle.setPosition(position);
	m_circle.setFillColor(sf::Color::White);
	m_circle.setRadius(20);
}

void Ball::SetVelocity(sf::Vector2i initial, sf::Vector2i location)//figures out the velocity for the cue ball based on mouse position clicks
{
	m_velocityX = (initial.x - location.x)/20;
	m_velocityY = (initial.y - location.y)/20;
	if (m_velocityX > 1 && m_velocityX > 0) // clamping velocity values to 1
	{
		m_velocityX = 1;
	}
	else if (m_velocityX < -1 && m_velocityX < 0)
	{
		m_velocityX = -1;
	}
	if (m_velocityY > 1 && m_velocityY > 0)
	{
		m_velocityY = 1;
	}
	else if (m_velocityY < -1 && m_velocityY < 0)
	{
		m_velocityY = -1;
	}
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
	m_velocityX = m_velocityX * 0.999;
	m_velocityY = m_velocityY * 0.999;
	m_position.x += m_velocityX;
	m_position.y += m_velocityY;
	m_circle.setPosition(m_position);
}

sf::Vector2f Ball::GetPosition()
{
	return m_position;
}

void Ball::Bounce(int flag)//inverses velocity when ball bounces on a wall
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
