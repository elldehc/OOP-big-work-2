#ifndef Ops_h
#define Ops_h

#include "Operator.h"

class Add: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    
};

class Multiply: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    
};

class Minus: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
};

class Divide: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
};

class Power: public Operator {
  private:
    float calc(set<Node*>& calced) override;
  
  public:
    using Operator::Operator;
    Node* eval(set<Node*>& calced) override;
};

#endif /* Ops_h */
