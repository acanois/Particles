//
// Created by David Richter on 9/27/25.
//

#pragma once

#include <vector>

#include "Particle.h"

class ParticleSystem
{
public:
    explicit ParticleSystem(const Vector2 position)
        : position(position)
    {
    }

    void addParticle()
    {
        auto velocity = Vector2 {
            static_cast<float>(GetRandomValue(-1000, 1000)) / 1000.0f,
            static_cast<float>(GetRandomValue(-1000, 1000)) / 1000.0f
        };
        particles.emplace_back(std::make_unique<Particle>(
            Vector2 { 1280.0f / 2.0f, 720.0f / 2.0f }, // Position
            velocity, // Velocity
            Vector2 { 0.0f, 0.0f }, // Acceleration
            Color { 255, 255, 255, 255 }, // Color
            1.0f, // Alpha
            0.5f, // Size
            0.0f, // Rotation
            true // Active
        ));
    }

    void run()
    {
        for (const auto& particle: particles)
        {
            particle->update(3.0f);
            particle->draw();
        }

        // Putting this inside the for loop would cause iterator invalidation
        std::erase_if(particles, [] (const std::unique_ptr<Particle>& particle) {
            return !particle->alive();
        });
    }

private:
    Vector2 position;
    // Texture2D texture {};

    std::vector<std::unique_ptr<Particle> > particles;
};
