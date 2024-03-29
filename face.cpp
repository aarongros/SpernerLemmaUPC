#include "node.h"
#include "face.h"
#include "triangle.h"
#include "spernerTriangle.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * Custom constructor for the Face class.
 *
 * @param node_list List of nodes for a single face of simplex
 */
Face::Face(vector<Node*>& node_list) {
  traversed = false;

  nodes = node_list;
}

/*
 * Converts vector to string.
 *
 * @param vector Current vector to convert to string
 * @param ans Resulting string from vector
 */
void Face::vectorToString(vector<int>& vector, string& ans) {
  int zero = (int)('0');
  string stringNum;
  float decimal;
  for(int num : vector) {
    stringNum = "";
    if(num == 0) {
      stringNum += zero;
    }
    while(num > 0) {
      decimal = ((float)num)/10;
      num /= 10;
      decimal = (decimal - num) * 10;
      stringNum = (char)(decimal + zero) + stringNum;
    }
    ans += "-" + stringNum;
  }
}

/*
 * Determines if a face of Sperner simplex is open based on coloring.
 *
 * @param colors The colors within simplex instance
 * @return Boolean indicating if face is open
 */
bool Face::isOpen(vector<string>& colors){
 unordered_map<string,int> colors_found;

 for (string color : colors) {
   colors_found.insert({color, 0});
 }

 for (Node* node : this->nodes) {
   if (colors_found.find(node->color) != colors_found.end()) {
     colors_found[node->color] += 1;
   } else {
     return false;
   }
 }

 for (string color : colors) {
   if (colors_found[color] != 1) {
     return false;
   }
 }

 return true;
}

/*
 * Finds next face to travel through when searching for Sperner Triangle.
 *
 * @param colors The colors within the sperner simplex
 * @param result Next face found by function
 * @param extra_node Pointer to assign to non-matching node
 */
void Face::findNextFace(vector<string>& colors, Face *& result) {
 vector<Face *> matching_faces;

 for(Node* node : nodes) {
   for(Face* face : node->faces) {
     if(!(face->traversed) && face->isOpen(colors) && face->matchesNodes(nodes)) {
       result = face;
       return;
     }
   }
 }
 result = NULL;
}

/*
 * Checks if a non-matching node exists from parameter matching_nodes.
 *
 * @param matching_nodes Nodes ot search for match
 * @param extra_node Pointer to assign to non-matching node found
 */
bool Face::matchesNodes(vector<Node *>& matching_nodes) {
  // Initialize unordered_map that will contain nodes with no matching node
  unordered_map<string, Node*> match_not_found;
  string key;

  // Fill match_not_found with all nodes initially (matches later removed)
  for(Node* node : nodes) {
    key = "";
    vectorToString(node->x, key);
    match_not_found.insert({key, node});
  }
  int numMatches = 0;
  Node* non_matching_node;
  bool found_match;
  int index;
  vector<Node*> nodes_copy = this->nodes;

  // Iterate over nodes, counting matches and updating matches_not_found
  for(Node* match_node : matching_nodes) {
    found_match = false;
    index = 0;
    for(Node* face_node : nodes_copy) {
      if(match_node == face_node) {
        key = "";
        vectorToString(face_node->x, key);
        if(match_not_found.find(key) != match_not_found.end()) {
          match_not_found.erase(key);
        }
        nodes_copy.erase(nodes_copy.begin()+index);
        found_match = true;
        numMatches++;
        break;
      }
      ++index;
    }
    if(!found_match) {
      non_matching_node = match_node;
    }
  }

  // Check if only one non-matching node exists, otherwise return false
  if(numMatches == static_cast<int>(matching_nodes.size())-1 && static_cast<int>(match_not_found.size()) == 1) {
    Node* new_non_matching_node;
    for(auto n : match_not_found) {
      new_non_matching_node = n.second;
    }
    for(Face* face : new_non_matching_node->faces) {
      for(Node* node : face->nodes) {
        if(node == non_matching_node) {
          return true;
        }
      }
    }
  }
  return false;
}

/*
 * Checks if a specific value (ith-value) of all nodes in a Face are
 * equal to zero.
 *
 * @param i Specific index value to check for zero in each of the face's nodes
 * @return Boolean value indicating if the
 */
 bool Face::ithValIsZero(int i) {
   for(Node* node : nodes) {
     if(node->x[i] != 0) {
       return false;
     }
   }
   return true;
 }

/*
 * Prints the nodes of a Face instance.
 */
 void Face::printFace() {
   for(Node* node : this->nodes) {
     node->printNode();
     cout << " - ";
   }
 }

/*
 * Default destructor for the Face class.
 */
Face::~Face() {}
