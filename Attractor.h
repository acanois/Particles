//
// Created by David Richter on 10/5/25.
//

#pragma once

#include <cmath>

#include "raylib.h"
#include "raymath.h"
#include "Particle.h"

class Attractor
{
public:
    Attractor(const Vector3 position, const float mass)
        : position(position),
          mass(mass)
    {
    }

    [[nodiscard]] Vector3 attract(const Particle& particle) const
    {
        const auto force = Vector3Subtract(position, particle.getPosition());
        const auto magnitude = Vector3Length(force);
        const auto distance = Clamp(magnitude, 5, 25);

        const auto strength = G * mass * particle.getMass() / powf(distance, 2.0f);

        return Vector3Scale(force, strength);
    }

private:
    Vector3 position;
    float mass;

    static constexpr float G = 0.25f;
};
