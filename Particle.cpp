//
// Created by David Richter on 10/27/25.
//

#include "Particle.h"

Particle::Particle(const Vector2 position,
         const Vector2 velocity,
         const Vector2 acceleration,
         const Color color,
         const float alpha,
         const float size,
         const float mass
) : position(position),
    velocity(velocity),
    acceleration(acceleration),
    color(color),
    alpha(alpha),
    size(size),
    lifespan(1.0f),
    mass(mass),
    active(true)
{
}

void Particle::update()
{
    if (active)
    {
        const auto distanceToCenter = Vector2Subtract(
            position,
            Vector2 {
                static_cast<float>(cfg.getConfig()["screenWidth"]) / 2.0f,
                static_cast<float>(cfg.getConfig()["screenHeight"]) / 2.0f
            }
        );
        const auto distanceMag = Vector2Length(distanceToCenter);
        const auto colorShift = Remap(
            distanceMag, // Input
            static_cast<float>(cfg.getConfig()["screenWidth"]) * 0.6f, // Input min
            0.0f, // Input max
            0.0f, // Output min
            255.0f // Output max
        );

        velocity = Vector2Add(velocity, acceleration);
        position = Vector2Add(position, velocity);

        acceleration *= 0.0f;

        color.g = static_cast<unsigned char>(colorShift);
        color.r = static_cast<unsigned char>(colorShift);
    }
}

void Particle::draw() const
{
    if (active)
    {
        DrawCircle(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            size,
            color
        );
    }
}

void Particle::applyForce(const Vector2 force)
{
    const Vector2 f = Vector2Divide(force, Vector2 { mass, mass });
    acceleration = Vector2Add(acceleration, f);
}