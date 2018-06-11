FLAG=-std=c++11 -g -Wall -Wextra
all: main

Node.o:Node.cpp stdops.h
	g++ $(FLAG) -c Node.cpp -o Node.o
nodes.o:nodes.cpp stdops.h
	g++ $(FLAG) -c nodes.cpp -o nodes.o
func.o:func.cpp stdops.h
	g++ $(FLAG) -c func.cpp -o func.o
Operator.o:Operator.cpp stdops.h
	g++ $(FLAG) -c Operator.cpp -o Operator.o
Ops.o:Ops.cpp stdops.h
	g++ $(FLAG) -c Ops.cpp -o Ops.o
Ex_ops.o:Ex_ops.cpp Ex_ops.h
	g++ $(FLAG) -c Ex_ops.cpp -o Ex_ops.o
main.o:main.cpp stdops.h
	g++ $(FLAG) -c main.cpp -o main.o
main:Node.o nodes.o func.o Operator.o Ops.o main.o Ex_ops.o
	g++ $(FLAG) Node.o func.o Operator.o Ops.o main.o nodes.o Ex_ops.o -o main
clean:
	rm *.o main
