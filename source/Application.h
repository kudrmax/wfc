#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Tile.h"

class Application {
public:
    using cells_t = std::vector<std::vector<std::unique_ptr<Cell>>>;
public:
    Application();
    void run(); // бесконечный цикл с запущенной игрой
private:
    Cell* find_min_entropy(const cells_t& cells);
    void create_cells(cells_t& cells);
    void create_tiles();
    void event_handling(); // обрабатываем события
    void update(); // меняем состояние объектов
    void render(); // отрисовываем новое состояние
private:
    sf::RenderWindow m_window{ sf::VideoMode(W, H), "WFC"};
    std::vector<std::vector<std::unique_ptr<Cell>>> m_cells;
    std::vector<Tile> m_tiles;
    sf::Clock m_clock;
};