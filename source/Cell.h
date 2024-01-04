#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"


struct Cell {
    Cell() = default;
    Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles) {
        m_body.setSize({ BLOCK_SIZE, BLOCK_SIZE });
        m_body.setOrigin(m_body.getSize() / 2.0f);
        m_body.setPosition(pos);
        m_body.setFillColor(sf::Color::Black);
        m_possible_tiles = tiles;
    }
    void update() {
        update_text();
        if (m_possible_tiles.size() == 1) {
//            m_body.setTexture("3.png");
            m_body.setTexture(m_possible_tiles[0].get_texture());
            is_collapsed = true;
        }
    }
    void update_text() {
        if (!m_font.loadFromFile("PixelFont.ttf"))
            throw std::runtime_error("No such file in directory");
        m_text.setFont(m_font);
        m_text.setString(std::to_string(is_collapsed) + "\n" + std::to_string(m_possible_tiles.size()));
        m_text.setCharacterSize(60);
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
    sf::RectangleShape m_body;
    bool is_collapsed = false;
    std::vector<Tile> m_possible_tiles;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_text;
};