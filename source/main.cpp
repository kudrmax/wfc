#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <execution>
#include <unordered_set>
#include <list>
#include "Cell.h"


using cells_t = std::vector<std::vector<std::unique_ptr<Cell>>>;

void create_cells(cells_t& cells) {
    for (int row = 0; row < BLOCK_COUNT; row++) {
        std::vector<std::unique_ptr<Cell>> row_vec;
        auto pos_zero = sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto pos = pos_zero + sf::Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE);
            row_vec.emplace_back(std::make_unique<Cell>(pos));
        }
        cells.emplace_back(std::move(row_vec));
    }
    for (auto& row: cells)
        for (auto& tile: row)
            tile->set_texture();
}

Cell* find_min_entropy(const cells_t& cells) {
    auto compare_entropy = [](const Cell& a, const Cell& b) {
        return b.is_collapsed || a.m_sides.size() < b.m_sides.size();
    };
    Cell* min_cell_p = cells[0][0].get();
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            if (compare_entropy(*cells[row][col], *min_cell_p))
                min_cell_p = cells[row][col].get();
        }
    }
    return min_cell_p;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(W, H), "WFC");

    // Заполняем массив клеток
    std::vector<std::vector<std::unique_ptr<Cell>>> cells;
    create_cells(cells);

    for (int i = 0; i < 7; i++) {
        auto* min_cell_p = find_min_entropy(cells);

        min_cell_p->m_sides.pop_back();
        min_cell_p->update();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto& row: cells)
            for (auto& cell: row) {
                cell->draw_into(window);
                cell->update();
            }
        window.display();
    }

    return 0;
}