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

      Triangle(int q_val, int k_val, vector<string> colors, int seed);
      ~Triangle();
      void findNodes(Node* curNode, unordered_map<string, Node*>& nodes_found, unordered_map<string, Face*>& faces_found);
      void findFaces(Node* curNode, vector<Node*> matches, vector<Node*> visited, unordered_map<string, Face*>& faces_made);
      void initializeBounds(int* upperbound, int* lowerbound, Node* curNode);
      void colorTriangle();
      void findSpernerTrangle();
      void printAllNodes();
      void printAllFaces();
      void printAllSpernerTriangles();
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
    void printNode();
};

class Face {
  public:
    bool traversed;
    vector<Node*> nodes;

    Face(vector<Node*> node_list);
    ~Face();
    bool isOpen(vector<string> colors);
    void findNextFace(vector<string> colors, Face*& result, Node*& extra_node);
    bool matchesNodes(vector<Node*> matching_nodes, Node*& extra_node);
    bool ithValIsZero(int i);
    void printFace();
};

class SpernerTriangle {
  public:
    vector<Node*> nodes;

    SpernerTriangle(vector<Node*> solution_nodes);
    void printSpernerTriangle();
};

#endif
