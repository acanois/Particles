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
            static_cast<float>(GetRandomValue(33, 1000)) / 1000.0f
        };
        particles.emplace_back(std::make_unique<Particle>(
            Vector2 { position.x, position.y }, // Position
            velocity, // Velocity
            Vector2 { 0.0f, 0.0f }, // Acceleration
            Color { 255, 255, 255, 255 }, // Color
            1.0f, // Alpha
            0.5f, // Size
            true // Active
        ));
    }

    void run()
    {
        for (const auto& particle: particles)
        {
            particle->update();
            particle->draw();
        }

        // Putting this inside the for loop would cause iterator invalidation
        std::erase_if(particles, [] (const std::unique_ptr<Particle>& particle) {
            return !particle->alive();
        });
    }

    [[nodiscard]] unsigned long getNumParticles() const
    {
        std::cout << particles.size() << std::endl;
        return particles.size();
    }

private:
    Vector2 position;
    // Texture2D texture {};

    std::vector<std::unique_ptr<Particle> > particles;
};
