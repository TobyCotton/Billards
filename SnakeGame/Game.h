#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Ball;
class Table;

class Game
{
private:
	int m_Colissions = 3;
	int m_attempts = 0;
	int m_rounds = 0;
	int m_ScreenWidth{ 1000 };
	int m_ScreenHeight{ 625 };
	int flag{ 0 };
	sf::Vector2i initial{ sf::Vector2i(0,0) };
	std::vector <Ball*> m_balls{};
public:
	void Run();
	void Collision();
	void MovingColision(Ball* ball1, Ball* ball2);
	float CosOfAngle(sf::Vector2f A, sf::Vector2f B);
};

