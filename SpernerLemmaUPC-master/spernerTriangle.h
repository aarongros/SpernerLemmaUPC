#pragma once

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
 * Describes an overall Sperner simplex with a complete node list.
 */
class SpernerTriangle {
  public:
    vector<Node*> nodes;

    SpernerTriangle(vector<Node*> solution_nodes);
    void printSpernerTriangle();
};
