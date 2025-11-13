#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include <array>
#include <chrono>
#include "DoublePendulum.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Pendulum", sf::State::Windowed, settings);
    window.setVerticalSyncEnabled(true);


    const sf::Vector2f origin = {1920 / 2, 500};

    // Pendulum Properties
    const float m1 = 2.f;  // (kg)
    const float m2 = 2.f;  // (kg)
    const float r1 = 1.f;  // (m)
    const float r2 = 1.f;  // (m)
    const float g = 9.81f; // (m/s²)
    
    // Initial conditions
    const float angle1 = PI / 2.f;
    const float angle2 = PI / 2.f;
    float w1 = 0;
    float w2 = 0;
    
    DoublePendulum pendulum(m1, m2, r1, r2, g, angle1, angle2, w1, w2);
    pendulum.setOrigin(origin);
    pendulum.resetTrace();
    
    // Time
    const float DeltaT = 1.f / 60.f;
    const long long nano_DeltaT = DeltaT * 1e9;
    auto last_update = std::chrono::steady_clock::now();
    long long exceeded_time = 0;

    while (window.isOpen())
    {
        // update window
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        auto current_time = std::chrono::steady_clock::now();
        long long dt = (long long)(current_time - last_update).count() - exceeded_time;
        if (dt > 0){
            last_update = current_time;
            exceeded_time = nano_DeltaT - dt % nano_DeltaT;
        }

        // update pendulum
        while (dt > 0)
        {
            bool right_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
            bool left_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
            if (left_click || right_click )
            {
                float angle = -std::atan2f(-sf::Mouse::getPosition(window).x + origin.x, sf::Mouse::getPosition(window).y - origin.y);
                pendulum.setAngularSpeed1(0);
                pendulum.setAngularSpeed2(0);
                if(left_click)
                    pendulum.setAngle1(angle);
                if(right_click)
                    pendulum.setAngle2(angle);
            }

            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                pendulum.integrate(DeltaT);
            }

            dt -= nano_DeltaT;
        }


        // Drawing

        pendulum.updateDrawing();

        window.clear({50, 50, 50, 100});

        window.draw(pendulum);

        window.display();
    }
    return 0;
}