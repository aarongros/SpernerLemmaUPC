# Sperner Lemma Triangulation
This program creates a triangulation of an n-dimensional simplex following Sperner's Lemma. It accomplished by creating this relationship through nodes, the verticies of the simplex, and through faces, the connection of vertices(a line in n=2, a triangle in n=3, and so on). It colors the nodes randomly based on a seem while following Sperner Lemma's coloring guidelines. To find the cell with the complete set of colors we have programed the door method.

## Instalation
To install first download or clone the repository onto your local machine. Once downloaded, make sure all the files are in the same directory(folder) and compile using the Makefile by using the make command.
'''
make
'''
or if your don't have the make command use g++
'''
g++ -o main main.cpp
'''

## Usage
To use, run the executable
'''
./main
'''
and follow the direction on what to input and the results will follow
