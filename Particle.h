//
// Created by David Richter on 9/27/25.
//

#pragma once
#include "raylib.h"
#include "raymath.h"

class Particle
{
public:
    Particle(const Vector2 position,
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
        mass(mass),
        active(true),
        lifespan(1.0f)
    {
    }

    ~Particle() = default;

    Particle(const Particle& other) = default;

    Particle& operator=(const Particle& other) = default;

    Particle(Particle&& other) noexcept = default;

    Particle& operator=(Particle&& other) noexcept = default;


    void update()
    {
        if (active)
        {
            auto distanceToCenter = Vector2Subtract(
                position,
                Vector2 { 1280.0f / 2.0f, 720.0f / 2.0f }
            );
            auto distanceMag = Vector2Length(distanceToCenter);
            auto colorShift = Remap(distanceMag, 0, (1280.0f / 2.0f), 50.0f, 255.0f);
            velocity = Vector2Add(velocity, acceleration);
            position = Vector2Add(position, velocity);
            acceleration *= 0.0f;
            color.g = static_cast<unsigned char>(colorShift);
            color.b = static_cast<unsigned char>(colorShift);
            // lifespan -= 1.0f / (255.0f * 5.0f);
            //
            // if (lifespan <= 0)
            // {
            //     active = false;
            // }
        }
    }

    void draw() const
    {
        if (active)
        {
            DrawCircle(
                static_cast<int>(position.x),
                static_cast<int>(position.y),
                2.0f,
                color
            );
        }
    }

    void applyForce(Vector2 force)
    {
        Vector2 f = Vector2Divide(force, Vector2 { mass, mass });
        acceleration = Vector2Add(acceleration, f);
    }

    [[nodiscard]] Vector2 getPosition() const
    {
        return position;
    }

    [[nodiscard]] bool alive() const
    {
        return lifespan > 0;
    }

    [[nodiscard]] float getMass() const
    {
        return mass;
    }

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Color color;

    float alpha;
    float size;
    float lifespan;
    float mass;

    bool active;
};
