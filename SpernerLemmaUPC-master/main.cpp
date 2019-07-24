#include <iostream>
#include <vector>
#include <unordered_map>

#include "node.h"
#include "face.h"
#include "triangle.h"
#include "spernerTriangle.h"

using namespace std;

int main() {
  // Get k and q values as inputs from user
  int k;
  int q;

  cout << "Enter a k-value (number of dimensions): ";
  cin >> k;
  cout << "Enter a q-value (size of triangle): ";
  cin >> q;

  // Get k unique colors as inputs from user
  vector<string> colors;
  unordered_map<string, int> colors_used;

  while(static_cast<int>(colors.size()) != k) {
    string color;
    cout << "Enter a unique color: ";
    cin >> color;
    if(colors_used.find(color) == colors_used.end()) {
      colors.push_back(color);
      colors_used.insert({color, 0});
    } else {
      cout << "Error: color was already entered" << endl;
    }
  }

  // Get a random seed as input from user
  int seed;
  cout << "Enter a random seed: ";
  cin >> seed;

  // Build the triangle
  cout << "Building the triangle......" << endl;
  Triangle* triangle = new Triangle(q, k, colors, seed);

  // Color the triangle
  cout << "Coloring the triangle......" << endl;
  triangle->colorTriangle();

  // Find sperner triangles
  cout << "Finding sperner triangles......" << endl;
  triangle->findSpernerTriangle();

  // Print all nodes, faces, and sperner triangles
  cout << endl;
  triangle->printAllNodes();
  triangle->printAllFaces();
  triangle->printAllSpernerTriangles();

  return 0;
}
