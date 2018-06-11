#ifndef numbers_h
#define numbers_h

#include <string>

#include "Node.h"

class Constant: public Node {
  private:
    
  public:
    Constant(float number);
    
    float calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

class Placeholder: public Node {
  private:
    string name;
    
  public:
    Placeholder(string myname);
    
    float calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

class Print: public Node {
  private:
    Node* dest;
    
  public:
    Print(Node* node);
    
    float calc(set<Node*>& calced) override;
    Node* eval(set<Node*>& calced) override;
};

class Parameter: public Node {
  private:
    float calc(set<Node*>& calced) override;
    
  public:
    Parameter(float number);
    
    void set(float number);
    void add(float number);
    void multiply(float number);
    void divide(float number);
    void minus(float number);
    
    Node* eval(::set<Node*>& calced) override;
};

#endif /* numbers_h */
