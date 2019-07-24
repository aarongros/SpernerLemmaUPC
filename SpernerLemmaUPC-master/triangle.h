#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "spernerTriangle.h"

using namespace std;

class Triangle {
    public:
      int k;
      int q;
      vector<Node*> all_nodes;
      vector<Face*> all_faces;
      vector<string> all_colors;
      vector<SpernerTriangle*> all_sperner_triangles;

      Triangle(int q_val, int k_val, vector<string>& colors, int seed);
      void resetFacesVisited(vector<Face *>& faces_visited);
      void combineVectors(vector<Node *>& result, vector<Node *>& vector1,
                          vector<Node *>& vector2);
      void initializeArrToZero(int * array, int size);
      void combineVectorNodes(int * result, vector<Node *>& nodes);
      void arrayToString(int * array, int size, string& ans);
      bool notEqual(int * cur, int * bound, int size);
      void incrementCoordinate(int * cur, int * upper, int * lower, int size);
      int addCoordinates(int * array, int size);
      bool isValidNode(int * cur, int size);
      int factorial(int n);
      void findNodes(Node* curNode, unordered_map<string, Node*>& nodes_found, unordered_map<string, Face*>& faces_found);
      void findFaces(Node* curNode, vector<Node*>& matches, vector<Node*>& visited, unordered_map<string, Face*>& faces_made);
      void initializeBounds(int* upperbound, int* lowerbound, Node* curNode);
      void colorTriangle();
      void findSpernerTriangle();
      void printAllNodes();
      void printAllFaces();
      void printAllSpernerTriangles();
      ~Triangle();
};
