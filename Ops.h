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

class Transpose: public Operator_1 {
   private:
	 Tensor calc(set<Node*>& calced) override;
   public:
     using Operator_1::Operator_1;
	 void getgrad();
};


/*class Matmul: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};*/

Add* add(Node *a,Node *b);
Minus* sub(Node *a,Node *b);
Minus* minus(Node *a,Node *b);
Multiply* mul(Node *a,Node *b);
Divide* div(Node *a,Node *b);
Power* power(Node *a,Node *b);
#endif /* Ops_h */
