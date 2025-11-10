#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
constexpr float PI = 3.141596;

float accel(float* pos, float* coeff, const int &size, const float &dt)
{
    float a = 0;
    for(int i = 0; i < size; i++)
    {
        pos[i] * coeff[i];
    }

    return a/ (dt*dt);
}

void add_to_list(float* data, const int &size, const float &x)
{
    for(int i = 0; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    data[size-1] = x;

}
void add_to_list(sf::Vector2f* data, const int &size, const sf::Vector2f &x)
{
    for(int i = 0; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    data[size-1] = x;

}



sf::Vector2f f(const float& theta1, const float& theta2, const float& v1, const float& v2, const float& dt, const float& m1, const float& m2, const float& r1, const float& r2, const float& g)
{
    sf::Vector2f result;
    result.x = -(( v1- v2) * m2 * r1 * r2 *  v2 * sinf( theta2 -  theta1) - m2* r1 * r2 *  v1 *  v2 * sinf( theta2 -  theta1) + (m1 + m2) * r1 * g * sinf( theta1));
    result.x += ( v2- v1) * m2*r1*r1* v1 * cosf( theta2- theta1) * sinf( theta2- theta1) + m2 * r1 * r1 *  v1 *  v2 * cosf( theta2-  theta1)* sinf( theta2- theta1) + m2 * r1 * g * cosf( theta2-  theta1) * sinf( theta2);
    result.x /=  ((m1+m2 * (1 - pow(cosf( theta2 -  theta1),2))) * r1 * r1);

    result.y = 1/(m2*r2*r2) *(-m2*r1 *r2*result.x*cosf( theta2 -  theta1) + ( v2 - v1) * m2 * r1 * r2 *  v1 * sinf( theta2 -  theta1) - m2 * r1 * r2 *  v1 *  v2 * sinf( theta2 -  theta1) - m2 * r2 * g * sinf( theta2)); 
    return result;
}
int main()
{
    sf::RenderWindow window(sf::VideoMode{1920, 1080}, "Pendulum");

    sf::CircleShape point1(2.f);
    point1.setFillColor(sf::Color::Magenta);
    point1.setOrigin(2,2);

    sf::CircleShape point2(2.f);
    point2.setFillColor(sf::Color::Yellow);
    point2.setOrigin(2,2);

    sf::Vertex line1[] = 
    {
        sf::Vertex(sf::Vector2f()),
        sf::Vertex(sf::Vector2f())
    };
    line1[0].color = sf::Color::Magenta;
    line1[1].color = sf::Color::Magenta;
    
    sf::Vertex line2[] = 
    {
        sf::Vertex(sf::Vector2f()),
        sf::Vertex(sf::Vector2f())
    };
    line2[0].color = sf::Color::Yellow;
    line2[1].color = sf::Color::Yellow;
    sf::Vector2f O = {1920/2 , 500};

    sf::CircleShape masse1(20.f);
    masse1.setOrigin(20.f, 20.f);
    masse1.setFillColor(sf::Color::Red);

    sf::CircleShape masse2(20.f);
    masse2.setOrigin(20.f, 20.f);
    masse2.setFillColor(sf::Color::Red);



    float l1 = 200;
    float l2 = 200;

    sf::RectangleShape barre1({4, l1});
    barre1.setFillColor(sf::Color::Black);
    barre1.setOrigin({2, 0});
    barre1.setPosition(O);

    sf::RectangleShape barre2({4, l2});
    barre2.setFillColor(sf::Color::Black);
    barre2.setOrigin({2, 0});
    barre2.setPosition(O);

    float theta1 = PI/2;
    float theta2 = PI/2;

    float v1 = 0;
    float v2 = 0;

    masse1.setPosition(O.x - l1 * std::sinf(theta1), O.y + l1 * std::cosf(theta1));
    masse2.setPosition(masse1.getPosition().x - l2 * std::sinf(theta2), masse1.getPosition().y + l2 * std::cosf(theta2));
    
    float data1[100] = {0};
    float data2[100] = {0};
    sf::Vector2f data3[100];
    sf::Vector2f data4[1000];
    for(int i = 0; i < 1000; i++)
    {
        //data3[i] = {masse1.getPosition()};
        data4[i] = {masse2.getPosition()};
    }

    float m1 = 0.1;    // (kg)
    float m2 = 0.1;    // (kg)
    float r1 = 0.20; // (m)
    float r2 = 0.20; // (m)
    float g = 2;      // (m/s²)
    
    clock_t time = std::clock();
    float dt = 0;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        clock_t n_time = std::clock();
        dt = float(n_time - time)/CLOCKS_PER_SEC;

        if(dt > 1.f/60.f)
        {
            time = n_time;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                theta1 = std::atan2f(-sf::Mouse::getPosition(window).x + O.x,  sf::Mouse::getPosition(window).y - O.y);
                v1 = 0;
                v2 = 0;
            }else
            {
            
                sf::Vector2f k1 = f(theta1, theta2, v1, v2, dt, m1, m2, r1, r2, g);
                sf::Vector2f k2 = f(theta1 + dt/2 * v1, theta2 + dt/2 * v2, v1 + dt/2 * k1.x, v2+ dt/2 * k1.y, dt, m1, m2, r1, r2, g);
                sf::Vector2f k3 = f(theta1 + dt/2 * v1 + dt*dt/4 * k1.x, theta2 + dt/2 * v2+ dt*dt/4 * k1.y, v1 + dt/2 * k2.x, v2+ dt/2 * k2.y, dt, m1, m2, r1, r2, g);
                sf::Vector2f k4 = f(theta1 + dt * v1 + dt*dt/2 * k2.x, theta2 + dt * v2+ dt*dt/2 * k2.y, v1 + dt * k3.x, v2+ dt * k3.y, dt, m1, m2, r1, r2, g);

                theta1 += dt * v1 + dt*dt/6 *(k1.x + k2.x + k3.x);
                v1 += dt/6 * (k1.x + 2 * k2.x + 2 * k3.x + k4.x);

                theta2 += dt * v2 + dt*dt/6 *(k1.y + k2.y + k3.y);
                v2 += dt/6 * (k1.y + 2 * k2.y + 2 * k3.y + k4.y);

            }
            masse1.setPosition(O.x - l1 * std::sinf(theta1), O.y + l1 * std::cosf(theta1));
            barre1.setRotation(180 / PI * theta1);

            barre2.setPosition(masse1.getPosition());
            barre2.setRotation(180 / PI * theta2);
            masse2.setPosition(masse1.getPosition().x - l2 * std::sinf(theta2), masse1.getPosition().y + l2 * std::cosf(theta2));

            if(theta1 > PI)
                theta1 -= 2*PI;
            else if(theta1 < -PI)
                theta1 += 2*PI;
            if(theta2 > PI)
                theta2 -= 2*PI;
            else if(theta2 < -PI)
                theta2 += 2*PI;
            //add_to_list(data1, 100, theta1);
            //add_to_list(data2, 100, theta2);
            //add_to_list(data3, 100, masse1.getPosition());
            add_to_list(data4, 1000, masse2.getPosition());
        }
        
       
        window.clear({50,50,50,100});


        for(int i = 0; i < 999; i++)
        {
            int dx = 500 / 100;
            //point1.setPosition({float(i) * dx, 450 + 200/(2*PI) * data1[i]});
            //point1.setPosition(data3[i]);
            // line1[0].position = {data3[i]};
            // line1[1].position = {data3[i + 1]};
            // window.draw(line1, 2, sf::Lines);
            //point2.setPosition({float(i) * dx, 450 + 200/(2*PI) * data2[i]});
            line2[0].position = {data4[i]};
            line2[1].position = {data4[i + 1]};
            line2[0].color = sf::Color(255,255,255, std::min(255.f, 2000.f/(1000 - i)));
            line2[1].color = sf::Color(255,255,255, std::min(255.f,2000.f/(1000 - i- 1)));

            window.draw(line2, 2, sf::Lines);
        }
        window.draw(barre1);
        window.draw(barre2);
        window.draw(masse1);
        window.draw(masse2);
        window.display();
    }
    return 0;
}