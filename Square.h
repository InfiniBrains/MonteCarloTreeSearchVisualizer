//
// Created by Alexandre Tolstenko Nogueira on 2024.03.21.
//

#ifndef UNTITLED130_SQUARE_H
#define UNTITLED130_SQUARE_H

#include <cstdint>

// square state on the board
enum struct Square: uint8_t {
  O = 0b00,
  X = 0b01,
  EMPTY = 0b10
};

#endif //UNTITLED130_SQUARE_H
