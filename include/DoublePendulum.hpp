#pragma once
#include <SFML/Graphics.hpp>
#include <array>

constexpr int trace_size = 1000;
constexpr float PI = 3.141596;

class DoublePendulum : public sf::Drawable
{
private:
    // Physics
    float m_mass1, m_mass2;
    float m_radius1, m_radius2;
    float m_gravity;

    float m_angle1, m_angle2;
    float m_angular_speed1, m_angular_speed2;

    // Drawing
    sf::Vector2f m_origin;
    sf::CircleShape m_mass1_shape, m_mass2_shape;
    sf::RectangleShape m_rod1, m_rod2;

    std::array<sf::Vector2f, trace_size> m_second_weight_trace;

public:
    /// @brief Create a double pendulum with the given physical characteristics and initial conditions
    /// @param mass1 mass of the first weight (kg)
    /// @param mass2 mass of the second weight (kg)
    /// @param radius_1 size of the first rod (m)
    /// @param radius_2  size of the second rod (m)
    /// @param gravity gravitational acceleration (m/s²)
    /// @param angle1 angle of the first weight (rad)
    /// @param angle2 angle of the second weight (rad)
    /// @param angular_speed1 angular speed of the first weight (rad/s)
    /// @param angular_speed2 angular speed of the second weight (rad/s)
    DoublePendulum(const float &mass1, const float &mass2, const float &radius_1, const float &radius_2, const float &gravity,
                   const float &angle1 = 0, const float &angle2 = 0, const float &angular_speed1 = 0, const float &angular_speed2 = 0);


    /// @brief Set the origin of the pendulum
    /// @param origin (pixel, pixel)
    void setOrigin(sf::Vector2f origin);

    void setAngle1(const float &angle);
    void setAngle2(const float &angle);
    void setAngularSpeed1(const float &speed);
    void setAngularSpeed2(const float &speed);

    float getAngle1();
    float getAngle2();
    float getAngularSpeed1();
    float getAngularSpeed2();

    sf::Vector2f getAngularAcceleration() const;
    
    /// @brief Compute the angular accelerations of the pendulum in the given configuration 
    /// @param angle1 angle of the first weight (rad)
    /// @param angle2 angle of the second weight (rad)
    /// @param angular_speed1 angular speed of the first weight (rad/s)
    /// @param angular_speed2 angular speed of the second weight (rad/s)
    /// @return Angular acceleration of the two weights (rad/s², rad/s²)
    sf::Vector2f getAngularAcceleration(const float &angle1, const float &angle2, const float &angular_speed1, const float &angular_speed2) const;
    
    /// @brief Compute the angles and angular speeds at t + dt
    /// @param dt time step (s)
    void integrate(const float &dt);

    /// @brief Update the drawings’ positions
    void updateDrawing();
    
    /// @brief Clear the trace
    void resetTrace();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
