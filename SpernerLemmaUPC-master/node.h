#pragma once

#include <vector>
#include <string>

using namespace std;

// Resolve circular dependence between Face and Node classes.
class Face;

/*
 * Describes a single node within the Sperner simplex.
 */
class Node {
  public:
    int label;
    string color = "";
    vector<int> x;
    vector<Face*> faces;

    Node(int* x_vals, int size);
    void findMissingNode(Node*& result, int target_label, string target_string);
    void labelVertex(int k);
    int numZeroes();
    void printNode();
    ~Node();
};
