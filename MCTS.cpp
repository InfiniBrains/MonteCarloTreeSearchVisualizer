//
// Created by Alexandre Tolstenko Nogueira on 2024.03.21.
//

#include "MCTS.h"
#include "Random.h"
#include "Memory.h"
#include <iostream>

Node *MCTS::best_child(Node *node) const {
  if(node->children.size()==0)
    return node;
  if(node->children.size()==1)
    return *node->children.begin();
  Node* best = nullptr;
  double best_score = -100;
  for(auto child: node->children){
    auto score = child->uct();
    if(score>best_score) {
      best_score = score;
      best = child;
    }
  }
  return best;
}

Node *MCTS::selection(Node *node) {
  // only select the best child only if it is fully expanded
  // if not fully expanded, return the current node
  while (node->children.size() == node->board.generate_children().size() && node->children.size()>0)
    node = best_child(node);
  return node;
}

Node* MCTS::expansion(Node* node) {
  if(node->board.is_terminal())
    return node;
  // add the first child not present in the children set
  uset<Board> newStates = node->board.generate_children();
  // get all states from all node->children
  uset<Board> currentStates;
  for(auto child: node->children)
    currentStates.insert(child->board);
  // insert the first state not present in the currentStates
  for(auto state: newStates) { // is it possible to make this more efficient or one-liner?
    if(!currentStates.contains(state)){
      auto n = new Node(state, node);
      node->children.insert(n);
      return n;
    }
  }
  // if all children are present, return the current node
  return node;
}

int MCTS::simulation(Node *node) {
  Board board = node->board;
  while(!board.is_terminal()){
    auto children = board.generate_children();
    // random move
    auto index = random<size_t>(0,children.size()-1);
    auto it = children.begin();
    std::advance(it, index);
    board = *it;
    board.set_turn((Square)(!(bool)board.get_turn()));
  }
  if(board.have_winner(root->board.get_turn())){
    return 1;
  }
  if(board.have_winner((Square)(!(bool)root->board.get_turn()))){
    return -1;
  }
  return 0;
}

void MCTS::backpropagation(Node *node, int result) {
  Node* it = node;
  while(it!=nullptr){
    it->visits++;
    it->wins+=result;
    it = it->parent;
  }
}
Board MCTS::search(Board board, int iterations) {
  delete root;
  if(iterations==0)
    iterations = max_iterations;
  root = new Node(board, nullptr);
  for (int i = 0; i < iterations; i++) {
    Node* node = selection(root);
    node = expansion(node);
    int result = simulation(node);
    backpropagation(node, result);
  }
  Node *best = nullptr;
  double best_score = -100000000;
  for (auto child: root->children) {
    double score = child->uct();
    if (score > best_score) {
      best_score = score;
      best = child;
    }
  }
  return best->board;
}

Board* MCTS::current_board() const {
  if(root == nullptr)
    return nullptr;
  return &root->board;
}

Node::~Node() {
  for(auto child: children){
    delete child;
  }
}

double Node::uct() const {
  if(visits==0 || parent == nullptr || parent->visits==0)
    return 100000000;
  return (double)wins/(double)visits + 1.41*sqrt(log(parent->visits)/(double)visits);
}

void Node::print_node() const {
  board.print_board();
  std::cout << "Wins: " << wins << std::endl;
  std::cout << "Visits: " << visits << std::endl;
  std::cout << "UCT: " << uct() << std::endl;
}

