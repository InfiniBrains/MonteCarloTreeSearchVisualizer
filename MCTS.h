//
// Created by Alexandre Tolstenko Nogueira on 2024.03.21.
//

#ifndef UNTITLED130_MCTS_H
#define UNTITLED130_MCTS_H

#include "Board.h"
#include <iostream>

// monte carlo tree search node
struct __attribute__((packed)) Node {
  size_t visits=0;
  int32_t wins=0;
  Node* parent= nullptr;
  std::unordered_set<Node*> children;
  Board board;
  Node(Board board, Node* parent): board(board), parent(parent) {}
  ~Node();
  double uct() const;
  void print_node() const;
};

struct MCTS {
private:
  int max_iterations;
  Node* root = nullptr;

  Node* best_child(Node* node) const;
  Node* selection(Node* node);
  Node* expansion(Node* node);
  int simulation(Node* node);
  void backpropagation(Node* node, int result);

public:
  MCTS(int max_iterations): max_iterations(max_iterations) {}
  ~MCTS(){
    delete root;
  }
  Board search(Board board);
};


#endif //UNTITLED130_MCTS_H
