#ifndef SPERNER_LEMMA
#define SPERNER_LEMMA

#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Node;
class Face;
class SpernerTriangle;

class Triangle {
    public:
      int k;
      int q;
      vector<Node*> all_nodes;
      vector<Face*> all_faces;
      vector<string> all_colors;
      vector<SpernerTriangle*> all_sperner_triangles;

      Triangle(int q_val, int k_val, vector<string> colors);
      ~Triangle();
      void findNodes(Node* curNode, unordered_map<string, Node*>& nodes_found, unordered_map<string, Face*>& faces_found);
      void findFaces(Node* curNode, vector<Node*> matches, vector<Node*> visited, unordered_map<string, Face*>& faces_made);
      void initializeBounds(int* upperbound, int* lowerbound, int k, Node* curNode);
      void colorTriangle();
      void findSpernerTrangle();
};

class Node {
  public:
    int label;
    string color = "";
    vector<int> x;
    vector<Face*> faces;

    Node(int* x_vals, int size);
    ~Node();
    void labelVertice(int k);
    bool isColored();
    int numZeroes();
};

class Face {
  public:
    bool traversed;
    vector<Node*> nodes;

    Face(vector<Node*> node_list);
    ~Face();
    bool isOpen(vector<string> colors);
    bool hasAllColors(int numColors);
    void findNextFace(vector<string> colors, Face*& result);
    bool matchesNodes(vector<Node*> matching_nodes);
    bool ithValIsZero(int i);
};

class SpernerTriangle {
  public:
    vector<Node*> nodes;

    SpernerTriangle(vector<Node*> solution_nodes);
};

#endif