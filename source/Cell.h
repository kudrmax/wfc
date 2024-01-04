#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>


struct Cell {
    Cell() = default;
    Cell(sf::Vector2f pos) {
        m_body.setSize({ BLOCK_SIZE, BLOCK_SIZE });
        m_body.setOrigin(m_body.getSize() / 2.0f);
        m_body.setPosition(pos);
    }
    void set_texture() {
        std::string texture_path;
        if (m_sides.size() <= 1)
            texture_path = "without.png";
        else {
            switch (m_sides[0]) {
                case LEFT:
                    texture_path = "left.png";
                case UP:
                    texture_path = "up.png";
                case RIGHT:
                    texture_path = "right.png";
                case DOWN:
                    texture_path = "down.png";
                case BLANK:
                    texture_path = "blank.png";
            }
        }
        m_texture.loadFromFile(texture_path);
        m_body.setTexture(&m_texture);
    }
    void update() {
        if (!m_font.loadFromFile("PixelFont.ttf"))
            throw std::runtime_error("No such file in directory");
        m_text.setFont(m_font);
        m_text.setString(std::to_string(m_sides.size()));
        m_text.setCharacterSize(100);
        auto textRect = m_text.getLocalBounds();
        m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        m_text.setPosition(m_body.getPosition());
        m_text.setFillColor(sf::Color::White);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(4);
    }
    void draw_into(sf::RenderWindow& window) const {
        window.draw(m_body);
        window.draw(m_text);
    };
    enum SIDE {
        BLANK, LEFT, UP, RIGHT, DOWN
    };
//    std::vector<SIDE> m_sides = { DOWN };
    std::vector<SIDE> m_sides = { BLANK, LEFT, UP, RIGHT, DOWN };
    sf::RectangleShape m_body;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_text;
};