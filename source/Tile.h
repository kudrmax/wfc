#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(const std::string&& texture_path, const std::vector<size_t>&& edges) : edges(edges) {
        m_texture.loadFromFile(texture_path);
        m_body.setTexture(&m_texture);
    }
public:
    const sf::Texture* get_texture() { return m_body.getTexture(); }
    Tile& rotate(size_t n);
public:
    std::vector<size_t> edges;
    sf::Texture m_texture;
    sf::RectangleShape m_body;
};
