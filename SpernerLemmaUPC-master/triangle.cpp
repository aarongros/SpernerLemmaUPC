#include "node.h"
#include "face.h"
#include "triangle.h"
#include "spernerTriangle.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * Custom constructor for the Triangle class.
 */
Triangle::Triangle(int q_val, int k_val, vector<string> colors, int seed) {
  k = k_val;
  q = q_val;
  srand(seed); // adjust to be random

  all_colors = colors;

  int nodeValues[k];
  initializeArrToZero(nodeValues, k);
  nodeValues[0] = q;

  string mapKey = "";
  arrayToString(nodeValues, k, mapKey);
  unordered_map<string, Node*> nodes_found;
  Node * node = new Node(nodeValues, k);
  nodes_found.insert({mapKey, node});
  all_nodes.push_back(node);

  unordered_map<string, Face*> faces_found;
  this->findNodes(node, nodes_found, faces_found);
}

/*
 * Sets face's traversed attribute to false.
 *
 * @param faces_visited Faces to set to traversed
 */
void Triangle::resetFacesVisited(vector<Face *> faces_visited) {
  for (Face * face : faces_visited) {
    face->traversed = false;
  }
}

/*
 * Checks if set of nodes has all colors.
 *
 * @param nodes Vector of nodes to check colors of
 * @param numColors Number of colors of current Sperner simplex
 * @return Boolean indicating if all colors are represented
 */
bool Triangle::hasAllColors(vector<Node *>& nodes, int numColors) {
  unordered_map<string, int> colors_found;
  for (Node * node : nodes) {
    if (colors_found.find(node->color) == colors_found.end()) {
      colors_found.insert({node->color, 0});
    }
  }
  if (static_cast<int>(colors_found.size()) == numColors) {
    return true;
  }
  return false;
}

/*
 * Concatenates to vectors into one.
 *
 * @param result pointer to resulting combined vector
 * @param vector1 First vector to concatenate
 * @param vector2 Second vector to concatenate
 */
void Triangle::combineVectors(vector<Node *>& result, vector<Node *> vector1,
                    vector<Node *> vector2) {
  for (Node * node : vector1) {
    result.push_back(node);
  }
  for (Node * node : vector2) {
    result.push_back(node);
  }
}

/*
 * Initializes array pointer to all zeros.
 *
 * @param array Pointer to array to initialize to zero
 * @param size Dimension of the Sperner simplex
 */
void Triangle::initializeArrToZero(int * array, int size) {
  for(int i = 0; i < size; i++) {
    array[i] = 0;
  }
}

/*
 * Adds coordinate vectors of multiple nodes.
 *
 * @param result Pointer to where result vector is stored
 * @param nodes Nodes of which the coordinates should be summed
 */
void Triangle::combineVectorNodes(int * result, vector<Node *> nodes) {
  for(Node * node : nodes) {
    int index = 0;
    for(int x : node->x) {
      result[index++] += x;
    }
  }
}

/*
 * Converts array to string.
 *
 * @param array Pointer to array to convert to a string
 * @param size Dimension of current Sperner simplex
 * @param ans Resulting string from array
 */
void Triangle::arrayToString(int * array, int size, string& ans) {
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
}

/*
 * Checks if coordinates are not equal.
 *
 * @param cur Current node coordinates
 * @param bound Coordinates to compare against
 * @param size Dimension of Sperner simplex
 * @return Boolena indicating if coordinates are not equal.
 */
bool Triangle::notEqual(int * cur, int * bound, int size) {
  for(int j = 0; j < size; j++) {
    if(cur[j] != bound[j]) {
      return true;
    }
  }
  return false;
}

/*
 * Increments a set of node coordinates.
 *
 * @param cur Pointer to current coordinates
 * @param upper Pointer to upper bound of coordinates
 * @param lower Pointer to lower bound of coordinates
 * @param size Dimension of Sperner simplex
 */
void Triangle::incrementCoordinate(int * cur, int * upper, int * lower, int size) {
  for(int j = size - 1; j >= 0;  j--) {
    if(cur[j] >= upper[j]) {
      cur[j] = lower[j];
    } else {
      cur[j] += 1;
      return;
    }
  }
}

/*
 * Adds a set of coordinates together.
 *
 * @param array Pointer to coordinate array
 * @param size Dimension of current Sperner simplex
 * @return Sum of coordinates
 */
int Triangle::addCoordinates(int * array, int size) {
  int sum = 0;
  for(int j = 0; j < size; j++) {
    sum += array[j];
  }
  return sum;
}

/*
 * Checks if node is valid based on Sperner Triangle requirements.
 *
 * @param cur Pointer to current Node coordinates
 * @param size Dimension of current Sperner simplex
 * @return Boolean indicating if node is valid
 */
bool Triangle::isValidNode(int * cur, int size) {
  int numOnes = 0;
  int numNegOnes = 0;
  int previousNum = 0;

  for (int j = 0; j < size; j++) {
    if (cur[j] != 0) {
      if (cur[j] == 1 && 1 != previousNum) {
        numOnes++;
        previousNum = 1;
        continue;
      }
      if (cur[j] == -1 && -1 != previousNum) {
        numNegOnes++;
        previousNum = -1;
        continue;
      }
      return false;
    }
  }
  if (numOnes != numNegOnes || numOnes == 0) {
    return false;
  }
  return true;
}

/*
 * Computes the factorial of n.
 *
 * @param n Number of which to find factorial
 * @return Factorial of n
 */
int Triangle::factorial(int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += i;
  }
  return sum;
}

/*
 * Finds nearby nodes of Sperner simplex.
 *
 * @param curNode Node from which to search for new nodes
 * @param nodes_found Pointer to location where found nodes are to be added
 * @param faces_found Pointer to location where found faces are to be added
 */
 void Triangle::findNodes(Node * curNode,
                          unordered_map<string, Node *>& nodes_found,
                          unordered_map<string, Face *>& faces_found) {
   // Find upper and lower bounds
   int upperbound[k];
   int lowerbound[k];
   initializeBounds(upperbound, lowerbound, curNode);

   // Initialized the current cordinate
   int curCoordinates[k];
   for (int i = 0; i < k; i++) {
     curCoordinates[i] = lowerbound[i];
   }

   // Compute the possible nodes
   vector<Node *> surrounding_nodes;
   while(notEqual(curCoordinates, upperbound, k)) {
     incrementCoordinate(curCoordinates, upperbound, lowerbound, k);
     if (addCoordinates(curCoordinates, k) == q) {
       int testValidity[k];

       for (int i = 0; i < k; i++) {
         testValidity[i] = curNode->x[i] - curCoordinates[i];
       }
       if (isValidNode(testValidity, k)) {
         string mapKey = "";
         arrayToString(curCoordinates, k, mapKey);
         if (nodes_found.find(mapKey) != nodes_found.end()) {
           // Add existant node to function list
           surrounding_nodes.push_back(nodes_found[mapKey]);
         } else {
           // Create node
           Node * node = new Node(curCoordinates, k);
           nodes_found.insert({mapKey, node});
           surrounding_nodes.push_back(node);
           this->all_nodes.push_back(node);

           // Recurse into the node
           this->findNodes(node, nodes_found, faces_found);
         }
       }
     }
   }

   // Check the number of nodes and find faces
   vector<Node *> visited;
   visited.push_back(curNode);

   if (static_cast<int>(surrounding_nodes.size()) >= k) {
     for (int i = 0; i < static_cast<int>(surrounding_nodes.size()); i++) {
       Node * temp_node = surrounding_nodes[i];
       surrounding_nodes.erase(surrounding_nodes.begin()+i);
       findFaces(temp_node, surrounding_nodes, visited, faces_found);
       surrounding_nodes.insert(surrounding_nodes.begin()+i, temp_node);
     }
   } else {
     //Make Face
     //Combine vectors
     vector<Node *> nodes;
     combineVectors(nodes, visited, surrounding_nodes);
     for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
       Node * temp_node = nodes[i];
       nodes.erase(nodes.begin()+i);

       //Check if face exists
       string mapKey = "";
       int combinedValues[k];
       initializeArrToZero(combinedValues, k);
       combineVectorNodes(combinedValues, nodes);
       arrayToString(combinedValues, k, mapKey);

       if (faces_found.find(mapKey) == faces_found.end()) {
         Face * face = new Face(nodes);
         faces_found.insert({mapKey, face});
         this->all_faces.push_back(face);
         for (Node * node : face->nodes) {
           node->faces.push_back(face);
         }
       }
       nodes.insert(nodes.begin()+i, temp_node);
     }
   }
 }

/*
 * Find nearby faces of Sperner simplex.
 *
 * @param curNode Node from which tpo search for faces
 * @param matches Set of nodes to search for potential faces
 * @param visited Pointed to nodes that have already been visited
 * @param faces_made Pointer to new faces created in function
 */
 void Triangle::findFaces(Node * curNode, vector<Node *> matches,
                          vector<Node *> visited,
                          unordered_map<string, Face *>& faces_made) {
   // Find upper and lower bounds
   visited.push_back(curNode);
   int upperbound[k];
   int lowerbound[k];
   initializeBounds(upperbound, lowerbound, curNode);
   vector<Node *> new_matches;
   for (Node * node : matches) {
     bool valid = true;
     for (int i = 0; i < k; i++) {
       if (node->x[i] > upperbound[i] || node->x[i] < lowerbound[i]) {
         valid = false;
         break;
       }
     }
     if (valid) {
       new_matches.push_back(node);
     }
   }
   if (static_cast<int>(new_matches.size()) + static_cast<int>(visited.size()) > k) {
     for (int i = 0; i < static_cast<int>(new_matches.size()); i++) {
       Node * temp_node = new_matches[i];
       new_matches.erase(new_matches.begin()+i);
       findFaces(temp_node, new_matches, visited, faces_made);
       new_matches.insert(new_matches.begin()+i, temp_node);
     }
   } else {
     // Create new face if non-existant
     vector<Node *> nodes;
     combineVectors(nodes, visited, new_matches);
     for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
       Node * temp_node = nodes[i];
       nodes.erase(nodes.begin()+i);

       //Check if face exists
       string mapKey = "";
       int combinedValues[k];
       initializeArrToZero(combinedValues, k);
       combineVectorNodes(combinedValues, nodes);
       arrayToString(combinedValues, k, mapKey);

       if (faces_made.find(mapKey) == faces_made.end()) {
         Face * face = new Face(nodes);
         faces_made.insert({mapKey, face});
         this->all_faces.push_back(face);

         for (Node * node : face->nodes) {
           node->faces.push_back(face);
         }
       }
       nodes.insert(nodes.begin()+i, temp_node);
     }
   }
   visited.pop_back();
 }

/*
 * Initializes bounds in which to search for new nodes.
 *
 * @param upperbound Pointer to array defining coordinates upper bound
 * @param lowerbound Pointer to array defining coordinates lower bound
 * @param k Dimension of Sperner simplex
 * @param curNode Node to base bounds off of
 */
void Triangle::initializeBounds(int * upperbound, int * lowerbound,
                                Node * curNode) {
 for (int i = 0; i < k; i++) {
   upperbound[i] = (curNode->x[i] + 1 <= q) ? curNode->x[i] + 1 : curNode->x[i];
   lowerbound[i] = (curNode->x[i] - 1 >= 0) ? curNode->x[i] - 1 : curNode->x[i];
 }
}

/*
 * Colors vertices of Sperner simplex.
 */
void Triangle::colorTriangle() {
  for (Node * node : all_nodes) {
    vector<string> valid_colors;
    for (int  i = 0; i < static_cast<int>(node->x.size()); i++) {
      if (node->x[i] != 0) {
        valid_colors.push_back(all_colors[i]);
      }
    }
    int randIndex = rand() % static_cast<int>(valid_colors.size());
    node->color = valid_colors[randIndex];
  }
}

/*
 * Finds all Sperner Triangles in Sperner simplex.
 */
void Triangle::findSpernerTriangle() {
 unordered_map<string, SpernerTriangle *> sperner_triangles_found;

  for (int i = 0; i < k; i++) {
    vector<Face *> faces_visited;
    string tempColor = all_colors[i];
    all_colors.erase(all_colors.begin()+i);

    for (Face * face : all_faces) {
      if (!(face->traversed) && face->ithValIsZero(i) && face->isOpen(all_colors)) {
        // Go into face
        Face* curFace = face;
        Face* lastFace = face;
        Node* extra_node = NULL;

        while(curFace != NULL) {
          faces_visited.push_back(curFace);
          curFace->traversed = true;
          lastFace = curFace;
          curFace->findNextFace(all_colors, curFace, extra_node);
        }

        int target_label = factorial(k-1);
        for (Node* node : lastFace->nodes) {
          target_label -= node->label;
        }

        vector<Node*> possible_extra_nodes;
        for (Node* node : lastFace->nodes) {
          for (Face* face : node->faces) {
            for (Node* node2 : face->nodes) {
              if (node2->label == target_label) {
                possible_extra_nodes.push_back(node2);
              }
            }
          }
        }
        vector<Node*> sperner_nodes;
        sperner_nodes = lastFace->nodes;

        for (Node * node : possible_extra_nodes) {
          sperner_nodes.push_back(node);

          if (hasAllColors(sperner_nodes, k)) {
            //create Sprener Triangle and add to results
            string key = "";
            int combined_vectors[k];
            initializeArrToZero(combined_vectors, k);
            combineVectorNodes(combined_vectors, sperner_nodes);
            arrayToString(combined_vectors, k, key);
            if (sperner_triangles_found.find(key) == sperner_triangles_found.end()) {
              SpernerTriangle * ans = new SpernerTriangle(sperner_nodes);
              sperner_triangles_found.insert({key, ans});
              all_sperner_triangles.push_back(ans);
            }
          }
          sperner_nodes.pop_back();
        }
      }
    }
    resetFacesVisited(faces_visited);
    all_colors.insert(all_colors.begin()+i, tempColor);
  }
}

/*
 * Print attributes of all nodes within a traingle.
 */
void Triangle::printAllNodes() {
  cout << "All Nodes:" << endl;
  for (Node * node : this->all_nodes) {
    node->printNode();
    cout << endl;
  }
  cout << endl;
}

/*
 * Prints all faces of a triangle.
 */
void Triangle::printAllFaces() {
  cout << "All Faces:" << endl;
  for (Face * face : this->all_faces) {
    face->printFace();
    cout << endl;
  }
  cout << endl;
}

/*
 * Print all Sperner Triangles from Sperner simplex instance.
 */
void Triangle::printAllSpernerTriangles() {
  cout << "All Sperner Triagnles:" << endl;
  for (SpernerTriangle * sperner_triangle : this->all_sperner_triangles) {
    sperner_triangle->printSpernerTriangle();
    cout << endl;
  }
  cout << endl;
}

/*
 * Destructor for Triangle class.
 */
Triangle::~Triangle() {
  for (Node * node : all_nodes) {
    delete node;
  }
  for (Face * face : all_faces) {
    delete face;
  }
}
