//
// Created by David Richter on 9/27/25.
//

#pragma once
#include "raylib.h"

class Particle
{
public:
    Particle(Vector2 position,
             Color color,
             float alpha,
             float size,
             float rotation,
             float velocity,
             float acceleration,
             bool active
    ) : m_position(position),
        m_color(color),
        m_alpha(alpha),
        m_size(size),
        m_rotation(rotation),
        m_velocity(velocity),
        m_acceleration(acceleration),
        m_active(active),
        m_texture(LoadTexture(ASSETS_PATH "particle_texture.png"))
    {
    }

    ~Particle()
    {
        UnloadTexture(m_texture);
    }

    void update()
    {
    }

    void draw()
    {
        auto gravity = 3.0f;

        if (m_active)
        {
            m_position.y += gravity / 2;
            m_alpha -= 0.005f;

            if (m_alpha <= 0.0f) m_active = false;

            m_rotation += 2.0f;
        }
        if (m_active)
        {
            DrawTexturePro(
                m_texture,
                (Rectangle) { 0.0f, 0.0f, (float) m_texture.width, (float) m_texture.height },
                (Rectangle) {
                    m_position.x,
                    m_position.y,
                    m_texture.width * m_size,
                    m_texture.height * m_size
                },
                (Vector2) {
                    (float) (m_texture.width * m_size / 2.0f),
                    (float) (m_texture.height * m_size / 2.0f)
                }, m_rotation,
                Fade(m_color, m_alpha));
        }
    }

private:
    Vector2 m_position;

    Texture2D m_texture;

    Color m_color;

    float m_alpha;
    float m_size;
    float m_rotation;
    float m_velocity;
    float m_acceleration;

    bool m_active;
};
