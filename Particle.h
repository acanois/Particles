//
// Created by David Richter on 9/27/25.
//

#pragma once

#include "raylib.h"
#include "raymath.h"

#include "AppConfig.h"

class Particle
{
public:
    Particle(Vector2 position,
             Vector2 velocity,
             Vector2 acceleration,
             Color color,
             float alpha,
             float size,
             float mass
    );

    ~Particle() = default;

    Particle(const Particle& other) = default;

    Particle& operator=(const Particle& other) = default;

    Particle(Particle&& other) noexcept = default;

    Particle& operator=(Particle&& other) noexcept = default;
    
    void update();

    void draw() const;

    void applyForce(Vector2 force);

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
    AppConfig& cfg = AppConfig::getInstance();

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
