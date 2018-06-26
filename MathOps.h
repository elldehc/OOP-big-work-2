#ifndef MathOps_h
#define MathOps_h

#include "Operator.h"
#include<cmath>
const float pi=acos(-1);

class Cos: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Cos* cos(Node *a);

class Sin: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Sin* sin(Node *a);

class Tan: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Tan* tan(Node *a);

class Acos: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Acos* acos(Node *a);

class Asin: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Asin* asin(Node *a);

class Atan: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Atan* atan(Node *a);

class Cosh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Cosh* cosh(Node *a);

class Sinh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Sinh* sinh(Node *a);

class Tanh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Tanh* tanh(Node *a);

class Acosh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Acosh* acosh(Node *a);

class Asinh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Asinh* asinh(Node *a);

class Atanh: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Atanh* atanh(Node *a);

class Exp: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Exp* exp(Node *a);

class Log: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Log* log(Node *a);

class Log10: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Log10* log10(Node *a);

class Exp2: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Exp2* exp2(Node *a);

class Expm1: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Expm1* expm1(Node *a);

class Log1p: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Log1p* log1p(Node *a);

class Log2: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Log2* log2(Node *a);

class Sqrt: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	Node* eval(set<Node*>& calced) override;
	void getgrad();
};
Sqrt* sqrt(Node *a);

class Sqr: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Sqr* sqr(Node *a);

class Erf: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Erf* erf(Node *a);

class Erfc: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Erfc* erfc(Node *a);

class Ceil: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Ceil* ceil(Node *a);

class Floor: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Floor* floor(Node *a);

class Abs: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Abs* abs(Node *a);

class Sgn: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Sgn* sgn(Node *a);

class Sigmoid: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Sigmoid* sigmoid(Node *a);

class Relu: public Operator_1 {
private:
	Tensor calc(set<Node*>& calced) override;
public:
	using Operator_1::Operator_1;
	void getgrad();
};
Relu* relu(Node *a);

class Softmax: public Operator_1 {
  private:
    Tensor calc(set<Node*>& calced) override;

  public:
    using Operator_1::Operator_1;
    void getgrad();
};
Softmax* softmax(Node *a);

#endif 

