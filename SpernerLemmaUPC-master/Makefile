# main: main.cpp
# 	g++ -Wall -g -o test main.cpp
#
# clean:
# 	rm test

EXENAME = main
OBJS = main.o node.o face.o triangle.o spernerTriangle.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

node.o: node.cpp node.h
		  	$(CXX) $(CXXFLAGS) node.cpp

face.o: face.cpp face.h
			  $(CXX) $(CXXFLAGS) face.cpp

triangle.o: triangle.cpp triangle.h
	 		 $(CXX) $(CXXFLAGS) triangle.cpp

spernerTriangle.o: spernerTriangle.cpp spernerTriangle.h
			 $(CXX) $(CXXFLAGS) spernerTriangle.cpp

main.o : main.cpp
			 $(CXX) $(CXXFLAGS) main.cpp

clean:
	-rm -f *.o $(EXENAME)
