#include "Application.h"
#include <iostream>
#include <algorithm>
#include "random.h"

void Application::fillTiles() {
    switch (TILE_TYPE) {
        case BLUE:
            m_tiles.push_back({ "simple/0000.png", { 0, 0, 0, 0 }, 0 });
            m_tiles.push_back({ "simple/1111.png", { 1, 1, 1, 1 }, 0 });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "simple/1101.png", { 1, 1, 0, 1 }, i });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "simple/0101.png", { 0, 1, 0, 1 }, i });
            break;
        case GREEN_KNOTS:
            m_tiles.push_back({ "knots/empty.png", { 0, 0, 0, 0 }, 0 });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "knots/line.png", { 0, 1, 0, 1 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "knots/t.png", { 0, 1, 1, 1 }, i });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "knots/cross.png", { 1, 1, 1, 1 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "knots/corner.png", { 1, 1, 0, 0 }, i });
            break;
        case BLACK_AND_WHITE_ROADS:
            m_tiles.push_back({ "black_and_white_roads/0.png", { 0, 0, 0, 0 }, 0 });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "black_and_white_roads/1.png", { 0, 1, 0, 1 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "black_and_white_roads/2.png", { 1, 1, 0, 1 }, i });
            m_tiles.push_back({ "black_and_white_roads/3.png", { 1, 1, 1, 1 }, 0 });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "black_and_white_roads/4.png", { 0, 2, 0, 2 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "black_and_white_roads/5.png", { 2, 2, 0, 2 }, i });
            m_tiles.push_back({ "black_and_white_roads/6.png", { 2, 2, 2, 2 }, 0 });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "black_and_white_roads/7.png", { 1, 2, 1, 2 }, i });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "black_and_white_roads/8.png", { 1, 2, 1, 2 }, i });
            break;
        case GAME:
            m_tiles.push_back({ "summer/grass 0.png", { 0, 0, 0, 0 }, 0 });
            m_tiles.push_back({ "summer/road 0.png", { 1, 1, 0, 1 }, 0 });
            m_tiles.push_back({ "summer/road 1.png", { 1, 0, 1, 1 }, 0 });
            m_tiles.push_back({ "summer/road 2.png", { 0, 1, 1, 1 }, 0 });
            m_tiles.push_back({ "summer/road 3.png", { 1, 1, 1, 0 }, 0 });
            m_tiles.push_back({ "summer/roadturn 0.png", { 1, 1, 0, 0 }, 0 });
            m_tiles.push_back({ "summer/roadturn 1.png", { 1, 0, 0, 1 }, 0 });
            m_tiles.push_back({ "summer/roadturn 2.png", { 0, 0, 1, 1 }, 0 });
            m_tiles.push_back({ "summer/roadturn 3.png", { 0, 1, 1, 0 }, 0 });

            m_tiles.push_back({ "summer/cliff 0.png", { 0, 2, 0, 2 }, 0 });
            m_tiles.push_back({ "summer/cliff 1.png", { 2, 0, 2, 0 }, 0 });
            m_tiles.push_back({ "summer/cliff 2.png", { 0, 3, 0, 3 }, 0 });
            m_tiles.push_back({ "summer/cliff 3.png", { 4, 0, 4, 0 }, 0 });

            m_tiles.push_back({ "summer/cliffcorner 0.png", { 2, 3, 0, 0 }, 0 });
            m_tiles.push_back({ "summer/cliffcorner 1.png", { 4, 0, 0, 3 }, 0 });
            m_tiles.push_back({ "summer/cliffcorner 2.png", { 0, 0, 7, 6 }, 0 });
            m_tiles.push_back({ "summer/cliffcorner 3.png", { 0, 10, 2, 0 }, 0 });
            m_tiles.push_back({ "summer/cliffturn 0.png", { 2, 2, 0, 0 }, 0 });
            m_tiles.push_back({ "summer/cliffturn 1.png", { 2, 0, 0, 2 }, 0 });
            m_tiles.push_back({ "summer/cliffturn 2.png", { 0, 0, 2, 3 }, 0 });
            m_tiles.push_back({ "summer/cliffturn 3.png", { 0, 3, 4, 0 }, 0 });

            m_tiles.push_back({ "summer/water_a 0.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer/water_b 0.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer/water_c 0.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer/watercorner 0.png", { 14, 16, 0, 0 }, 0 });
            m_tiles.push_back({ "summer/watercorner 1.png", { 12, 0, 0, 16 }, 0 });
            m_tiles.push_back({ "summer/watercorner 2.png", { 0, 0, 12, 12 }, 0 });
            m_tiles.push_back({ "summer/watercorner 3.png", { 0, 12, 14, 0 }, 0 });
            m_tiles.push_back({ "summer/waterside 0.png", { 11, 16, 0, 16 }, 0 });
            m_tiles.push_back({ "summer/waterside 1.png", { 13, 0, 13, 11 }, 0 });
            m_tiles.push_back({ "summer/waterside 2.png", { 0, 12, 11, 12 }, 0 });
            m_tiles.push_back({ "summer/waterside 3.png", { 14, 11, 14, 0 }, 0 });
            m_tiles.push_back({ "summer/waterturn 0.png", { 11, 11, 14, 16 }, 0 });
            m_tiles.push_back({ "summer/waterturn 1.png", { 11, 16, 13, 11 }, 0 });
            m_tiles.push_back({ "summer/waterturn 2.png", { 13, 12, 11, 11 }, 0 });
            m_tiles.push_back({ "summer/waterturn 3.png", { 14, 11, 11, 12 }, 0 });
            break;
        case GAME_PIXEL:
            m_tiles.push_back({ "summer-pixel/grass 0-pixelicious.png", { 0, 0, 0, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/road 0-pixelicious.png", { 1, 1, 0, 1 }, 0 });
            m_tiles.push_back({ "summer-pixel/road 1-pixelicious.png", { 1, 0, 1, 1 }, 0 });
            m_tiles.push_back({ "summer-pixel/road 2-pixelicious.png", { 0, 1, 1, 1 }, 0 });
            m_tiles.push_back({ "summer-pixel/road 3-pixelicious.png", { 1, 1, 1, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/roadturn 0-pixelicious.png", { 1, 1, 0, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/roadturn 1-pixelicious.png", { 1, 0, 0, 1 }, 0 });
            m_tiles.push_back({ "summer-pixel/roadturn 2-pixelicious.png", { 0, 0, 1, 1 }, 0 });
            m_tiles.push_back({ "summer-pixel/roadturn 3-pixelicious.png", { 0, 1, 1, 0 }, 0 });

            m_tiles.push_back({ "summer-pixel/cliff 0-pixelicious.png", { 0, 2, 0, 2 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliff 1-pixelicious.png", { 2, 0, 2, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliff 2-pixelicious.png", { 0, 3, 0, 3 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliff 3-pixelicious.png", { 4, 0, 4, 0 }, 0 });

            m_tiles.push_back({ "summer-pixel/cliffcorner 0-pixelicious.png", { 2, 3, 0, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffcorner 1-pixelicious.png", { 4, 0, 0, 3 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffcorner 2-pixelicious.png", { 0, 0, 7, 6 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffcorner 3-pixelicious.png", { 0, 10, 2, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffturn 0-pixelicious.png", { 2, 2, 0, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffturn 1-pixelicious.png", { 2, 0, 0, 2 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffturn 2-pixelicious.png", { 0, 0, 2, 3 }, 0 });
            m_tiles.push_back({ "summer-pixel/cliffturn 3-pixelicious.png", { 0, 3, 4, 0 }, 0 });

            m_tiles.push_back({ "summer-pixel/water_a 0-pixelicious.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/water_b 0-pixelicious.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/water_c 0-pixelicious.png", { 11, 11, 11, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/watercorner 0-pixelicious.png", { 14, 16, 0, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/watercorner 1-pixelicious.png", { 12, 0, 0, 16 }, 0 });
            m_tiles.push_back({ "summer-pixel/watercorner 2-pixelicious.png", { 0, 0, 12, 12 }, 0 });
            m_tiles.push_back({ "summer-pixel/watercorner 3-pixelicious.png", { 0, 12, 14, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterside 0-pixelicious.png", { 11, 16, 0, 16 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterside 1-pixelicious.png", { 13, 0, 13, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterside 2-pixelicious.png", { 0, 12, 11, 12 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterside 3-pixelicious.png", { 14, 11, 14, 0 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterturn 0-pixelicious.png", { 11, 11, 14, 16 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterturn 1-pixelicious.png", { 11, 16, 13, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterturn 2-pixelicious.png", { 13, 12, 11, 11 }, 0 });
            m_tiles.push_back({ "summer-pixel/waterturn 3-pixelicious.png", { 14, 11, 11, 12 }, 0 });
            break;
        case PLATFORMER:
            m_tiles.push_back({ "platformer/dirt 0.png", { 0, 0, 0, 0 }, 0 });
            m_tiles.push_back({ "platformer/dirt 0.png", { 0, 0, 3, 0 }, 0 });
            m_tiles.push_back({ "platformer/dirt 1.png", { 1, 2, 0, 2 }, 0 });
            m_tiles.push_back({ "platformer/dirt 1.png", { 1, 3, 0, 2 }, 0 });
            m_tiles.push_back({ "platformer/dirt 1.png", { 1, 2, 0, 3 }, 0 });
            m_tiles.push_back({ "platformer/dirt 1.png", { 1, 3, 0, 3 }, 0 });
            m_tiles.push_back({ "platformer/tree 0.png", { 3, 3, 1, 3 }, 0 });
            m_tiles.push_back({ "platformer/tree 1.png", { 3, 3, 1, 3 }, 0 });
            m_tiles.push_back({ "platformer/sky 0.png", { 3, 3, 3, 3 }, 0 });
            m_tiles.push_back({ "platformer/sky 0.png", { 3, 3, 1, 3 }, 0 });
            break;
        case TRAIN:
            m_tiles.push_back({ "train/blank.png", { 0, 0, 0, 0 }, 0 });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "train/down.png", { 0, 1, 1, 1 }, i });
            break;
        case POLKA:
            m_tiles.push_back({ "polka/5.png", { 1, 1, 1, 1 }, 0 });
            m_tiles.push_back({ "polka/8.png", { 0 ,0 ,0 ,0 }, 0 });
            m_tiles.push_back({ "polka/9.png", { 3, 3, 3, 3 }, 0 });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/0.png", { 0, 1, 1, 1 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/1.png", { 0, 0, 1, 1 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/2.png", { 0, 0, 1, 0 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/3.png", { 0, 0, 2, 0 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/4.png", { 0, 3, 3, 3 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/6.png", { 0, 0, 3, 3 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/7.png", { 0, 0, 0, 3 }, i });
            for (size_t i = 0; i < 2; i++) m_tiles.push_back({ "polka/10.png", { 1, 3, 1, 3 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/11.png", { 1, 0, 2, 0 }, i });
            for (size_t i = 0; i < 4; i++) m_tiles.push_back({ "polka/12.png", { 3, 0, 2, 0 }, i });
            break;


        default:
            m_tiles.push_back({ "simple/0000.png", { 0, 0, 0, 0 }, 0 });
    }
}

Application::Application() {
    generateFromScratch();
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
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                sf::Vector2i pixel_pos = sf::Mouse::getPosition(m_window);
                sf::Vector2f pos = m_window.mapPixelToCoords(pixel_pos);
                int col = BLOCK_COUNT_W * pos.x / W;
                int row = BLOCK_COUNT_H * pos.y / H;
                collapseCell(&m_cells[row][col]);
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::R) {
                generateFromScratch();
            }
            if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter) {
                is_on_pause = !is_on_pause;
            }
        }
    }
}

void Application::update() {

    if (m_clock.getElapsedTime().asSeconds() >= DELTA_TIME) {
        m_clock.restart().asSeconds();

        if (m_cells_to_collapse_p_stack.empty()) {
            if (!is_on_pause)
                collapseCell(getLowestEntropyCell());
        } else
            waveFunctionCollapse();
    }
}

void Application::render() {
    m_window.clear();
    for (const auto& row: m_cells)
        for (const auto& cell: row)
            cell.drawInto(m_window);
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
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            m_cells[row][col].m_row = row;
            m_cells[row][col].m_col = col;
        }
    }
}

std::vector<Cell*> Application::getLowestEntropyCells() {
    std::vector<Cell*> lowest_entropy_tiles;
    size_t lowest_entropy_size = 10000;
    for (int row = 0; row < BLOCK_COUNT_H; row++) {
        for (int col = 0; col < BLOCK_COUNT_W; col++) {
            auto entropy_size = m_cells[row][col].m_possible_tiles.size();
            if (entropy_size != 1 && entropy_size < lowest_entropy_size)
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


std::pair<size_t, size_t> Application::getCellsIndexes(Cell& cell_ref) {
    return { cell_ref.m_row, cell_ref.m_col };
}

Cell* Application::getNeighbour(Cell& cell_ref, Cell::DIR dir) {
    auto [row, col] = getCellsIndexes(cell_ref);
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
Cell* Application::waveFunctionCollapse() {
    auto& cell = *m_cells_to_collapse_p_stack.top(); // взяли верхний элемент
    m_cells_to_collapse_p_stack.pop(); // убрали его из стека (т.е. считаем его collapsed)
    for (const auto& possible_direction: cell.m_possible_directions) {
        auto& neighbour_cell = *getNeighbour(cell, possible_direction);
        auto possible_edges = cell.getPossibleEdgesOnDirection(possible_direction);
        if (!neighbour_cell.is_collapsed) {
            bool was_reduced = neighbour_cell.reduceEntropyCell(possible_edges, possible_direction);
            if (was_reduced)
                m_cells_to_collapse_p_stack.push(&neighbour_cell);
        }
    }
    cell.updateTexture();
    return &cell;
}

void Application::collapseCell(Cell* cell_to_collapse) {
    if (cell_to_collapse) {
        cell_to_collapse->collapseCell();
        m_cells_to_collapse_p_stack.push(cell_to_collapse);
    }
}

void Application::generateFromScratch() {
    m_cells_to_collapse_p_stack = std::stack<Cell*>{};
    m_tiles.clear();
    m_cells.clear();
    m_clock = sf::Clock{};
    fillTiles();
    fillCells();
    for (auto& row: m_cells)
        for (auto& cell: row)
            cell.updateTexture();
}




