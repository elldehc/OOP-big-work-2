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

#endif /* Operator_h */
