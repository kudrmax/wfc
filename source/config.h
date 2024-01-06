#pragma once

#include <unordered_map>

// настраиваемые вручную параметра
const int H = 800; // высота окна
const int BLOCK_COUNT_H = 12; // количество фрагментов разбиения по вертикали
const float DELTA_TIME = 0.005f; // минимальное время между итерациями (0 для наискорейшей генерации)

// параметры, которые высчитываются автоматически
const int BLOCK_SIZE = H / BLOCK_COUNT_H; // размер одного фрагмента разбиения
const int W = 16 * H / 9 - (16 * H / 9) % BLOCK_SIZE; // ширина окна
const int BLOCK_COUNT_W = W / BLOCK_SIZE; // количество фрагментов разбиения по горизонтали
