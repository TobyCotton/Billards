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
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            m_balls.push_back(new Ball(sf::Vector2f((i * 50) + 50, (i * 50) + 50), sf::Color::White));
        }
        else
        {
            m_balls.push_back(new Ball(sf::Vector2f((i * 50) + 50, (i * 50) + 50), sf::Color::Blue));
        }
    }
    sf::Event event;
    while (window.isOpen())
    {
        if (m_Colissions >= 3)
        {
            m_rounds++;
            m_attempts = 0;
            m_Colissions = 0;
            int counter = 0;
            for (Ball* ball : m_balls)
            {
                if (counter == 0)
                {
                    sf::Vector2f random{ 500,500 };
                    ball->SetPosition(random);
                    counter++;
                }
                else
                {
                    int use1 = m_ScreenWidth - 120;
                    int use2 = m_ScreenHeight - 120;
                    float x = rand() % use1;
                    float y = rand() % use2;
                    sf::Vector2f random{ 40 + x,40 + y };
                    ball->SetPosition(random);
                    counter++;
                }
            }
        }
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
        if (abs(m_balls[0]->GetVelocity(0)) <= 0.0001f && abs(m_balls[0]->GetVelocity(1)) <= 0.0001f)
        {
            flag = 1;
            if (m_attempts >= 2)
            {
                std::cout << "You completed " << m_rounds << " rounds" << std::endl;
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && flag == 1)
        {
            sf::Vector2i location = sf::Vector2i(m_balls[0]->GetPosition());
            m_balls[0]->SetVelocity(location, sf::Mouse::getPosition(window));
            flag = 0;
            m_attempts++;
        }
        //else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && flag == 0)
        //{
        //    initial = sf::Mouse::getPosition();
        //    flag = 1;
        //}
        for (int i = 0; i < m_balls.size(); i++)
        {
            if (m_balls[i]->GetPosition().x <= 40 || m_balls[i]->GetPosition().x + 40 >= 960)
            {
                m_balls[i]->Bounce(0);
            }
            if (m_balls[i]->GetPosition().y <= 40 || m_balls[i]->GetPosition().y + 40 >= 585)
            {
                m_balls[i]->Bounce(1);
            }
        }
        Collision();
        for (Ball* ball : m_balls)
        {
            ball->Move();
        }
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
    //std::vector <Ball*> 
    for (int x = 0; x < m_balls.size(); x++)
    {
        sf::Vector2f cuePosition = m_balls[x]->GetPosition() - sf::Vector2f(20, 20);
        sf::Vector2f cueVelocity{ m_balls[x]->GetVelocity(0),m_balls[x]->GetVelocity(1) };
        float VLength = sqrt(pow(cueVelocity.x, 2) + pow(cueVelocity.y, 2));//length of Velocity
        int radius{ 20 };
        for (int i = 0; i < m_balls.size(); i++)
        {
            float distance = sqrt(pow(m_balls[x]->GetPosition().x - m_balls[i]->GetPosition().x, 2) + pow(m_balls[x]->GetPosition().y - m_balls[i]->GetPosition().y, 2));
            if (x == i);
            else
            {
                if ((abs(cueVelocity.x) > 0.0001f || abs(cueVelocity.y) > 0.0001f) && (abs(m_balls[i]->GetVelocity(1)) > 0.0001f || abs(m_balls[i]->GetVelocity(0)) > 0.0001f))
                {
                    MovingColision(m_balls[x], m_balls[i]);
                }
                else
                {
                    sf::Vector2f ballPosition = m_balls[i]->GetPosition() - sf::Vector2f(20, 20);
                    sf::Vector2f A{ ballPosition.x- cuePosition.x , ballPosition.y - cuePosition.y }; //distance vector between the balls
                    float ALength = sqrt(pow(A.x, 2) + pow(A.y, 2)); // length of A
                    float cosa = CosOfAngle(A, cueVelocity);// Dot Product of V and A
                    float alpha = acos(cosa);
                    float d = sin(alpha) * ALength; //Length to velocity at moment of collision
                    if (d <= radius * 2)
                    {
                        float e = sqrt(pow(radius * 2, 2) - pow(d, 2)); //distance from d at moment of collision
                        float CollisionDistance = cosa * ALength - e; // how far until collision
                        if (CollisionDistance >= 0 && CollisionDistance<=sqrt(pow(m_balls[x]->GetVelocity(0),2)+ pow(m_balls[x]->GetVelocity(1), 2)))
                        {
                            m_Colissions++;
                            sf::Vector2f velocity{ m_balls[x]->GetVelocity(0),m_balls[x]->GetVelocity(1) };// velocity of cue ball
                            float length = sqrt(pow(cuePosition.x - ballPosition.x, 2) + pow(cuePosition.y - ballPosition.y, 2)); // s2-s1 length
                            sf::Vector2f Fd{ (ballPosition.x - cuePosition.x) / length,(ballPosition.y - cuePosition.y) / length }; // force direction calculation
                            //float cosA = ((Fd.x * velocity.x) + (Fd.y * velocity.y)) / sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)); // cos alpha of angle between ball 1 and 2
                            float V2X = cosa * sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) * Fd.x;
                            float V2Y = cosa * sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) * Fd.y;
                            sf::Vector2f V2{ V2X,V2Y };
                            m_balls[i]->SetVelocityCollision(V2);
                            sf::Vector2f V1{ velocity - V2 };
                            m_balls[x]->SetVelocityCollision(V1);
                        }
                    }
                }
            }
        }
    }
}

void Game::MovingColision(Ball* ball1,Ball* ball2)
{
    float xp = ball1->GetPosition().x - ball2->GetPosition().x;
    float yp = ball1->GetPosition().y - ball2->GetPosition().y;
    float xv = ball1->GetVelocity(0) - ball2->GetVelocity(0);
    float yv = ball1->GetVelocity(1) - ball2->GetVelocity(1);
    float a = (pow(xv, 2)) + (pow(yv, 2));
    float b = (2 * xp * xv) + (2 * yp * yv);
    float c = ((pow(xp, 2)) + (pow(yp, 2))) - (pow(40, 2));
    float t1 = (-b + sqrt((pow(b, 2)) - (4 * a * c))) / (2 * a);
    float t2 = (-b - sqrt((pow(b, 2)) - (4 * a * c))) / (2 * a);
    if ((t1 > 0 && t1 < 1) || (t2>0 && t2 < 1))
    {
        m_Colissions++;
        sf::Vector2f S1 = ball1->GetPosition() + sf::Vector2f(20, 20);
        sf::Vector2f S2 = ball2->GetPosition() + sf::Vector2f(20, 20);

        float cosA = CosOfAngle((S2 - S1), sf::Vector2f{ ball1->GetVelocity(0),ball1->GetVelocity(1) })*sqrt(pow(ball1->GetVelocity(0), 2) + pow(ball1->GetVelocity(1), 2));
        float cosB = CosOfAngle((S1 - S2), sf::Vector2f{ ball2->GetVelocity(0),ball2->GetVelocity(1) }) * sqrt(pow(ball2->GetVelocity(0), 2) + pow(ball2->GetVelocity(1), 2));

        float division=sqrt(pow(S2.x - S1.x, 2) + pow(S2.y - S1.y, 2));
        sf::Vector2f FD1{ (S2.x - S1.x) / (division),(S2.y - S1.y) / (division) };
        sf::Vector2f FD2{ -FD1 };
        float v1length = sqrt(pow(ball1->GetVelocity(0), 2) + pow(ball1->GetVelocity(1), 2));
        float v2length = sqrt(pow(ball2->GetVelocity(0), 2) + pow(ball2->GetVelocity(1), 2));
        sf::Vector2f F12{ cosA * v1length * FD1.x,cosA * v1length * FD1.y };
        sf::Vector2f F21{ cosB * v2length * FD2.x,cosB * v2length * FD2.y };
        sf::Vector2f V2F{ (ball2->GetVelocity(0) + F12.x) - F21.x,(ball2->GetVelocity(1) + F12.y) - F21.y };
        sf::Vector2f V1F{ (ball1->GetVelocity(0) + ball2->GetVelocity(0)) - V2F.x,(ball1->GetVelocity(1) + ball2->GetVelocity(1)) - V2F.y };
        ball1->SetVelocityCollision(V1F);
        ball2->SetVelocityCollision(V2F);
    }
}
float Game::CosOfAngle(sf::Vector2f A, sf::Vector2f B)
{
    float ALength = sqrt(pow(A.x, 2) + pow(A.y, 2));
    float BLength = sqrt(pow(B.x, 2) + pow(B.y, 2));
    float answer = ((A.x * B.x) + (A.y * B.y)) / (ALength * BLength);
    return answer;
}