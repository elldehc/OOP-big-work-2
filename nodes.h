#ifndef numbers_h
#define numbers_h

#include <string>

#include "Node.h"

class Constant: public Node {
  private:
    
  public:
    Constant(float number);
    void getgrad();
    float calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;


class Placeholder: public Node {
  private:
    string name;
    
  public:
    Placeholder(string myname="");
    void getgrad();
    float calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

class Print: public Node {
  private:
    Node* dest;
    
  public:
    Print(Node* node);
    void getgrad();
    float calc(set<Node*>& calced) override;
    Node* eval(set<Node*>& calced) override;
};

class Parameter: public Node {
  private:
    float calc(set<Node*>& calced) override;
    
  public:
    Parameter(float number);
    void getgrad();
    void set(float number);
    void add(float number);
    void multiply(float number);
    void divide(float number);
    void minus(float number);
    
    Node* eval(::set<Node*>& calced) override;
};

Constant* constant(float a);
Placeholder* placeholder(string name="");
Print* print(Node *a);
Parameter* parameter(float a);
#endif /* numbers_h */
