#ifndef Ex_ops_h
#define Ex_ops_h

#include "Operator.h"

class Less: public Operator {
  private:
	  Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Greater: public Operator {
  private:
	  Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Leq: public Operator {
  private:
	  Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Geq: public Operator {
  private:
	  Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Equal: public Operator {
  private:
	  Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Ineq: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    void getgrad();
};

class Assert: public Operator_1 {
  private:
	 Tensor calc(set<Node*>& calced) override;
  
  public:
    using Operator_1::Operator_1;
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};

class Bind: public Operator {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator::Operator;
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};

class Cond: public Node {
  protected:
	Tensor calc(set<Node*>& calced) override;
    Node *const co,*const ans1,*const ans2;
  public:
    Cond(Node* node1, Node* node2,Node* node3);
    Node* eval(set<Node*>& calced) override;
    void getgrad();
};
Less* less(Node *a,Node *b);
Greater* greater(Node *a,Node *b);
Leq* leq(Node *a,Node *b);
Geq* geq(Node *a,Node *b);
Equal* equal(Node *a,Node *b);
Ineq* ineq(Node *a,Node *b);
Assert* assert(Node *a);
Bind* bind(Node *a,Node *b);
Cond* cond(Node *a,Node *b,Node *c);

#endif /* Ex_ops_h */
