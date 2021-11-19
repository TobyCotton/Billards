#include "Game.h"
#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include "Table.h"
#include "Ball.h"

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), "Billards : A0031189");
    Table table(1);
    m_balls.push_back(new Ball(sf::Vector2f(400, 300)));
    m_balls.push_back(new Ball(sf::Vector2f(400, 500)));
    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && flag == 1)
        {
            m_balls[0]->SetVelocity(initial, sf::Mouse::getPosition());
            flag = 0;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && flag == 0)
        {
            initial = sf::Mouse::getPosition();
            flag = 1;
        }
        if (m_balls[0]->GetPosition().x <= 40 || m_balls[0]->GetPosition().x + 40 >= 960)
        {
            m_balls[0]->Bounce(0);
        }
        if (m_balls[0]->GetPosition().y <= 40 || m_balls[0]->GetPosition().y + 40 >= 585)
        {
            m_balls[0]->Bounce(1);
        }
        for (Ball* ball : m_balls)
        {
            ball->Move();
        }
        Collision();
        window.clear();
        table.Render(window);
        for (Ball* ball : m_balls)
        {
            ball->Render(window);
        }
        window.display();
    }
}

void Game::Collision()
{
    sf::Vector2f cuePosition = m_balls[0]->GetPosition();
    sf::Vector2f cueVelocity{ m_balls[0]->GetVelocity(0),m_balls[0]->GetVelocity(1) };
    float VLength = sqrt(pow(cueVelocity.x, 2) + pow(cueVelocity.y, 2));//length of Velocity
    int radius{ 20 };
    for (int i = 1; i < m_balls.size(); i++)
    {
        sf::Vector2f ballPosition = m_balls[i]->GetPosition();
        sf::Vector2f A{ cuePosition.x - ballPosition.x, cuePosition.y - ballPosition.y }; //distance vector between the balls
        float ALength = sqrt(pow(A.x, 2) + pow(A.y, 2)); // length of A
        sf::Vector2f Vhat{cueVelocity.x/VLength,cueVelocity.y/VLength}; //A portion of V
        sf::Vector2f Ahat{A.x/ALength,A.y/ALength}; // A portion of A
        float DotProduct= (Ahat.x*Vhat.x)+(Ahat.y*Vhat.y); // Dot Product of V and A
        float d = sqrt(1 - pow(DotProduct, 2)) * ALength; //Length to velocity at moment of collision
        if (d <= radius * 2)
        {
            float e = sqrt(pow(radius * 2, 2) - pow(d, 2)); //distance from d at moment of collision
            float CollisionDistance = abs(DotProduct * ALength) - e; // how far until collision
            if (CollisionDistance <= 0)
            {
                std::cout << "Fuck Yeah";
            }
        }
    }
}
