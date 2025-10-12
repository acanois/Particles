//
// Created by David Richter on 10/5/25.
//

#include <math.h>

#include "raylib.h"
#include "raymath.h"
#include "Particle.h"

class Attractor
{
public:
    Attractor(Vector2 position, float mass)
        : position(position),
          mass(mass)
    {
    }

    Vector2 attract(const Particle& particle)
    {
        const auto force = Vector2Subtract(position, particle.getPosition());
        const auto magnitude = Vector2Length(force);
        const auto distance = Clamp(magnitude, 5, 25);

        const auto strength = (G * mass * particle.getMass()) / powf(distance, 2.0f);

        return Vector2Scale(force, strength);
    }

private:
    Vector2 position;
    float mass;

    static constexpr float G = 0.5f;
};
