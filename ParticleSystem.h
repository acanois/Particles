//
// Created by David Richter on 9/27/25.
//

#pragma once

#include <vector>

#include "Particle.h"

class ParticleSystem
{
public:
    ParticleSystem(Vector2 position)
        : m_position(position)
    {
    }

    void addParticle(Particle particle)
    {
        m_particles.push_back(particle);
    }

    void run()
    {
        for (auto&& particle: m_particles)
        {
            particle->update(3.0f);
            particle->draw();

            if (!particle->alive())
                m_particles.erase(
                    std::ranges::remove(m_particles, particle)
                    .begin()
                );
        }
    }

private:
    Vector2 m_position;

    std::vector<std::unique_ptr<Particle>> m_particles;
};
