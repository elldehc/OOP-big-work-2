FLAG=-std=c++11
all: main

Node.o:Node.cpp Node.h
	g++ $(FLAG) -c Node.cpp -o Node.o
nodes.o:nodes.cpp nodes.h
	g++ $(FLAG) -c nodes.cpp -o nodes.o
func.o:func.cpp func.h
	g++ $(FLAG) -c func.cpp -o func.o
Operator.o:Operator.cpp Operator.h
	g++ $(FLAG) -c Operator.cpp -o Operator.o
Ops.o:Ops.cpp Ops.h
	g++ $(FLAG) -c Ops.cpp -o Ops.o
main.o:main.cpp
	g++ $(FLAG) -c main.cpp -o main.o
main:Node.o nodes.o func.o Operator.o Ops.o main.o
	g++ $(FLAG) Node.o func.o Operator.o Ops.o main.o nodes.o -o main
clean:
	rm *.o main
