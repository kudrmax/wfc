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
private:
    void fillCells();
    void fillTiles();
    std::vector<Cell*> getLowestEntropyCells();
    Cell* getLowestEntropyCell();
    std::pair<size_t, size_t> getCellsIndexesByReference(Cell&);
    Cell* getNeighbour(Cell& cell_ref, Cell::DIR dir);
    void waveFunctionCollapse(Cell& cell);
private:
    sf::RenderWindow m_window{ sf::VideoMode(W, H), "WFC"};
    std::vector<std::vector<Cell>> m_cells;
    std::vector<Tile> m_tiles;
    sf::Clock m_clock;
};