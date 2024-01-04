#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <execution>
#include <unordered_set>
#include <list>

const int W = 800;
const int H = 800;
const int BLOCK_SIZE = 200;
const int BLOCK_COUNT = 4;



struct Tile {
    Tile() = default;
    Tile(sf::Vector2f pos) {
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

//auto comparator_for_tails = [](const Tile& a, const Tile& b){
//    return a.m_sides.size() < b.m_sides.size();
//};
//
//struct comparator_for_tails {
//    bool operator()(const Tile& a, const Tile& b) const {
//        return a.m_sides.size() < b.m_sides.size();
//    }
//};


int main() {

    sf::RenderWindow window(sf::VideoMode(W, H), "Title");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);


    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    for (int row = 0; row < BLOCK_COUNT; row++) {
        std::vector<std::unique_ptr<Tile>> row_vec;
        auto pos_zero = sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto pos = pos_zero + sf::Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE);
            row_vec.emplace_back(std::make_unique<Tile>(pos));
        }
        tiles.emplace_back(std::move(row_vec));
    }
    for (auto& row: tiles)
        for (auto& tile: row)
            tile->set_texture();

    auto* min_tile = tiles[0][0].get();
    auto comparator_for_tails = [](const Tile& a, const Tile& b){
        return a.m_sides.size() <= b.m_sides.size();
    };
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            if (comparator_for_tails(*min_tile, *tiles[row][col]))
                min_tile = tiles[row][col].get();
        }
    }
    min_tile->m_sides.pop_back();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto& row: tiles)
            for (auto& tile: row) {
                tile->update();
                tile->draw_into(window);
            }
//        window.draw(shape);
        window.display();
    }

    return 0;
}