#ifndef numbers_h
#define numbers_h

#include <string>

#include "Node.h"

class Constant: public Node {
  private:
    
  public:
    //Constant(const std::initializer_list<float>& list, const std::initializer_list<int>& dims);
    //Constant(const float& value);
    Constant(const Tensor& value);
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
    Placeholder(string myname="");
    void getgrad();
    Tensor calc(set<Node*>& calced);
    Node* eval(set<Node*>& calced);
};

class Print: public Node {
  private:
    Node* dest;
    string info;
  public:
    Print(Node* node,const string & _info="Print Operator: ");
    void getgrad();
    Tensor calc(set<Node*>& calced) override;
    Node* eval(set<Node*>& calced) override;
};

class Parameter: public Node {
  private:
    Tensor calc(set<Node*>& calced) override;
    
  public:
    Parameter(const Tensor& number);
	Parameter(const float& number);
    void getgrad();
    void set(const Tensor& number);
    void add(const Tensor& number);
    void multiply(const Tensor& number);
    void divide(const Tensor& number);
    void minus(const Tensor& number);
    Node* eval(::set<Node*>& calced) override;
};

extern map<Parameter*,Tensor> assign_map;
class Assign: public Node {
  private:
    Node* src;
    Parameter *tar;
  public:
    Assign(Parameter* para,Node* node);
    void getgrad();
    Tensor calc(set<Node*>& calced) override;
    Node* eval(set<Node*>& calced) override;
};


Constant* constant(const Tensor &a);
//Constant* constant(const std::initializer_list<float>& list, const std::initializer_list<int>& dims);
Placeholder* placeholder(string name="");
Print* print(Node *a,const string &b="Print Operator: ");
Parameter* parameter(const Tensor &a);
Assign* assign(Parameter *para,Node *node);
#endif /* numbers_h */
