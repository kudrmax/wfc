#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <random>
#include "random.h"


struct Cell {
    Cell() = default;
    Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles);
    void markCollapsed();
    void updateText();
    void drawInto(sf::RenderWindow& window) const;
    void collapseCell();
public:
    sf::RectangleShape m_body;
    bool is_collapsed = false;
    std::vector<Tile> m_possible_tiles;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_text;
};