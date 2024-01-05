#include "Application.h"
#include <iostream>
#include <algorithm>
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

//    if (m_clock.getElapsedTime().asSeconds() >= 2.0f) {
//        m_clock.restart().asSeconds();

    auto* cell_to_collapse = getLowestEntropyCell();
    if (cell_to_collapse) {
        cell_to_collapse->collapseCell();
        waveFunctionCollapse(*cell_to_collapse);

        for (auto& row: m_cells)
            for (auto& cell: row)
                cell.updateTexture();
    }
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
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        std::vector<Cell> row_vec;
        auto pos_zero = sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            auto pos = pos_zero + sf::Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE);
            std::vector<Cell::DIR> possible_directions = { Cell::U, Cell::R, Cell::D, Cell::L };
            if (row == 0)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::U));
            if (col == 0)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::L));
            if (row == BLOCK_COUNT_H - 1)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::D));
            if (col == BLOCK_COUNT_W - 1)
                possible_directions.erase(std::find(possible_directions.begin(), possible_directions.end(), Cell::R));
            row_vec.emplace_back(pos, m_tiles, std::move(possible_directions));
        }
        m_cells.emplace_back(std::move(row_vec));
    }
}

void Application::fillTiles() {
//    m_tiles.push_back({ "demo/blank.png", { 0, 0, 0, 0 }, 1 });
//    for (size_t i = 0; i < 4; i++)
//        m_tiles.push_back({ "demo/3.png", { 1, 1, 0, 1 }, i });

    m_tiles.push_back({ "simple/0000.png", { 0, 0, 0, 0 }, 0 });
    m_tiles.push_back({ "simple/1111.png", { 1, 1, 1, 1 }, 0 });
    for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "simple/1101.png", { 1, 1, 0, 1 }, i });
    for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "simple/0101.png", { 0, 1, 0, 1 }, i });
}

std::vector<Cell*> Application::getLowestEntropyCells() {
    std::vector<Cell*> lowest_entropy_tiles;
    size_t lowest_entropy_size = 10000;
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            if (m_cells[row][col].is_collapsed)
                continue;
            auto entropy_size = m_cells[row][col].m_possible_tiles.size();
            if (entropy_size < lowest_entropy_size)
                lowest_entropy_size = entropy_size;
        }
    }
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            if (m_cells[row][col].m_possible_tiles.size() == lowest_entropy_size)
                lowest_entropy_tiles.push_back(&m_cells[row][col]);
        }
    }
    return lowest_entropy_tiles;
}

Cell* Application::getLowestEntropyCell() {
    std::vector<Cell*> lowest_entropy_cells_vec = getLowestEntropyCells();
    if (lowest_entropy_cells_vec.empty())
        return nullptr;
    Cell* cell_to_collapse = *select_randomly(lowest_entropy_cells_vec.begin(), lowest_entropy_cells_vec.end());
    return cell_to_collapse;
}


std::pair<size_t, size_t> Application::getCellsIndexesByReference(Cell& cell_ref) {
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            if (&m_cells[row][col] == &cell_ref)
                return { row, col };
        }
    }
    return { -1, -1 };
}

Cell* Application::getNeighbour(Cell& cell_ref, Cell::DIR dir) {
    auto [row, col] = getCellsIndexesByReference(cell_ref);
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
void Application::waveFunctionCollapse(Cell& cell_ref) {
    std::stack<Cell*> cells_to_collapse_p_stack;
    cells_to_collapse_p_stack.push(&cell_ref);
    while (!cells_to_collapse_p_stack.empty()) {
        auto& cell = *cells_to_collapse_p_stack.top(); // взяли верхний элемент
        cells_to_collapse_p_stack.pop(); // убрали его из стека (т.е. считаем его collapsed)
        for (const auto& possible_direction: cell.m_possible_directions) {
            auto& neighbour_cell = *getNeighbour(cell, possible_direction);
            auto possible_edges = cell.getPossibleEdgesOnDirection(possible_direction);
            if (!neighbour_cell.is_collapsed) {
                bool was_reduced = neighbour_cell.reduceEntropyCell(possible_edges, possible_direction);
                if (was_reduced)
                    cells_to_collapse_p_stack.push(&neighbour_cell);
            }
        }
    }
}




