//
// Created by Alexandre Tolstenko Nogueira on 2024.03.21.
//

#ifndef UNTITLED130_BOARD_H
#define UNTITLED130_BOARD_H

#include "Square.h"
#include <unordered_set>

// tic-tac-toe board
struct __attribute__((packed)) Board {
private:
  uint32_t board: 18 = 0b101010101010101010; // empty board
  Square turn: 2 = Square::EMPTY;
public:
  // default constructor
  Board() = default;
  explicit Board(uint32_t board) : board(board) {}
  Board(const Board& board) = default;
  Board(uint32_t board, Square turn) : board(board), turn(turn) {}

  void print_board() const;
  Square get_square(int x, int y) const;
  void set_square(int x, int y, Square square);
  Square get_turn() const;
  void set_turn(Square turn);
  const uint32_t get_board() const;
  bool operator==(const Board& other) const;
  std::unordered_set<Board> generate_children() const;
  bool have_winner(Square square) const;
  Square get_winner() const;
  bool is_full() const;
  bool is_terminal() const;
};

template <>
struct std::hash<Board> {
  size_t operator()(const Board &board) const {
    return std::hash<uint32_t>()(board.get_board());
  }
};

#endif //UNTITLED130_BOARD_H
