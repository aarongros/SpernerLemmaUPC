#include "sperner.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdlib.h>

bool isValidNode(int* cur, int size) {
  int numOnes = 0;
  int numNegOnes = 0;
  int previousNum = 0;
  for(int j = 0; j < size; j++) {
    if(cur[j] != 0) {
      if(cur[j] == 1 && 1 != previousNum) {
        numOnes++;
        previousNum = 1;
        continue;
      }
      if(cur[j] == -1 && -1 != previousNum) {
        numNegOnes++;
        previousNum = -1;
        continue;
      }
      return false;
    }
  }
  if(numOnes != numNegOnes || numOnes == 0) {
    return false;
  }
  return true;
} // works

int addCordinates(int* array, int size) {
  int sum = 0;
  for(int j = 0; j < size; j++) {
    sum += array[j];
  }
  return sum;
} // works

void incrementCordinate(int* cur, int* upper, int* lower, int size) {
  for(int j = size - 1; j >= 0;  j--) {
    if(cur[j] >= upper[j]) {
      cur[j] = lower[j];
    } else {
      cur[j] += 1;
      return;
    }
  }
} // works

bool notEqual(int* cur, int* bound, int size) {
  for(int j = 0; j < size; j++) {
    if(cur[j] != bound[j]) {
      return true;
    }
  }
  return false;
} // works

void arrayToString(int* array, int size, string& ans) {
  int zero = (int)('0');
  int num;
  string stringNum;
  float decimal;
  for(int j = 0; j < size; j++) {
    num = array[j];
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
} // works

void vectorToString(vector<int>& vector, string& ans) {
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
} // works

void combineVectorNodes(int* result, vector<Node*> nodes) {
  int index;
  for(Node* node : nodes) {
    index = 0;
    for(int x : node->x) {
      result[index++] += x;
    }
  }
} //works

void initializeArrToZero(int* array, int size) {
  for(int i = 0; i < size; i++) {
    array[i] = 0;
  }
} // works

void combineVectors(vector<Node*>& result, vector<Node*> vector1, vector<Node*> vector2) {
  for(Node* node : vector1) {
    result.push_back(node);
  }
  for(Node* node : vector2) {
    result.push_back(node);
  }
} // works

void Triangle::initializeBounds(int* upperbound, int* lowerbound, Node* curNode) {
  for(int i = 0; i < k; i++) {
    upperbound[i] = (curNode->x[i] + 1 <= q) ? curNode->x[i] + 1 : curNode->x[i];
    lowerbound[i] = (curNode->x[i] - 1 >= 0) ? curNode->x[i] - 1 : curNode->x[i];
  }
} // works

void Triangle::findNodes(Node* curNode, unordered_map<string, Node*>& nodes_found, unordered_map<string, Face*>& faces_found) {
  // Find upper and lower bounds
  int upperbound[k];
  int lowerbound[k];
  initializeBounds(upperbound, lowerbound, curNode);
  // Initializef the current cordinate
  int curCordinates[k];
  for(int i = 0; i < k; i++) {
    curCordinates[i] = lowerbound[i];
  }
  // Compute the possible nodes
  string mapKey;
  vector<Node*> surrounding_nodes;
  int testValidity[k];
  while(notEqual(curCordinates, upperbound, k)) {
    incrementCordinate(curCordinates, upperbound, lowerbound, k);
    if(addCordinates(curCordinates, k) == q) {
      for(int i = 0; i < k; i++) {
        testValidity[i] = curNode->x[i] - curCordinates[i];
      }
      if(isValidNode(testValidity, k)) {
        mapKey = "";
        arrayToString(curCordinates, k, mapKey);
        if(nodes_found.find(mapKey) != nodes_found.end()) {
          //node exists
          //add node to function list
          surrounding_nodes.push_back(nodes_found[mapKey]);
        } else {
          //create node
          Node* node = new Node(curCordinates, k);
          nodes_found.insert({mapKey, node});
          surrounding_nodes.push_back(node);
          this->all_nodes.push_back(node);
          //Recurse into the node
          this->findNodes(node, nodes_found, faces_found);
        }
      }
    }
  }
  //Find faces
  //Check the number of nodes
  vector<Node*> visited;
  visited.push_back(curNode);
  Node* temp_node;
  if(static_cast<int>(surrounding_nodes.size()) >= k) {
    for(int i = 0; i < static_cast<int>(surrounding_nodes.size()); i++) {
      temp_node = surrounding_nodes[i];
      surrounding_nodes.erase(surrounding_nodes.begin()+i);
      findFaces(temp_node, surrounding_nodes, visited, faces_found);
      surrounding_nodes.insert(surrounding_nodes.begin()+i, temp_node);
    }
  } else {
    //Make Face
    //Combine vectors
    vector<Node*> nodes;
    combineVectors(nodes, visited, surrounding_nodes);
    int combinedValues[k];
    for(int i = 0; i < static_cast<int>(nodes.size()); i++) {
      temp_node = nodes[i];
      nodes.erase(nodes.begin()+i);
      //Check if face exists
      mapKey = "";
      initializeArrToZero(combinedValues, k);
      combineVectorNodes(combinedValues, nodes);
      arrayToString(combinedValues, k, mapKey);
      if(faces_found.find(mapKey) == faces_found.end()) {
        Face* face = new Face(nodes);
        faces_found.insert({mapKey, face});
        this->all_faces.push_back(face);
        for(Node* node : face->nodes) {
          node->faces.push_back(face);
        }
      }
      nodes.insert(nodes.begin()+i, temp_node);
    }
  }
}

void Triangle::findFaces(Node* curNode, vector<Node*> matches, vector<Node*> visited, unordered_map<string, Face*>& faces_made) {
  // Find upper and lower bounds
  visited.push_back(curNode);
  int upperbound[k];
  int lowerbound[k];
  initializeBounds(upperbound, lowerbound, curNode);
  vector<Node*> new_matches;
  bool valid;
  Node* temp_node;
  for(Node* node : matches) {
    valid = true;
    for(int i = 0; i < k; i++) {
      if(node->x[i] > upperbound[i] || node->x[i] < lowerbound[i]) {
        valid = false;
        break;
      }
    }
    if(valid) {
      new_matches.push_back(node);
    }
  }
  if(static_cast<int>(new_matches.size()) + static_cast<int>(visited.size()) > k) {
    for(int i = 0; i < static_cast<int>(new_matches.size()); i++) {
      temp_node = new_matches[i];
      new_matches.erase(new_matches.begin()+i);
      findFaces(temp_node, new_matches, visited, faces_made);
      new_matches.insert(new_matches.begin()+i, temp_node);
    }
  }
  // Check if face exists, if deosn't create face
  else {
    //Make Face
    string mapKey;
    int combinedValues[k];
    vector<Node*> nodes;
    combineVectors(nodes, visited, new_matches);
    for(int i = 0; i < static_cast<int>(nodes.size()); i++) {
      temp_node = nodes[i];
      nodes.erase(nodes.begin()+i);
      //Check if face exists
      mapKey = "";
      initializeArrToZero(combinedValues, k);
      combineVectorNodes(combinedValues, nodes);
      arrayToString(combinedValues, k, mapKey);
      if(faces_made.find(mapKey) == faces_made.end()) {
        Face* face = new Face(nodes);
        faces_made.insert({mapKey, face});
        this->all_faces.push_back(face);
        for(Node* node : face->nodes) {
          node->faces.push_back(face);
        }
      }
      nodes.insert(nodes.begin()+i, temp_node);
    }
  }
  visited.pop_back();
}

Triangle::Triangle(int q_val, int k_val, vector<string> colors, int seed) {
  k = k_val;
  q = q_val;
  srand(seed); // adjusts to be random
  all_colors = colors;

  int nodeValues[k];
  initializeArrToZero(nodeValues, k);
  nodeValues[0] = q;

  string mapKey = "";
  arrayToString(nodeValues, k, mapKey);
  unordered_map<string, Node*> nodes_found;
  Node* node = new Node(nodeValues, k);
  nodes_found.insert({mapKey, node});
  all_nodes.push_back(node);
  unordered_map<string, Face*> faces_found;
  this->findNodes(node, nodes_found, faces_found);
}

Node::Node(int* x_vals, int size) {
  for(int j = 0; j < size; j++) {
    x.push_back(x_vals[j]);
  }
  this->labelVertice(size);
} // works

void Node::labelVertice(int k) {
  int sum = 0;
  for(int j = 1; j <= k ; j++) {
    sum += j * this->x[j-1];
  }
  this->label = sum % k;
} // works

Face::Face(vector<Node*> node_list) {
  traversed = false;
  nodes = node_list;
} // works

Triangle::~Triangle() {
  for(Node* node : all_nodes) {
    delete node;
  }
  for(Face* face : all_faces) {
    delete face;
  }
}

Node::~Node() {}

Face::~Face() {}

int Node::numZeroes() {
  int count = 0;
  for(int x : this->x) {
    if(x == 0) {
      count++;
    }
  }
  return count;
} // works

bool Face::isOpen(vector<string> colors){
  unordered_map<string,int> colors_found;
  for(string color : colors) {
    colors_found.insert({color, 0});
  }
  for(Node* node : this->nodes) {
    if(colors_found.find(node->color) != colors_found.end()) {
      colors_found[node->color] += 1;
    } else {
      return false;
    }
  }
  for(string color : colors) {
    if(colors_found[color] != 1) {
      return false;
    }
  }
  return true;
}

SpernerTriangle::SpernerTriangle(vector<Node*> solution_nodes) {
  nodes = solution_nodes;
} // works

void Triangle::colorTriangle() {
  int randIndex;
  vector<string> valid_colors;
  for(Node* node : all_nodes) {
    for(int  i = 0; i < static_cast<int>(node->x.size()); i++) {
      if(node->x[i] != 0) {
        valid_colors.push_back(all_colors[i]);
      }
    }
    randIndex = rand() % static_cast<int>(valid_colors.size());
    node->color = valid_colors[randIndex];
    valid_colors.clear();
  }
} // works

bool Face::matchesNodes(vector<Node*> matching_nodes) {
  unordered_map<string, Node*> match_not_found;
  string key;
  // Create a vector of the nodes whose match hasn't been found
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

// Computes the factorial of n
int factorial(int n) {
  int sum = 0;
  for(int i = 1; i <= n; i++) {
    sum += i;
  }
  return sum;
} // works

// Finds the next face/door to go through while finding sperner triangles
void Face::findNextFace(vector<string> colors, Face*& result) {
  vector<Face*> matching_faces;
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

// Checks if the ith val of all nodes in the Face are equal to zero
bool Face::ithValIsZero(int i) {
  for(Node* node : nodes) {
    if(node->x[i] != 0) {
      return false;
    }
  }
  return true;
} // works

// Sets face's traversed variable to false
void resetFacesVisited(vector<Face*> faces_visited) {
  for(Face* face : faces_visited) {
    face->traversed = false;
  }
} // works

// Finds missing node to form a sperner triangle
void Node::findMissingNode(Node*& result, int target_label, string target_string) {
  for(Face* face : this->faces) {
    for(Node* node : face->nodes) {
      if(node->label == target_label && node->color == target_string) {
        result = node;
        return;
      }
    }
  }
}

// Finds all the sperner triangles
void Triangle::findSpernerTrangle() {
  unordered_map<string, SpernerTriangle*> sperner_triangles_found;
  vector<Face*> faces_visited;
  string tempColor;
  Face* curFace;
  Face* lastFace;
  int target_label;
  Node* extra_node;
  vector<Node*> sperner_nodes;
  string key;
  int combined_vectors[k];
  // Loop through all the sides of the simplex
  for(int i = 0; i < k; i++) {
    // Remove a color to find find the valid doors
    tempColor = all_colors[i];
    all_colors.erase(all_colors.begin()+i);
    for(Face* face : all_faces) {
      // Check if face hasn't been traversed, if it coresponds with the side and if open
      if(!(face->traversed) && face->ithValIsZero(i) && face->isOpen(all_colors)) {
        //go into face
        curFace = face;
        lastFace = face;
        // Loop until you come back out the simplex or find a sperner triangle
        while(curFace != NULL) {
          faces_visited.push_back(curFace);
          curFace->traversed = true;
          lastFace = curFace;
          curFace->findNextFace(all_colors, curFace);
        }
        // Find the label the missing node must have
        target_label = factorial(k-1);
        for(Node* node : lastFace->nodes) {
          target_label -= node->label;
        }
        extra_node = NULL;
        lastFace->nodes[0]->findMissingNode(extra_node, target_label, tempColor);
        // If a node was found have a sperner triangle, if it wasn't then outside simplex
        if(extra_node != NULL) {
          sperner_nodes = lastFace->nodes;
          sperner_nodes.push_back(extra_node);
          //create Sprener Triangle and add to results
          key = "";
          initializeArrToZero(combined_vectors, k);
          combineVectorNodes(combined_vectors, sperner_nodes);
          arrayToString(combined_vectors, k, key);
          if(sperner_triangles_found.find(key) == sperner_triangles_found.end()) {
            SpernerTriangle* ans = new SpernerTriangle(sperner_nodes);
            sperner_triangles_found.insert({key, ans});
            all_sperner_triangles.push_back(ans);
          }
          sperner_nodes.clear();
        }
      }
    }
    resetFacesVisited(faces_visited);
    faces_visited.clear();
    all_colors.insert(all_colors.begin()+i, tempColor);
  }
}

// Prints nodes from triangles
void Triangle::printAllNodes() {
  cout << "All Nodes:" << endl;
  for(Node* node : this->all_nodes) {
    node->printNode();
    cout << endl;
  }
  cout << endl;
} // works

// Prints cordinates of node
void Node::printNode() {
  for(int cord : this->x) {
    cout << cord << ",";
  }
  cout << this->color << " " << this->label;
} // works

// Prints faces from triangle
void Triangle::printAllFaces() {
  cout << "All Faces:" << endl;
  for(Face* face : this->all_faces) {
    face->printFace();
    cout << endl;
  }
  cout << endl;
} // works

// Prints nodes from face
void Face::printFace() {
  for(Node* node : this->nodes) {
    node->printNode();
    cout << " - ";
  }
} // works

// Prints sperner triangles from triangle
void Triangle::printAllSpernerTriangles() {
  cout << "All Sperner Triagnles:" << endl;
  for(SpernerTriangle* sperner_triangle : this->all_sperner_triangles) {
    sperner_triangle->printSpernerTriangle();
    cout << endl;
  }
  cout << endl;
} // works

// Prints nodes from sperner triangle
void SpernerTriangle::printSpernerTriangle() {
  for(Node* node : nodes) {
    node->printNode();
    cout << " - ";
  }
} // works
