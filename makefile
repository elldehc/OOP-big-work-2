FLAG=-std=c++11 -Wall -Wextra -O2 -ffast-math -Dnotensor
.PHONY: all clean
all: main learn

Node.o:Node.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c Node.cpp -o Node.o
nodes.o:nodes.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c nodes.cpp -o nodes.o
func.o:func.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c func.cpp -o func.o
Operator.o:Operator.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c Operator.cpp -o Operator.o
Ops.o:Ops.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c Ops.cpp -o Ops.o
Ex_ops.o:Ex_ops.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c Ex_ops.cpp -o Ex_ops.o
MathOps.o:MathOps.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c MathOps.cpp -o MathOps.o	
main.o:main.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c main.cpp -o main.o
learn.o:learn.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c learn.cpp -o learn.o
exam.o:exam.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c exam.cpp -o exam.o
main:Node.o nodes.o func.o Operator.o Ops.o main.o Ex_ops.o MathOps.o
	g++ $(FLAG) Node.o func.o Operator.o Ops.o main.o nodes.o Ex_ops.o MathOps.o -o main
learn:Node.o nodes.o func.o Operator.o Ops.o learn.o Ex_ops.o MathOps.o
	g++ $(FLAG) Node.o func.o Operator.o Ops.o learn.o nodes.o Ex_ops.o MathOps.o -o learn
exam:Node.o nodes.o func.o Operator.o Ops.o exam.o Ex_ops.o MathOps.o
	g++ $(FLAG) Node.o func.o Operator.o Ops.o exam.o nodes.o Ex_ops.o MathOps.o -o exam
clean:
	rm *.o main
