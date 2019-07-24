#include "node.h"
#include "face.h"
#include "triangle.h"
#include "spernerTriangle.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * Custom constructor for the Node class.
 *
 * @param x_vals Pointer to vals to Node coordinates
 * @param size Dimension of the Sperner simplex
 */
Node::Node(int * x_vals, int size) {
  for (int j = 0; j < size; j++) {
    x.push_back(x_vals[j]);
  }
  this->labelVertex(size);
}

/*
 * Finds missing node to form a sperner triangle
 *
 * @param node pointer to store the node reference at
 * @param target label of the node
 * @param target color of the node
 */
void Node::findMissingNode(Node*& result, int target_label, string target_string) {
  for(Face* face : this->faces) {
    for(Node* node : face->nodes) {
      if(node->label == target_label && node->color == target_string) {
        result = node;
        return;
      }
    }
  }
}

/*
 * Assigns a label to a vertex of the simplex.
 *
 * @param k Dimension of Sperner simplex
 */
void Node::labelVertex(int k) {
  int sum = 0;

  for (int j = 1; j <= k ; j++) {
    sum += j * this->x[j-1];
  }
  this->label = sum % k;
}

/*
 * Counts number of zeros in Node's coordinates.
 *
 * @return Number of zeros in Node's coordinates
 */
int Node::numZeroes() {
  int count = 0;

  for (int x : this->x) {
    if (x == 0) {
      count++;
    }
  }
  return count;
}

/*
 * Prints coordinates of a Node.
 */
void Node::printNode() {
  for (int cord : this->x) {
    cout << cord << ",";
  }
  cout << this->color << " " << this->label;
}

/*
 * Default destructor for the Node class.
 */
Node::~Node() {}
