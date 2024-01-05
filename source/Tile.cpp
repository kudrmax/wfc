#include "Tile.h"

Tile::Tile(const std::string&& texture_path,
           const std::vector<size_t>&& eds,
           size_t rotation = 0) : texture_str(texture_path),
                                  rotation(rotation) {
    for (int i = 0; i < 4; i++)
        edges.push_back(eds[i + rotation % 4]);
}
