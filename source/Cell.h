#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <random>
#include "random.h"


struct Cell {
    Cell() = default;
    Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles) : m_possible_tiles(tiles) {
        m_body.setSize({ BLOCK_SIZE, BLOCK_SIZE });
        m_body.setOrigin(m_body.getSize() / 2.0f);
        m_body.setPosition(pos);
    }
    void update() {
        update_text();
        if (!is_collapsed && m_possible_tiles.size() == 1) {
            m_texture.loadFromFile(m_possible_tiles[0].texture_str);
            m_body.setTexture(&m_texture);
            m_body.rotate(m_possible_tiles[0].rotation * 90);
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
    void specify_cell() {
        auto one_tile = *select_randomly(m_possible_tiles.begin(), m_possible_tiles.end());
        m_possible_tiles.clear();
        m_possible_tiles = { one_tile };
    };
public:
    sf::RectangleShape m_body;
    bool is_collapsed = false;
    std::vector<Tile> m_possible_tiles;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_text;
};