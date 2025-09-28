//
// Created by David Richter on 9/27/25.
//

#pragma once
#include "raylib.h"
#include "raymath.h"

class Particle
{
public:
    Particle(Vector2 position,
             Vector2 velocity,
             Vector2 acceleration,
             Color color,
             float alpha,
             float size,
             float rotation,
             bool active
    ) : position(position),
        velocity(velocity),
        acceleration(acceleration),
        color(color),
        alpha(alpha),
        size(size),
        rotation(rotation),
        active(active)
    {
    }

    ~Particle() = default;

    Particle(const Particle& other) = default;

    Particle& operator=(const Particle& other) = default;

    Particle(Particle&& other) noexcept = default;

    Particle& operator=(Particle&& other) noexcept = default;


    void update(float gravity)
    {
        if (active)
        {
            velocity = Vector2Add(velocity, acceleration);
            position = Vector2Add(position, velocity);
            acceleration *= 0.0f;
            // position.y += gravity / 2;
            color.a -= 2;

            if (color.a <= 0) active = false;

            // rotation += 2.0f;
        }
    }

    void draw()
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

    [[nodiscard]] bool alive() const
    {
        return color.a > 0;
    }

private:
    Vector2 position { 0.0f, 0.0f };
    Vector2 velocity { 0.0f };
    Vector2 acceleration { 0.0f };

    Color color {};

    float alpha { 0.0f };
    float size { 0.0f };
    float rotation { 0.0f };


    bool active { true };
};
