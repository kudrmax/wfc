#include "Cell.h"

Cell::Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles, std::vector<DIR>&& possible_directions)
        : m_possible_tiles(tiles), m_possible_directions(possible_directions) {
    m_body.setSize({ BLOCK_SIZE, BLOCK_SIZE });
    m_body.setOrigin(m_body.getSize() / 2.0f);
    m_body.setPosition(pos);
}

void Cell::markCollapsed() {

    updateText();

    if (!is_collapsed && m_possible_tiles.size() == 1) {
        m_texture.loadFromFile(m_possible_tiles[0].texture_str);
        m_body.setTexture(&m_texture);
        m_body.rotate(m_possible_tiles[0].rotation * 90);
        is_collapsed = true;
    }
}

void Cell::updateText() {
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

void Cell::drawInto(sf::RenderWindow& window) const {
    window.draw(m_body);
    window.draw(m_text);
}

void Cell::collapseCell() {
    auto one_tile = *select_randomly(m_possible_tiles.begin(), m_possible_tiles.end());
    m_possible_tiles.clear();
    m_possible_tiles = { one_tile };
}

bool Cell::reduceEntropyCell(std::vector<Tile> neighbour_possible_tiles, Cell::DIR dir_from) {

    Cell::DIR dir_to;
    switch (dir_from) {
        case Cell::DIR::U:
            dir_to = Cell::DIR::D;
        case Cell::DIR::R:
            dir_to = Cell::DIR::L;
        case Cell::DIR::D:
            dir_to = Cell::DIR::U;
        case Cell::DIR::L:
            dir_to = Cell::DIR::R;
    }

    bool was_reduced = false;

    for (const auto& possible_tile: m_possible_tiles) {
        bool is_possible_tile_correct = false;
        auto id = possible_tile.edges[dir_to];
        for (const auto& neighbour_possible_tile: neighbour_possible_tiles) {
            auto neighbour_id = neighbour_possible_tile.edges[dir_from];
            if (id == neighbour_id) {
                is_possible_tile_correct = true;
                break;
            }
        }
        if (!is_possible_tile_correct) {
            auto* tile_to_delete_p = &possible_tile;
            auto it = std::find_if(m_possible_tiles.begin(), m_possible_tiles.end(),
                                   [&](const Tile& a) { return &a == tile_to_delete_p; });
            if (it != m_possible_tiles.end()) {
                m_possible_tiles.erase(it);
                was_reduced = true;
            }
        }
    }

    return was_reduced;
}
