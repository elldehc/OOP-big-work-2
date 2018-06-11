#ifndef Node_h
#define Node_h

#include <iostream>
#include <set>

using namespace std;

class Node {
  private:
    float value;
  
  public:
    void setvalue(float v);
    float getvalue();
    
    virtual float calc(set<Node*>& calced) = 0;
    virtual Node* eval(set<Node*>& calced) = 0;
    
    friend ostream& operator>> (ostream& out, Node* const nodeptr);
    
    virtual ~Node();
};


#endif /* Node_h */
