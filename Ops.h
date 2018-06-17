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
/*class Power: public Operator {
  private:
    float calc(set<Node*>& calced) override;
  
  public:
    using Operator::Operator;
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};*/

#endif /* Ops_h */
