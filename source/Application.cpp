#include "Application.h"

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
        auto* min_cell_p = find_min_entropy(m_cells);
        min_cell_p->m_possible_tiles.pop_back();
        min_cell_p->update();
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

Cell* Application::find_min_entropy(const Application::cells_t& cells) {
    auto compare_entropy = [](const Cell& a, const Cell& b) {
        return b.is_collapsed || a.m_possible_tiles.size() < b.m_possible_tiles.size();
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
    m_tiles.push_back({ "blank.png", { 0, 0, 0, 0 }, 1 });
    for (size_t i = 0; i < 4; i++)
        m_tiles.push_back({ "3.png", { 1, 1, 0, 1 }, i });
}


