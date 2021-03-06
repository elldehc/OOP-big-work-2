#ifndef Ops_h
#define Ops_h

#include "Operator.h"

class Add: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Multiply: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Minus: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Divide: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Power: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;
  
  public:
    using Operator::Operator;
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};

#ifndef notensor
class Transpose: public Operator_1 {
   private:
	 Tensor calc(set<Node*>& calced) override;
   public:
     using Operator_1::Operator_1;
	 void getgrad();
};

class Concat: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;
    int dim;
  public:
    Concat(Node* node1, Node* node2, int _dim=0):Operator(node1, node2), dim(_dim){}
    int get_dim() {return dim;}
    void set_dim(const int& _dim) {dim=_dim;}
    void getgrad();
};

class Reshape: public Operator_1 {
   private:
   Tensor calc(set<Node*>& calced) override;
   std::vector<int> list;
   public:
     Reshape(Node* _op,const std::vector<int>& _list):Operator_1(_op),list(_list){}
     std::vector<int> get_list() {return list;}
     void set_list(const std::vector<int>& _list) {list=_list;}
   void getgrad();
};

class Reshape2: public Operator {
private:
   Tensor calc(set<Node*>& calced) override;
public:
   using Operator::Operator;
   void getgrad();
};

class Matmul: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};
#endif

class Addn: public Operator_n {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator_n::Operator_n;
    void getgrad();
};

Add* add(Node *a,Node *b);
Minus* sub(Node *a,Node *b);
Minus* minus(Node *a,Node *b);
Multiply* mul(Node *a,Node *b);
Divide* div(Node *a,Node *b);
Power* power(Node *a,Node *b);
#ifndef notensor
Transpose* transpose(Node *a);
Concat* concat(Node *a,Node *b,int c);
Reshape* reshape(Node *a,const std::vector<int>& b);
Reshape2* reshape2(Node *a,Node *b);
Matmul* matmul(Node *a,Node *b);
#endif
Addn* addn(const std::vector<Node*> &a);
#endif /* Ops_h */
