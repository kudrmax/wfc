#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <random>
#include "random.h"


struct Cell {
public:
    enum DIR {
        U = 0, R, D, L
    };
public:
    Cell() = default;
    Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles, std::vector<DIR>&& possible_directions);
    void markCollapsed();
    void updateText();
    void drawInto(sf::RenderWindow& window) const;
    void collapseCell();
    bool reduceEntropyCell(std::vector<size_t> possible_ids_on_dir, Cell::DIR dir_from);
public:
    std::vector<Tile> m_possible_tiles;
    bool is_collapsed = false;
    std::vector<DIR> m_possible_directions;
    sf::RectangleShape m_body;
    sf::Texture m_texture;
    sf::Font m_font;
    sf::Text m_text;
};