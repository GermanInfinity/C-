CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra
LDFLAGS  = -g3


#
# Here are the rules!  Each rule has a "target" followed by a colon.
# After the colon, is a list of "dependencies" (also called
# "prerequisites") all on one line.  These are files that must already
# exist and be up-to-date before you can make the target.  So, the
# first rule below says that you'd like define how to make a thing
# called "peanutOlympics," and that depends on 4 .o files.  You may follow
# that line with a recipe as a series of one line commands indented
# with a tab character (yes, it must be a tab character!).  In this
# first rule, if you have all the .o files up-to-date, you make a
# peanutOlympics by running clang++ with the flags specified above giving it
# all the .o files and producing leaving the executable output in a
# file named "peanutOlympics."
# 
#

bridges: main.o Island.o Bridges.o Graph.o Stack.o LinkedList.o Queue.o
	${CXX} ${LDFLAGS} -o bridges $^

main.o: main.cpp Island.o Bridges.o Graph.o Stack.o LinkedList.o Queue.o 

Island.o: Island.cpp Island.h
	${CXX} ${CXXFLAGS} -c -o Island.o Island.cpp

Bridges.o: Bridges.cpp Bridges.h
	${CXX} ${CXXFLAGS} -c -o Bridges.o Bridges.cpp

Graph.o: Graph.cpp Graph.h
	${CXX} ${CXXFLAGS} -c -o Graph.o Graph.cpp

Stack.o: Stack.cpp Stack.h
	${CXX} ${CXXFLAGS} -c -o Stack.o Stack.cpp

LinkedList.o: LinkedList.cpp LinkedList.h
	${CXX} ${CXXFLAGS} -c -o LinkedList.o LinkedList.cpp

Queue.o: Queue.cpp Queue.h
	${CXX} ${CXXFLAGS} -c -o Queue.o Queue.cpp


clean:
	rm -rf driver *.o *.dSYM
