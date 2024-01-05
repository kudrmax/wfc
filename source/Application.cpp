#include "Application.h"
#include <iostream>
#include "random.h"

Application::Application() {
    fillTiles();
    fillCells();
}

void Application::run() {
    while (m_window.isOpen()) {
        eventHandling();
        update();
        render();
    }
}

void Application::eventHandling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Application::update() {

    if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
        m_clock.restart().asSeconds();
        std::vector<Cell*> lowest_entropy_cells_vec = getLowestEntropyCells();
        Cell* cell_to_collapse_p = *select_randomly(lowest_entropy_cells_vec.begin(), lowest_entropy_cells_vec.end());
        cell_to_collapse_p->collapseCell();
        cell_to_collapse_p->markCollapsed();

        for (auto& row: m_cells) {
            for (auto& cell: row) {
                cell.markCollapsed();
            }
        }

        m_cells_to_collapse_p_stack.push(cell_to_collapse_p);

        while (!m_cells_to_collapse_p_stack.empty()) {
            auto* cell_p = m_cells_to_collapse_p_stack.top();
            m_cells_to_collapse_p_stack.pop();
            auto possible_tiles_p_vec = cell_p->m_possible_tiles;
            auto possible_directions = cell_p->m_possible_directions;
            for (auto dir : possible_directions) {
                auto neighbour_cell_p = getNeighbour(cell_p, dir);
                if (!neighbour_cell_p->is_collapsed) {
//                    bool was_reduced = neighbour_cell_p->reduceEntropyCell(possible_tiles_p_vec, dir);
//                    if (was_reduced)
//                        m_cells_to_collapse_p_stack.push(neighbour_cell_p);
                }
            }
        }

//        bool was_reduced = m_cells[2][2].reduceEntropyCell({Cell::DIR::L, Cell::DIR::L}, Cell::DIR::D);
    }

//    waveFunctionCollapse();



//    for (int row = 0; row < BLOCK_COUNT; row++) {
//        for (int col = 0; col < BLOCK_COUNT; col++) {
//            auto& cell = m_cells[row][col];
//            if (!cell.is_collapsed) {
//                // пофиксить ее возможные варианты
//
//            }
//        }
//    }
}

void Application::render() {
    m_window.clear();

    for (auto& row: m_cells) {
        for (auto& cell: row) {
            cell.drawInto(m_window);
        }
    }

    m_window.display();
}

void Application::fillCells() {
    for (int row = 0; row < BLOCK_COUNT; row++) {
        std::vector<Cell> row_vec;
        auto pos_zero = sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto pos = pos_zero + sf::Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE);
            std::vector<Cell::DIR> possible_directions = { Cell::U, Cell::R, Cell::D, Cell::L };
            if (row == 0)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::U));
            if (col == 0)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::L));
            if (row == BLOCK_COUNT - 1)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::D));
            if (col == BLOCK_COUNT - 1)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::R));
            row_vec.emplace_back(pos, m_tiles, std::move(possible_directions));
        }
        m_cells.emplace_back(std::move(row_vec));
    }
}

void Application::fillTiles() {
    for (size_t i = 0; i < 4; i++) {
        m_tiles.push_back({ "3.png", { 1, 1, 0, 1 }, i });
    }
    m_tiles.push_back({ "blank.png", { 0, 0, 0, 0 }, 1 });
}

std::vector<Cell*> Application::getLowestEntropyCells() {
    std::vector<Cell*> lowest_entropy_tiles;
    size_t max_entropy_size = 10000;
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto entropy_size = m_cells[row][col].m_possible_tiles.size();
            if (entropy_size != 1 && entropy_size < max_entropy_size)
                max_entropy_size = entropy_size;
        }
    }
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            if (m_cells[row][col].m_possible_tiles.size() == max_entropy_size)
                lowest_entropy_tiles.push_back(&m_cells[row][col]);
        }
    }
    return lowest_entropy_tiles;
}

void Application::waveFunctionCollapse() {

}

std::pair<size_t, size_t> Application::getCellsIndexesByPointer(Cell* cell_p) {
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            if (&m_cells[row][col] == cell_p)
                return { row, col };
        }
    }
    return { -1, -1 };
}

Cell* Application::getNeighbour(Cell* cell_p, Cell::DIR dir) {
    auto [row, col] = getCellsIndexesByPointer(cell_p);
    if (row == -1 || col == -1)
        return nullptr;
    switch (dir) {
        case Cell::DIR::U:
            return &m_cells[row - 1][col];
        case Cell::DIR::R:
            return &m_cells[row][col + 1];
        case Cell::DIR::L:
            return &m_cells[row][col - 1];
        case Cell::DIR::D:
            return &m_cells[row + 1][col];
    }
    return nullptr;
}


