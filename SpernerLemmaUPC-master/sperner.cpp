#include <unordered_map>
#include <vector>
#include <string>

#include "node.h"
#include "face.h"
#include "triangle.h"
#include "sperner.hpp"

using namespace std;

/*
 * Custom constructor for Sperner Triangle
 *
 * @param solution_nodes Valid Sperner Traingle nodes
 */
SpernerTriangle::SpernerTriangle(vector<Node*> solution_nodes) {
  for(Node* node : solution_nodes) {
    this->nodes.push_back(node);
  }
}


//------------------------------------------------------------

//
// void findMissingNode(vector<Node*> sperner_nodes) {
//
// }

// void Triangle::findSpernerTrangle() {
//    vector<Face*> faces_traversed;
//    for(int i = 0; i < k; i++) {
//      string tempColor = all_colors[i];
//      all_colors.erase(all_colors.begin()+i);
//      for(Face* face : all_faces) {
//        if(!(face->traversed) && face->ithValIsZero(i) && face->isOpen(all_colors)) {
//          //go into face
//          Face* curFace = face;
//          Face* lastFace = face;
//          face->traversed = true;
//          while(curFace != NULL) {
//            lastFace = curFace;
//            curFace->findNextFace(all_colors, curFace);
//          }
//          if(hasAllColors) { //not right
//            //create Sprener Triangle and add to resultsw
//            vector<Node*> sperner_nodes;
//            copyVector(sperner_nodes, lastFace->nodes);
//
//            SpernerTriangle* ans = new SpernerTriangle();
//            all_sperner_triangles.push_back(ans);
//          }
//        }
//      }
//      all_colors.insert(all_colors.begin()+i, tempColor);
//    }
// }
