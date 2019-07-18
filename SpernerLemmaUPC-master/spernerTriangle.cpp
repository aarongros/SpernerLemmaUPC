#include "node.h"
#include "face.h"
#include "triangle.h"
#include "spernerTriangle.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * Custom constructor for the SpernerTriangle class.
 *
 * @param solution_nodes Pointers to nodes of Sperner Triangle
 */
SpernerTriangle::SpernerTriangle(vector<Node *> solution_nodes) {
  for (Node * node : solution_nodes) {
    this->nodes.push_back(node);
  }
}

/*
 * Prints nodes of Sperner Triangle.
 */
void SpernerTriangle::printSpernerTriangle() {
  for(Node* node : nodes) {
    node->printNode();
    cout << " - ";
  }
}
