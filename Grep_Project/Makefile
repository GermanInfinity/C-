CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra -O2
LDFLAGS  = -g3



gerp: FSTreeTraversal.o Index.o StringProcessing.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o gerp $^

FSTreeTraversal.o: FSTreeTraversal.cpp Index.o StringProcessing.o

Index.o: Index.cpp Index.h StringProcessing.o
	${CXX} ${CXXFLAGS} -c -o Index.o Index.cpp 

StringProcessing.o: StringProcessing.cpp StringProcessing.h
	${CXX} ${CXXFLAGS} -c -o StringProcessing.o StringProcessing.cpp

clean:
	rm -rf driver *.o *.dSYM
