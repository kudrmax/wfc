#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(const std::string&& texture_path,
         const std::vector<size_t>&& eds,
         size_t rotation);
public:
    std::vector<size_t> edges;
    std::string texture_str;
    sf::Sprite sprite;
    size_t rotation;
};
