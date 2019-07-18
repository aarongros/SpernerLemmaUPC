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
 * Checks if a Node has been colored.
 *
 * @return Boolean indicating if Node has been colored
 */
bool Node::isColored() {
  if (this->color == "") {
      return false;
  }
  return true;
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
