#include "Tile.h"

Tile& Tile::rotate(size_t n) {
    m_body.rotate(90.0f * n); // rotate image

    std::vector<size_t> new_edges(4); // rotate edges
    for (int i = 0; i < 4; i++)
        new_edges[i] = edges[i + n % 4];

    edges = new_edges;
    return *this;
}
