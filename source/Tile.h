#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(const std::string&& texture_path,
         const std::vector<size_t>&& eds,
         size_t rotation);
    void print() {
        std::cout << "{ ";
        for (auto edge : edges) {
            std::cout << edge << " ";
        }
        std::cout << "}\n";
    }
    std::string print_sfml(){
        if (edges[0] == 0 && edges[0] == edges[1])
            return "B";
        int n;
        for (int i = 0; i < 4; i++)
            if (edges[i] == 0) {
                n = i;
                break;
            }
        switch (n) {
            case 0:
                return "D";
            case 1:
                return "L";
            case 2:
                return "U";
            case 3:
                return "R";
            default:
                return "ERROR";
        }
        return "ERROR";
    }
public:
    std::vector<size_t> edges;
    std::string texture_str;
    sf::Sprite sprite;
    size_t rotation = 0;
};
