#include "Cell.h"
#include <algorithm>

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
        m_body.rotate(360 - m_possible_tiles[0].rotation * 90);
        is_collapsed = true;
    }
}

void Cell::updateText() {
    if (!m_font.loadFromFile("PixelFont.ttf"))
        throw std::runtime_error("No such file in directory");
    m_text.setFont(m_font);
    std::string tile_str;
    for (auto& tile: m_possible_tiles) {
        tile_str += tile.print_sfml() + " ";
    }
    m_text.setString(std::to_string(is_collapsed) + "\n" +
                     std::to_string(m_possible_tiles.size()) + "\n" +
                     tile_str);
    m_text.setCharacterSize(50);
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

bool Cell::reduceEntropyCell(std::vector<size_t> possible_edges_on_dir, Cell::DIR dir_from) {

    Cell::DIR dir_to = static_cast<Cell::DIR>((dir_from + 2) % 4); // opposite direction

    bool was_reduced = false;

    for (auto possible_tile_it = m_possible_tiles.begin(); possible_tile_it != m_possible_tiles.end(); possible_tile_it++) {
        bool is_possible_tile_correct = false;
        auto edge = possible_tile_it->edges[dir_to];
        for (auto edge_on_dir: possible_edges_on_dir) {
            if (edge == edge_on_dir) {
                is_possible_tile_correct = true;
                break;
            }
        }
        if (!is_possible_tile_correct) {
            auto it_to_erase = std::find_if(m_possible_tiles.begin(), m_possible_tiles.end(), [&](const Tile& a) { return &a == &*possible_tile_it; });
            if (it_to_erase != m_possible_tiles.end()) {
                possible_tile_it = m_possible_tiles.erase(it_to_erase);
                --possible_tile_it;
                was_reduced = true;
            }
        }
    }

    return was_reduced;
}
std::vector<size_t> Cell::getPossibleEdgesOnDirection(Cell::DIR direction) {
    std::vector<size_t> possible_edges;
    for (auto& possible_tile_p: m_possible_tiles) {
        auto id = possible_tile_p.edges[direction];
        if (std::find(possible_edges.begin(), possible_edges.end(), id) == possible_edges.end())
            possible_edges.push_back(id);
    }
    return possible_edges;
}
