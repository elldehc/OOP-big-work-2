#ifndef Ex_ops_h
#define Ex_ops_h

#include "Operator.h"

class Less: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Greater: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Leq: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Geq: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Equal: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Ineq: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Assert: public Operator_1 {
  private:
    float calc(set<Node*>& calced) override;
  
  public:
    using Operator_1::Operator_1;
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};

class Bind: public Operator {
  private:
    float calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};
#endif /* Ex_ops_h */
