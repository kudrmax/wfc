#include "Cell.h"
#include <algorithm>

Cell::Cell(const sf::Vector2f& pos, const std::vector<Tile>& tiles, std::vector<DIR>&& possible_directions)
        : m_possible_tiles(tiles), m_possible_directions(possible_directions) {
    m_body.setSize({ BLOCK_SIZE, BLOCK_SIZE });
    m_body.setOrigin(m_body.getSize() / 2.0f);
    m_body.setPosition(pos);
    fillRowCount();
}


void Cell::drawInto(sf::RenderWindow& window) const {
    window.draw(m_body);
    window.draw(m_text);
}

void Cell::collapseCell() {
    auto one_tile = *select_randomly(m_possible_tiles.begin(), m_possible_tiles.end());
    m_possible_tiles.clear();
    m_possible_tiles = { one_tile };
    updateCollapseStatus();
    updateTexture();
}

bool Cell::reduceEntropyCell(std::vector<size_t> possible_edges_on_dir, Cell::DIR dir_from) {

    Cell::DIR dir_to = static_cast<Cell::DIR>((dir_from + 2) % 4); // opposite direction

    bool was_reduced = false;

    for (auto possible_tile_it = m_possible_tiles.begin();
         possible_tile_it != m_possible_tiles.end(); possible_tile_it++) {
        bool is_possible_tile_correct = false;
        auto edge = possible_tile_it->edges[dir_to];
        for (auto edge_on_dir: possible_edges_on_dir) {
            if (edge == edge_on_dir) {
                is_possible_tile_correct = true;
                break;
            }
        }
        if (!is_possible_tile_correct) {
            auto it_to_erase = std::find_if(m_possible_tiles.begin(), m_possible_tiles.end(),
                                            [&](const Tile& a) { return &a == &*possible_tile_it; });
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

void Cell::updateCollapseStatus() {
    if (m_possible_tiles.size() == 1)
        is_collapsed = true;
}

void Cell::updateTexture() {

    sf::RenderTexture render_texture;
    render_texture.create(BLOCK_SIZE, BLOCK_SIZE);

    size_t count_total = m_possible_tiles.size();
    size_t count_in_row = m_col_count[count_total];

    auto side_delta = count_total == 1 ? 0 : 0.05f * BLOCK_SIZE;
    auto delta_between = count_total == 1 ? 0 : 0.15f * BLOCK_SIZE / count_in_row;

    float mini_block_size = (BLOCK_SIZE - side_delta * 2 - (count_in_row - 1) * delta_between) / count_in_row;

    auto zero_pos_x = side_delta;
    auto zero_pos_y = side_delta;

    for (int i = 0, y = 0, x = 0; i < count_total; i++, x++) {

        if (x > count_in_row - 1) {
            x = x % count_in_row;
            y++;
        }

        auto& tile = m_possible_tiles[i];
        const auto& texture_str = tile.texture_str;
        auto rotation = tile.rotation;
        sf::RectangleShape shape;
        shape.setSize({ mini_block_size, mini_block_size });
        shape.setOrigin(shape.getSize() / 2.0f);

        auto pos_x = zero_pos_x + (mini_block_size + delta_between) * x + mini_block_size / 2;
        auto pos_y = zero_pos_y + (mini_block_size + delta_between) * y + mini_block_size / 2;
        shape.setPosition(pos_x, pos_y);
        sf::Texture texture;
        texture.loadFromFile(texture_str);
        shape.setTexture(&texture);
        shape.rotate(360 - rotation * 90);
        render_texture.draw(shape);

        render_texture.display();
        sf::Texture temp(render_texture.getTexture());
        m_texture = temp;
        m_body.setTexture(&m_texture);
    }
}

void Cell::fillRowCount() {
    auto MAX_TILE_COUNT = 100;
    for (int i = 1; i < MAX_TILE_COUNT; i++) {
        for (int num = 1; num < MAX_TILE_COUNT; num++) {
            if (i <= num * num) {
                m_col_count[i] = num;
                break;
            }
        }
    }
}
