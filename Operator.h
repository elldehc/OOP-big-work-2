#ifndef Operator_h
#define Operator_h

#include "Node.h"

class Operator: public Node {
  private:
    Node* left;
    Node* right;
  public:
    Operator(Node* node1, Node* node2);
    Node* getleft();
    Node* getright();
    
    Node* eval(set<Node*>& calced) override;
};

#endif /* Operator_h */
