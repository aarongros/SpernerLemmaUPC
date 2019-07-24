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
SpernerTriangle::SpernerTriangle(vector<Node *>& solution_nodes) {
  nodes = solution_nodes;
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
