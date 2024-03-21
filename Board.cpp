//
// Created by Alexandre Tolstenko Nogueira on 2024.03.21.
//

#include "Board.h"
#include <iostream>

void Board::print_board() const {
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(get_square(i,j)==Square::X){
        std::cout<<"X ";
      } else if(get_square(i,j)==Square::O){
        std::cout<<"O ";
      } else {
        std::cout<<". ";
      }
    }
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}

Square Board::get_square(int x, int y) const {
  return static_cast<Square>((board >> (x * 2 + y * 6)) & 0b11);
}

void Board::set_square(int x, int y, Square square) {
  board &= ~(0b11 << (x * 2 + y * 6));
  board |= (static_cast<uint32_t>(square) << (x * 2 + y * 6));
}

Square Board::get_turn() const {
  return turn;
}

void Board::set_turn(Square turn) {
  this->turn = turn;
}

const uint32_t Board::get_board() const {
  return board;
}

bool Board::operator==(const Board &other) const {
  return board == other.board;
}

std::unordered_set<Board> Board::generate_children() const {
  std::unordered_set<Board> children;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (get_square(x, y) == Square::EMPTY) {
        Board child = *this;
        child.set_square(x, y, turn);
        child.set_turn((Square) (!(bool) turn));
        children.emplace(child);
      }
    }
  }
  return children;
}

bool Board::have_winner(Square square) const {
  // vertical and horizontal
  for (int i = 0; i < 3; i++) {
    if (get_square(i, 0) == square && get_square(i, 1) == square && get_square(i, 2) == square) {
      return true;
    }
    if (get_square(0, i) == square && get_square(1, i) == square && get_square(2, i) == square) {
      return true;
    }
  }
  // diagonal
  if (get_square(0, 0) == square && get_square(1, 1) == square && get_square(2, 2) == square) {
    return true;
  }
  if (get_square(0, 2) == square && get_square(1, 1) == square && get_square(2, 0) == square) {
    return true;
  }
  return false;
}

Square Board::get_winner() const {
  if (have_winner(Square::X)) {
    return Square::X;
  }
  if (have_winner(Square::O)) {
    return Square::O;
  }
  return Square::EMPTY;
}

bool Board::is_full() const {
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(get_square(i,j)==Square::EMPTY){
        return false;
      }
    }
  }
  return true;
}

bool Board::is_terminal() const {
  return have_winner(Square::X) || have_winner(Square::O) || is_full();
}