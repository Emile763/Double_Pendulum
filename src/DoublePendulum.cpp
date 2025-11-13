#include "DoublePendulum.hpp"
#include <math.h>
#include <iostream>

constexpr float mass_radius = 20.f;
constexpr float rod_scale = 200.f;
constexpr float rod_width = 4.f;

void add_to_list(sf::Vector2f *data, const int &size, const sf::Vector2f &x)
{
    for (int i = 0; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    data[size - 1] = x;
}


DoublePendulum::DoublePendulum(const float &mass1, const float &mass2, const float &radius_1, const float &radius_2, const float &gravity,
                               const float &angle1, const float &angle2, const float &angular_speed1, const float &angular_speed2)
    : m_mass1(mass1), m_mass2(mass2), m_radius1(radius_1), m_radius2(radius_2), m_gravity(gravity),
      m_angle1(angle1), m_angle2(angle2), m_angular_speed1(angular_speed1), m_angular_speed2(angular_speed2),
      m_origin{0, 0},
      m_mass1_shape(mass_radius), m_mass2_shape(mass_radius),
      m_rod1({rod_width, rod_scale * radius_1}), m_rod2({rod_width, rod_scale * radius_2})
{
    m_mass1_shape.setOrigin({mass_radius, mass_radius});
    m_mass2_shape.setOrigin({mass_radius, mass_radius});
    m_mass1_shape.setFillColor(sf::Color::Red);
    m_mass2_shape.setFillColor(sf::Color::Red);

    m_rod1.setOrigin({rod_width / 2.f, 0.f});
    m_rod2.setOrigin({rod_width / 2.f, 0.f});
    m_rod1.setFillColor(sf::Color::Black);
    m_rod2.setFillColor(sf::Color::Black);
    
    updateDrawing();
}


void DoublePendulum::setOrigin(sf::Vector2f origin)
{
    m_origin = origin;
    m_rod1.setPosition(m_origin);
    updateDrawing();

}

void DoublePendulum::setAngle1(const float &angle)
{
    m_angle1 = angle;
}

void DoublePendulum::setAngle2(const float &angle)
{
    m_angle2 = angle;
}

void DoublePendulum::setAngularSpeed1(const float &speed)
{
    m_angular_speed1 = speed;
}

void DoublePendulum::setAngularSpeed2(const float &speed)
{
    m_angular_speed2 = speed;
}

float DoublePendulum::getAngle1()
{
    return m_angle1;
}

float DoublePendulum::getAngle2()
{
    return m_angle2;
}

float DoublePendulum::getAngularSpeed1()
{
    return m_angular_speed1;
}

float DoublePendulum::getAngularSpeed2()
{
    return m_angular_speed2;
}

sf::Vector2f DoublePendulum::getAngularAcceleration() const
{
    return getAngularAcceleration(m_angle1, m_angle2, m_angular_speed1, m_angular_speed2);
}

sf::Vector2f DoublePendulum::getAngularAcceleration(const float &angle1, const float &angle2, const float &angular_speed1, const float &angular_speed2) const
{
    sf::Vector2f result;
    float denom = 2.f * m_mass1 + m_mass2 - m_mass2 * cosf(2.f * (angle2 - angle1));

    result.x = -(2.f * m_mass1 + m_mass2) * m_gravity * sinf(angle1);
    result.x += m_mass2 * m_gravity * sinf(2.f * angle2 - angle1);
    result.x += 2.f * m_mass2 * sinf(angle2 - angle1) * (m_radius2 * angular_speed2 * angular_speed2 + m_radius1 * angular_speed1 * angular_speed1 * cosf(angle2 - angle1));
    result.x /= (denom * m_radius1);

    result.y = -(m_mass1 + m_mass2) * m_gravity * cosf(angle1);
    result.y -= (m_mass1 + m_mass2) * m_radius1 * angular_speed1 * angular_speed1;
    result.y -= m_mass2 * m_radius2 * angular_speed2 * angular_speed2 * cosf(angle2 - angle1);
    result.y *= 2.f * sinf(angle2 - angle1);
    result.y /= (denom * m_radius2);

    return result;
}

void DoublePendulum::integrate(const float &dt)
{
    // Runge Kutta
    sf::Vector2f k1 = getAngularAcceleration(m_angle1,
                                             m_angle2,
                                             m_angular_speed1,
                                             m_angular_speed2);

    sf::Vector2f k2 = getAngularAcceleration(m_angle1 + dt / 2.f * m_angular_speed1,
                                             m_angle2 + dt / 2.f * m_angular_speed2,
                                             m_angular_speed1 + dt / 2.f * k1.x,
                                             m_angular_speed2 + dt / 2.f * k1.y);

    sf::Vector2f k3 = getAngularAcceleration(m_angle1 + dt / 2.f * m_angular_speed1 + dt * dt / 4 * k1.x,
                                             m_angle2 + dt / 2.f * m_angular_speed2 + dt * dt / 4 * k1.y,
                                             m_angular_speed1 + dt / 2.f * k2.x,
                                             m_angular_speed2 + dt / 2.f * k2.y);

    sf::Vector2f k4 = getAngularAcceleration(m_angle1 + dt * m_angular_speed1 + dt * dt / 2 * k2.x,
                                             m_angle2 + dt * m_angular_speed2 + dt * dt / 2 * k2.y,
                                             m_angular_speed1 + dt * k3.x,
                                             m_angular_speed2 + dt * k3.y);

    m_angle1 += dt * m_angular_speed1 + dt * dt / 6.f * (k1.x + k2.x + k3.x);
    m_angle2 += dt * m_angular_speed2 + dt * dt / 6.f * (k1.y + k2.y + k3.y);
    m_angular_speed1 += dt / 6.f * (k1.x + 2 * k2.x + 2 * k3.x + k4.x);
    m_angular_speed2 += dt / 6.f * (k1.y + 2 * k2.y + 2 * k3.y + k4.y);

    while (m_angle1 > PI)
        m_angle1 -= 2 * PI;
    while (m_angle1 < -PI)
        m_angle1 += 2 * PI;
    while (m_angle2 > PI)
        m_angle2 -= 2 * PI;
    while (m_angle2 < -PI)
        m_angle2 += 2 * PI;
}

void DoublePendulum::updateDrawing()
{
    m_rod1.setRotation(sf::radians(-m_angle1));
    m_mass1_shape.setPosition({m_origin.x + m_rod1.getSize().y * std::sinf(m_angle1), m_origin.y + m_rod1.getSize().y * std::cosf(m_angle1)});
    m_rod2.setPosition(m_mass1_shape.getPosition());
    m_rod2.setRotation(sf::radians(-m_angle2));
    m_mass2_shape.setPosition({m_mass1_shape.getPosition().x + m_rod2.getSize().y * std::sinf(m_angle2), m_mass1_shape.getPosition().y + m_rod2.getSize().y * std::cosf(m_angle2)});
    add_to_list(m_second_weight_trace.data(), trace_size, m_mass2_shape.getPosition());

}

void DoublePendulum::resetTrace()
{
    m_second_weight_trace.fill(m_mass2_shape.getPosition());
}

void DoublePendulum::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    sf::Vertex line[2];
    for (int i = 0; i < trace_size - 1; i++)
    {
        line[0].color = sf::Color(255, 255, 255, std::min(255.f, 2000.f / (trace_size - i)));
        line[1].color = sf::Color(255, 255, 255, std::min(255.f, 2000.f / (trace_size - i - 1)));

        line[0].position = {m_second_weight_trace[i]};
        line[1].position = {m_second_weight_trace[i + 1]};

        target.draw(line, 2, sf::PrimitiveType::Lines);
    }
    target.draw(m_rod1);
    target.draw(m_rod2);
    target.draw(m_mass1_shape);
    target.draw(m_mass2_shape);
}
