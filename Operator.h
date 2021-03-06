#ifndef Operator_h
#define Operator_h

#include "Node.h"
#include "nodes.h"

class Operator: public Node {
  protected:
    Node* left;
    Node* right;
  public:
    Operator(Node* node1, Node* node2);
    Node* getleft();
    Node* getright();
    
    Node* eval(set<Node*>& calced) override;
};

class Operator_1: public Node
{
protected:
	Node *op;
public:
	Operator_1(Node* _op);
	Node* getop();
	Node* eval(set<Node*>& calced) override;
};

class Operator_n: public Node
{
protected:
	std::vector<Node *>op;
public:
	Operator_n(const std::vector<Node*> &_op);
	const std::vector<Node*> & getop();
	Node* eval(set<Node*>& calced) override;
};


#endif /* Operator_h */
