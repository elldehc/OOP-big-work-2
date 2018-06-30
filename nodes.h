#ifndef numbers_h
#define numbers_h

#include <string>

#include "Node.h"

class Constant: public Node {
  private:
  	Tensor calc(set<Node*>& calced);
  public:
    //Constant(const std::initializer_list<float>& list, const std::initializer_list<int>& dims);
    //Constant(const float& value);
    Constant(const Tensor& value);
    void getgrad();
    Node* eval(set<Node*>& calced);
};

extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;


class Placeholder: public Node {
  private:
    const string name;
    Tensor calc(set<Node*>& calced);
  public:
    Placeholder(string myname="");
    void getgrad();
    
    Node* eval(set<Node*>& calced);
};

class Print: public Node {
  private:
    Node* const dest;
    const string info;
    Tensor calc(set<Node*>& calced) override;
  public:
    Print(Node* node,const string &_info="");
    void getgrad();
    Node* eval(set<Node*>& calced) override;
};

class Parameter: public Node {
    Tensor calc(set<Node*>& calced) override;
    
  public:
    Parameter(const Tensor& number);
	//Parameter(const float& number);
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
    Node* const src;
    Parameter* const tar;
    Tensor calc(set<Node*>& calced) override;
    
  public:
    Assign(Parameter* para,Node* node);
    void getgrad();
    Node* eval(set<Node*>& calced) override;
};


Constant* constant(const Tensor &a);
//Constant* constant(const std::initializer_list<float>& list, const std::initializer_list<int>& dims);
Placeholder* placeholder(string name="");
Print* print(Node *a,const string &b="");
Parameter* parameter(const Tensor &a);
Assign* assign(Parameter *para,Node *node);
#endif /* numbers_h */
