#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Tile.h"
#include <random>
#include <stack>

class Application {
public:
    Application();
    void run(); // бесконечный цикл с запущенной игрой
private:
    void eventHandling(); // обрабатываем события
    void update(); // меняем состояние объектов
    void render(); // отрисовываем новое состояние
    std::vector<Cell*> getLowestEntropyCells();
    void waveFunctionCollapse();
private:
    void fillCells();
    void fillTiles();
private:
    sf::RenderWindow m_window{ sf::VideoMode(W, H), "WFC"};
    std::vector<std::vector<Cell>> m_cells;
    std::vector<Tile> m_tiles;
    sf::Clock m_clock;
    std::stack<Cell*> m_cells_to_collapse_stack;
};