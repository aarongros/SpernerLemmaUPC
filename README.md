# Sperner Lemma Triangulation
This program creates a triangulation of an n-dimensional simplex following Sperner's Lemma. It is accomplished by creating this relationship through nodes(the vertices of the simplex) and through faces(the connection of vertices, for example: a line in n=2, a triangle in n=3, and so on). It colors the nodes randomly based on an inserted seed while following Sperner Lemma's coloring guidelines. To find the cell with the complete set of colors we have programed the door method.

## Instalation
To install first download or clone the repository onto your local machine. Once downloaded, make sure all the files are in the same directory(folder) and compile using the Makefile by using the make command.
```
make
```
or if your don't have the make command execute all the commands in the Makefile individually.
If you have g++ instead of clang replace `clang++` with `g++` in the Makefile.

## Usage
To use, run the executable
```
./main.exe
```
and follow the direction on what to input and the results will follow

## Issues
The triangles are built recursively and when the triangle is large enough this recursion fills the run time stack causing a segmentation fault.
