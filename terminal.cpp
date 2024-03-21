#include <iostream>
#include <vector>
#include "MCTS.h"


int main() {
  Board board;
  board.set_turn(Square::O);

  while(!board.is_terminal()){
    board.print_board();
    MCTS mcts = MCTS(1000);
    if(board.get_turn()==Square::X){
      std::cout<<"X's turn"<<std::endl;
      board = mcts.search(board);
      board.set_turn(Square::X);
    } else {
      std::cout<<"O's turn"<<std::endl;
      board = mcts.search(board);
      board.set_turn(Square::O);
    }
    // check if the game is over
    if(board.have_winner(Square::X)){
      std::cout<<"X wins"<<std::endl;
      break;
    }
    if(board.have_winner(Square::O)){
      std::cout<<"O wins"<<std::endl;
      break;
    }
    if(board.is_full()){
      std::cout<<"Draw"<<std::endl;
      break;
    }
    // change the turns
    board.set_turn((Square)(!(bool)board.get_turn()));
  }
  std::cout << "Final board"<<std::endl;
  board.print_board();

  return 0;
}
