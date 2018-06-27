#ifndef Node_h
#define Node_h
#pragma GCC optimize("O2")
#pragma GCC optimize("fast-math")

#include <iostream>
#include <set>
#include <map>
#include <vector>
#define float double

using std::map;
using std::set;
using std::cout;
using std::string;
using std::ostream;
using std::endl;
class Maths;
class Node;


class Tensor{
	std::vector<float> data;
	std::vector<int> shape;
	std::vector<int> num; //存储到达这一维度的张量分量的元素个数 num[0]=size
	int size;
	friend class Node;
	friend class Sgn;
	friend class Relu;
	friend Tensor tensor_calc(Tensor ts, const string& str);
	friend Tensor cos(Tensor ts);
	friend Tensor sin(Tensor ts);
	friend Tensor tan(Tensor ts);
	friend Tensor atan(Tensor ts);
	friend Tensor acos(Tensor ts);
	friend Tensor asin(Tensor ts);
	friend Tensor cosh(Tensor ts);
	friend Tensor sinh(Tensor ts);
	friend Tensor tanh(Tensor ts);
	friend Tensor acosh(Tensor ts);
	friend Tensor asinh(Tensor ts);
	friend Tensor atanh(Tensor ts);
	friend Tensor exp(Tensor ts);
	friend Tensor log(Tensor ts);
	friend Tensor log10(Tensor ts);
	friend Tensor exp2(Tensor ts);
	friend Tensor expm1(Tensor ts);
	friend Tensor log1p(Tensor ts);
	friend Tensor log2(Tensor ts);
	friend Tensor sqrt(Tensor ts);
	friend Tensor erf(Tensor ts);
	friend Tensor erfc(Tensor ts);
	friend Tensor ceil(Tensor ts);
	friend Tensor floor(Tensor ts);
	friend Tensor abs(Tensor ts);
public:
    Tensor();
	Tensor(const float& list);
    Tensor(const std::vector<float>& list, const std::vector<int>& dims);
	~Tensor();
	void _reshape(const std::vector<int>& list);
	Tensor _concat(const Tensor& r,int dim=0);
	Tensor _matmul(const Tensor& r);
	void _transpose();
	float& at(const std::vector<int>& dims);
    Tensor operator+(const Tensor& tr);
    Tensor operator-(const Tensor& tr);
    Tensor operator*(const Tensor& tr);
    Tensor operator/ (const Tensor& tr);
    const std::vector<int>& getshape()const;
    void fill(float x);
  friend ostream& operator<< (ostream& out, Node* const nodeptr);
  friend ostream &operator<< (ostream& output, const Tensor& tensor);
};

Tensor tensor_calc(Tensor ts, const string& str);
Tensor cos(Tensor ts);
Tensor sin(Tensor ts);
Tensor tan(Tensor ts);
Tensor atan(Tensor ts);
Tensor acos(Tensor ts);
Tensor asin(Tensor ts);
Tensor cosh(Tensor ts);
Tensor sinh(Tensor ts);
Tensor tanh(Tensor ts);
Tensor acosh(Tensor ts);
Tensor asinh(Tensor ts);
Tensor atanh(Tensor ts);
Tensor exp(Tensor ts);
Tensor log(Tensor ts);
Tensor log10(Tensor ts);
Tensor exp2(Tensor ts);
Tensor expm1(Tensor ts);
Tensor log1p(Tensor ts);
Tensor log2(Tensor ts);
Tensor sqrt(Tensor ts);
Tensor erf(Tensor ts);
Tensor erfc(Tensor ts);
Tensor ceil(Tensor ts);
Tensor floor(Tensor ts);
Tensor abs(Tensor ts);
class Node {
  protected:
    Tensor value;
  	map<Node *,Node *> grads;
  public:
    void setvalue(const Tensor& v); 
    void setvalue(const float& v);
    
	Tensor getvalue();
    float getfloat(const int& seq=0);
	int get_num();
	void reshape(const std::vector<int>& list);
	void transpose();
    virtual Tensor calc(set<Node*>& calced) = 0;
    virtual Node* eval(set<Node*>& calced) = 0;
    virtual void getgrad()=0;
    const map<Node *,Node *>& grad();
    Node * grad(Node *p);
    
    friend ostream& operator>> (ostream& out, const Node*  nodeptr);
    friend ostream& operator>> (ostream& out, const Tensor& tensor);
    virtual ~Node();
};


class Constant;
extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;
#endif /* Node_h */
