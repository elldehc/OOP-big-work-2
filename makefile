FLAG=-std=c++11 -Wall -Wextra -g
.PHONY: all clean
all: main learn exam main_old

Node.o:Node.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
nodes.o:nodes.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
func.o:func.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
Operator.o:Operator.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
Ops.o:Ops.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
Ex_ops.o:Ex_ops.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
MathOps.o:MathOps.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
main.o:main.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
learn.o:learn.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
exam.o:exam.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
main_old.o:main_old.cpp Node.h nodes.h Operator.h Ops.h func.h Ex_ops.h MathOps.h
	g++ $(FLAG) -c $< -o $@
main:main.o Node.o nodes.o func.o Operator.o Ops.o Ex_ops.o MathOps.o
	g++ $(FLAG) $^ -o $@
learn:learn.o Node.o nodes.o func.o Operator.o Ops.o Ex_ops.o MathOps.o
	g++ $(FLAG) $^ -o $@
exam:exam.o Node.o nodes.o func.o Operator.o Ops.o Ex_ops.o MathOps.o
	g++ $(FLAG) $^ -o $@
main_old:main_old.o Node.o nodes.o func.o Operator.o Ops.o Ex_ops.o MathOps.o
	g++ $(FLAG) $^ -o $@
	
clean:
	rm *.o main learn exam main_old
