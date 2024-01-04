#include "Application.h"
#include <iostream>
#include "random.h"

Application::Application() {
    create_tiles();
    create_cells(m_cells);
}
void Application::run() {

    while (m_window.isOpen()) {
        event_handling();
        update();
        render();
    }
}

void Application::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Application::update() {

    if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
        m_clock.restart().asSeconds();
        update_min_entropy_cells();
        Cell* cell_to_specify_p = *select_randomly(m_min_entropy_cells.begin(), m_min_entropy_cells.end());
        cell_to_specify_p->specify_cell();
        cell_to_specify_p->update();
    }

    for (auto& row: m_cells) {
        for (auto& cell: row) {
            cell->update();
        }
    }
}

void Application::render() {
    m_window.clear();

    for (auto& row: m_cells) {
        for (auto& cell: row) {
            cell->draw_into(m_window);
        }
    }

    m_window.display();
}
void Application::update_min_entropy_cells() {
    m_min_entropy_cells.clear();
    size_t max_entropy_size = 10000;
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto entropy_size = m_cells[row][col]->m_possible_tiles.size();
            if (entropy_size != 1 && entropy_size < max_entropy_size)
                max_entropy_size = entropy_size;
        }
    }
    for (int row = 0; row < BLOCK_COUNT; row++) {
        for (int col = 0; col < BLOCK_COUNT; col++) {
            if (m_cells[row][col]->m_possible_tiles.size() == max_entropy_size)
                m_min_entropy_cells.push_back(m_cells[row][col].get());
        }
    }
}

void Application::create_cells(Application::cells_t& cells) {
    for (int row = 0; row < BLOCK_COUNT; row++) {
        std::vector<std::unique_ptr<Cell>> row_vec;
        auto pos_zero = sf::Vector2f(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
        for (int col = 0; col < BLOCK_COUNT; col++) {
            auto pos = pos_zero + sf::Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE);
            row_vec.emplace_back(std::make_unique<Cell>(pos, m_tiles));
        }
        cells.emplace_back(std::move(row_vec));
    }
}

void Application::create_tiles() {
    for (size_t i = 0; i < 4; i++) {
        m_tiles.push_back({ "3.png", { 1, 1, 0, 1 }, i });
    }
    m_tiles.push_back({ "blank.png", { 0, 0, 0, 0 }, 1 });
}


