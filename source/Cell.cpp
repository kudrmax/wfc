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

bool Cell::reduceEntropyCell(std::vector<size_t> possible_ids_on_dir, Cell::DIR dir_from) {

    std::cout << "possible_ids_on_dir = ";
    for (auto id: possible_ids_on_dir)
        std::cout << id << " ";
    std::cout << std::endl;

    Cell::DIR dir_to;
    switch (dir_from) {
        case Cell::DIR::U:
            dir_to = Cell::DIR::D;
            break;
        case Cell::DIR::R:
            dir_to = Cell::DIR::L;
            break;
        case Cell::DIR::D:
            dir_to = Cell::DIR::U;
            break;
        case Cell::DIR::L:
            dir_to = Cell::DIR::R;
            break;
    }
    std::cout << "dir_to = " << dir_to << std::endl;
    std::cout << "dir_from = " << dir_from << std::endl;
    std::cout << "Cell::DIR::D = " << Cell::DIR::D << std::endl;

    bool was_reduced = false;

    int i = 0;
//    for (const auto& possible_tile: m_possible_tiles) {
    for (auto it = m_possible_tiles.begin(); it != m_possible_tiles.end(); it++) {
        auto& possible_tile = *it;
//        std::cout << "i = " << i++ << std::endl;
        bool is_possible_tile_correct = false;
        auto id = possible_tile.edges[dir_to];
        for (auto possible_id_on_dir: possible_ids_on_dir) {
            if (id == possible_id_on_dir) {
                is_possible_tile_correct = true;
                break;
            }
        }
        if (!is_possible_tile_correct) {
            auto* tile_to_delete_p = &possible_tile;
            auto it_to_erase = std::find_if(m_possible_tiles.begin(), m_possible_tiles.end(),
                                            [&](const Tile& a) { return &a == tile_to_delete_p; });
            if (it_to_erase != m_possible_tiles.end()) {
//                std::cout << "SIZE = " << m_possible_tiles.size() << "\n";
//                for (auto tile: m_possible_tiles)
//                    tile.print();
                it_to_erase->print();
                it = m_possible_tiles.erase(it_to_erase);
                --it;
                was_reduced = true;
            }
        }
    }

    return was_reduced;
}
