#ifndef Node_h
#define Node_h

#include <iostream>
#include <set>
#include <map>


using namespace std;

class Node {
  protected:
    float value;
  	map<Node *,Node *> grads;
  public:
    void setvalue(float v);
    float getvalue();
    virtual float calc(set<Node*>& calced) = 0;
    virtual Node* eval(set<Node*>& calced) = 0;
    virtual void getgrad()=0;
    const map<Node *,Node *>& grad();
    Node * grad(Node *p);
    
    friend ostream& operator>> (ostream& out, Node* const nodeptr);
    
    virtual ~Node();
};
class Constant;
extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;
#endif /* Node_h */
