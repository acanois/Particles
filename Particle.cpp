//
// Created by David Richter on 10/27/25.
//

#include "Particle.h"

Particle::Particle(const Vector3 position,
                   const Vector3 velocity,
                   const Vector3 acceleration,
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
        const auto distanceToCenter = Vector3Subtract(
            position,
            Vector3 {
                static_cast<float>(cfg.getConfig()["screenWidth"]) / 2.0f,
                static_cast<float>(cfg.getConfig()["screenHeight"]) / 2.0f
            }
        );
        const auto distanceMag = Vector3Length(distanceToCenter);
        const auto colorShift = Remap(
            distanceMag, // Input
            static_cast<float>(cfg.getConfig()["screenWidth"]) * 0.6f, // Input min
            0.0f, // Input max
            0.0f, // Output min
            255.0f // Output max
        );

        velocity = Vector3Add(velocity, acceleration);
        position = Vector3Add(position, velocity);

        acceleration *= 0.0f;

        color.g = static_cast<unsigned char>(colorShift);
        color.r = static_cast<unsigned char>(colorShift);
    }
}

void Particle::draw() const
{
    if (active)
    {
        DrawCircle3D(
            position,
            size * 0.1f,
            Vector3 { 0.0f, 1.0f, 0.0f },
            0.0f,
            RAYWHITE
        );
    }
}

void Particle::applyForce(const Vector3 force)
{
    const Vector3 f = Vector3Divide(force, Vector3 { mass, mass, mass });
    acceleration = Vector3Add(acceleration, f);
}
