#ifndef numbers_h
#define numbers_h

#include <string>

#include "Node.h"

class Constant: public Node {
  private:
    
  public:
    Constant(const initializer_list<float>& list, const initializer_list<int>& dims);
    Constant(const float& value);
    void getgrad();
    Tensor calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;


class Placeholder: public Node {
  private:
    string name;
    
  public:
    Placeholder(string myname);
    void getgrad();
    Tensor calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

class Print: public Node {
  private:
    Node* dest;
    
  public:
    Print(Node* node);
    void getgrad();
    Tensor calc(set<Node*>& calced) override;
    Node* eval(set<Node*>& calced) override;
};

class Parameter: public Node {
  private:
    Tensor calc(set<Node*>& calced) override;
    
  public:
    Parameter(const Tensor& number);
    void getgrad();
    void set(const Tensor& number);
    void add(const Tensor& number);
    void multiply(const Tensor& number);
    void divide(const Tensor& number);
    void minus(const Tensor& number);
    
    Node* eval(::set<Node*>& calced) override;
};

#endif /* numbers_h */
