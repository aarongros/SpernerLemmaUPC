#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * Class representing a Sperner Triangle.
 */
class SpernerTriangle {
  public:
    vector<Node*> nodes;
    SpernerTriangle(vector<Node*> solution_nodes);
};
