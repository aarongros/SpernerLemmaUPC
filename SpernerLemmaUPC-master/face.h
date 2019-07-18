#pragma once

#include <vector>
#include <string>

#include "spernerTriangle.h"

using namespace std;

// Resolve circular dependence between Face and Node classes.
class Node;

/*
 * Describes single face of Sperner simplex.
 */
class Face {
  public:
    bool traversed;
    vector<Node*> nodes;

    Face(vector<Node*> node_list);
    void vectorToString(vector<int>& vector, string& ans);
    bool isOpen(vector<string> colors);
    void findNextFace(vector<string> colors, Face*& result, Node*& extra_node);
    bool matchesNodes(vector<Node*> matching_nodes, Node*& extra_node);
    bool ithValIsZero(int i);
    void printFace();
    ~Face();
};
