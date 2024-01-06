#pragma once

#include <unordered_map>

const int H = 800;
const int BLOCK_COUNT_H = 7;
const int BLOCK_SIZE = H / BLOCK_COUNT_H;
const int W = 16 * H / 9 - (16 * H / 9) % BLOCK_SIZE;
const int BLOCK_COUNT_W = W / BLOCK_SIZE;
const int MAX_TILE_COUNT = 100;