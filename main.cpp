#include <iostream>
#include <fstream>
#include <vector>
#include "sperner.cpp"
using namespace std;
// Prints array
void printCords(int* curCordinates, int size) {
  for(int i = 0; i < size; i++) {
    cout << curCordinates[i] << " ";
  }
  cout << endl;
}
// Prints Nodes from triangles
void printAllNodes(Triangle* triangle) {
  cout << "All Nodes:" << endl;
  for(int i = 0; i < static_cast<int>(triangle->all_nodes.size()); i++) {
    for(int x : triangle->all_nodes[i]->x) {
      cout << x << " ";
    }
    cout << triangle->all_nodes[i]->color << " " << triangle->all_nodes[i]->label << endl;
  }
  cout << endl;
}
// Prints vector of nodes
void printNodes(vector<Node*> nodes) {
  for(Node* node : nodes) {
    for(int x : node->x) {
      cout << x << ",";
    }
    cout << node->color << " - ";
  }
  cout << endl;
}
//print face
void printFace(Face* face) {
  for(Node* node : face->nodes) {
    for(int x : node->x) {
      cout << x << ",";
    }
    cout << " - ";
  }
}
// Prints faces from triangle
void printAllFaces(Triangle* triangle) {
  cout << "All Faces:" << endl;
  for(int i = 0; i < static_cast<int>(triangle->all_faces.size()); i++) {
    printNodes(triangle->all_faces[i]->nodes);
  }
  cout << endl;
}
// Prints Sperner Triangles from Triangle
void printAllSpernerTriangles(Triangle* triangle) {
  cout << "All Sperner Triagnles:" << endl;
  for(SpernerTriangle* spernTri : triangle->all_sperner_triangles) {
    printNodes(spernTri->nodes);
  }
}
//Prints vector
template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

int main() {
  int q = 3;
  int k = 3;
  // vector should have k number of colors
  vector<string> colors {"blue", "red", "green"};
  Triangle* triangle = new Triangle(q, k, colors);
  triangle->colorTriangle();
  printAllNodes(triangle);
  printAllFaces(triangle);
  triangle->findSpernerTrangle();
  printAllSpernerTriangles(triangle);
  return 0;
}
