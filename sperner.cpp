#include "sperner.hpp"
#include <unordered_map>
#include <vector>
#include <string>

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
      break;
    }
  }
}

bool notEqual(int* cur, int* bound, int size) {
  for(int j = 0; j < size; j++) {
    if(cur[j] != bound[j]) {
      return true;
    }
  }
  return false;
}

void arrayToString(int* array, int size, string& ans) {
  int zero = (int)('0');
  for(int j = 0; j < size; j++) {
    int num = array[j];
    string stringNum = "";
    if(num == 0) {
      stringNum += zero;
    }
    while(num > 0) {
      float decimal = ((float)num)/10;
      num /= 10;
      decimal = (decimal - num) * 10;
      stringNum = (char)(decimal + zero) + stringNum;
    }
    ans += "-" + stringNum;
  }
} // works

void vectorToString(vector<int>& vector, string& ans) {
  int zero = (int)('0');
  for(int num : vector) {
    string stringNum = "";
    if(num == 0) {
      stringNum += zero;
    }
    while(num > 0) {
      float decimal = ((float)num)/10;
      num /= 10;
      decimal = (decimal - num) * 10;
      stringNum = (char)(decimal + zero) + stringNum;
    }
    ans += "-" + stringNum;
  }
} // works but not needed

void combineVectorNodes(int* result, vector<Node*> nodes) {
  for(Node* node : nodes) {
    int index = 0;
    for(int x : node->x) {
      result[index] += x;
      index++;
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
}

void Triangle::initializeBounds(int* upperbound, int* lowerbound, int k, Node* curNode) {
  for(int i = 0; i < k; i++) {
    upperbound[i] = (curNode->x[i] + 1 <= q) ? curNode->x[i] + 1 : curNode->x[i];
    lowerbound[i] = (curNode->x[i] - 1 >= 0) ? curNode->x[i] - 1 : curNode->x[i];
  }
}

void Triangle::findNodes(Node* curNode, unordered_map<string, Node*>& nodes_found, unordered_map<string, Face*>& faces_found) {
  // Find upper and lower bounds
  int upperbound[k];
  int lowerbound[k];
  initializeBounds(upperbound, lowerbound, k, curNode);
  // Initializef the current cordinate
  int curCordinates[k];
  for(int i = 0; i < k; i++) {
    curCordinates[i] = lowerbound[i];
  }
  // Compute the possible nodes
  vector<Node*> surrounding_nodes;
  while(notEqual(curCordinates, upperbound, k)) {
    incrementCordinate(curCordinates, upperbound, lowerbound, k);
    if(addCordinates(curCordinates, k) == q) {
      int testValidity[k];
      for(int i = 0; i < k; i++) {
        testValidity[i] = curNode->x[i] - curCordinates[i];
      }
      if(isValidNode(testValidity, k)) {
        string mapKey = "";
        arrayToString(curCordinates, k, mapKey);
        if(nodes_found.find(mapKey) != nodes_found.end()) {
          //node exists
          //add node to function list
          Node* nodeFound = nodes_found[mapKey];
          surrounding_nodes.push_back(nodeFound);
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
  if(static_cast<int>(surrounding_nodes.size()) >= k) {
    for(int i = 0; i < static_cast<int>(surrounding_nodes.size()); i++) {
      Node* temp_node = surrounding_nodes[i];
      surrounding_nodes.erase(surrounding_nodes.begin()+i);
      findFaces(temp_node, surrounding_nodes, visited, faces_found);
      surrounding_nodes.insert(surrounding_nodes.begin()+i, temp_node);
    }
  } else {
    //Make Face
    //Combine vectors
    vector<Node*> nodes;
    combineVectors(nodes, visited, surrounding_nodes);
    for(int i = 0; i < static_cast<int>(nodes.size()); i++) {
      Node* temp_node = nodes[i];
      nodes.erase(nodes.begin()+i);
      //Check if face exists
      string mapKey = "";
      int combinedValues[k];
      initializeArrToZero(combinedValues, k);
      combineVectorNodes(combinedValues, nodes);
      arrayToString(combinedValues, k, mapKey);
      if(faces_found.find(mapKey) == faces_found.end()) {
        Face* face = new Face(nodes);
        faces_found.insert({mapKey, face});
        this->all_faces.push_back(face);
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
  initializeBounds(upperbound, lowerbound, k, curNode);
  vector<Node*> new_matches;
  for(Node* node : matches) {
    bool valid = true;
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
      Node* temp_node = new_matches[i];
      new_matches.erase(new_matches.begin()+i);
      findFaces(temp_node, new_matches, visited, faces_made);
      new_matches.insert(new_matches.begin()+i, temp_node);
    }
  }
  //create face
  //Check if face exists
  //if deosn't create
  else {
    //Make Face
    vector<Node*> nodes;
    combineVectors(nodes, visited, new_matches);
    for(int i = 0; i < static_cast<int>(nodes.size()); i++) {
      Node* temp_node = nodes[i];
      nodes.erase(nodes.begin()+i);
      //Check if face exists
      string mapKey = "";
      int combinedValues[k];
      initializeArrToZero(combinedValues, k);
      combineVectorNodes(combinedValues, nodes);
      arrayToString(combinedValues, k, mapKey);
      if(faces_made.find(mapKey) == faces_made.end()) { // fix array to int
        Face* face = new Face(nodes);
        faces_made.insert({mapKey, face}); // fix vect to int
        this->all_faces.push_back(face);
      }
      nodes.insert(nodes.begin()+i, temp_node);
    }
  }
  visited.pop_back();
}

Triangle::Triangle(int q_val, int k_val, vector<string> colors) {
  k = k_val;
  q = q_val;

  for(string color : colors) {
    all_colors.push_back(color);
  }

  int nodeValues[k];
  nodeValues[0] = q;
  for(int j = 1; j < k; j++) {
    nodeValues[j] = 0;
  }
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
}

void Node::labelVertice(int k) {
  int sum = 0;
  for(int j = 1; j <= k ; j++) {
    sum += j * this->x[j-1];
  }
  this->label = sum % k;
}

Face::Face(vector<Node*> node_list) {
  traversed = false;
  for(Node* node : node_list) {
    nodes.push_back(node);
  }
}

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
}

bool Node::isColored() {
  if(this->color == "")
      return false;
  return true;
}

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

bool Face::hasAllColors(int numColors) {
  unordered_map<std::string, int> colors_found;
  for(Node* node : this->nodes) {
    if(colors_found.find(node->color) == colors_found.end()) {
      colors_found.insert({node->color, 0});
    }
  }
  if(static_cast<int>(colors_found.size()) == numColors) {
    return true;
  }
  return false;
}

SpernerTriangle::SpernerTriangle(vector<Node*> solution_nodes) {
  for(Node* node : solution_nodes) {
    this->nodes.push_back(node);
  }
}

void Triangle::colorTriangle() {
  srand(1); // adjust to be random
  for(Node* node : all_nodes) {
    vector<string> valid_colors;
    for(int  i = 0; i < static_cast<int>(node->x.size()); i++) {
      if(node->x[i] != 0) {
        valid_colors.push_back(all_colors[i]);
      }
      int randIndex = rand() % static_cast<int>(valid_colors.size());
      node->color = valid_colors[randIndex];
    }
  }
}

bool Face::matchesNodes(vector<Node*> matching_nodes) {
  int numMatches = 0;
  for(Node* match_node : matching_nodes) {
    for(Node* face_node : nodes) {
      if(match_node == face_node) {
        numMatches++;
      }
    }
  }
  if(numMatches >= static_cast<int>(matching_nodes.size())-1) {
    return true;
  }
  return false;
}

void Face::findNextFace(vector<string> colors, Face*& result) {
  for(Node* node : nodes) {
    for(Face* face : node->faces) {
      if(face->matchesNodes(nodes)) {
        if(face->isOpen(colors) && !(face->traversed)) {
          result = face;
          return;
        }
      }
    }
  }
  result = NULL;
}

bool Face::ithValIsZero(int i) {
  for(Node* node : nodes) {
    if(node->x[i] != 0) {
      return false;
    }
  }
  return true;
}
void copyVector(vector<Node*>& target, vector<Node*> original) {
  for(Node* node : original) {
    target.push_back(node);
  }
}

void findMissingNode(vector<Node*> sperner_nodes, ) {
  
}

void Triangle::findSpernerTrangle() {
   vector<Face*> faces_traversed;
   for(int i = 0; i < k; i++) {
     string tempColor = all_colors[i];
     all_colors.erase(all_colors.begin()+i);
     for(Face* face : all_faces) {
       if(!(face->traversed) && face->ithValIsZero(i) && face->isOpen(all_colors)) {
         //go into face
         Face* curFace = face;
         Face* lastFace = face;
         face->traversed = true;
         while(curFace != NULL) {
           lastFace = curFace;
           curFace->findNextFace(all_colors, curFace);
         }
         if(hasAllColors) { //not right
           //create Sprener Triangle and add to resultsw
           vector<Node*> sperner_nodes;
           copyVector(sperner_nodes, lastFace->nodes);

           SpernerTriangle* ans = new SpernerTriangle();
           all_sperner_triangles.push_back(ans);
         }
       }
     }
     all_colors.insert(all_colors.begin()+i, tempColor);
   }
}
