#pragma once

#include <unordered_map>

const int H = 765;
const int BLOCK_COUNT_H = 4;
const int BLOCK_SIZE = H / BLOCK_COUNT_H;
const int W = 16 * H / 9 - (16 * H / 9) % BLOCK_SIZE;
const int BLOCK_COUNT_W = W / BLOCK_SIZE;