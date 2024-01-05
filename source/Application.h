#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Tile.h"
#include <random>
#include <stack>

class Application {
    using cells_t = std::vector<std::vector<std::unique_ptr<Cell>>>;
public:
    Application();
    void run(); // бесконечный цикл с запущенной игрой
private:
    std::vector<Cell*> getLowestEntropyTiles();
    void eventHandling(); // обрабатываем события
    void update(); // меняем состояние объектов
    void render(); // отрисовываем новое состояние
private:
    void fillCells();
    void fillTiles();
private:
    sf::RenderWindow m_window{ sf::VideoMode(W, H), "WFC"};
    cells_t m_cells;
    std::vector<Tile> m_tiles;
    sf::Clock m_clock;
    std::stack<Tile*> st;
};