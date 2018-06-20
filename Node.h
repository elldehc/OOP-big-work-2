#ifndef Node_h
#define Node_h

#include <iostream>
#include <set>
#include <map>
#include <vector>

using std::map;
using std::set;
using std::cout;
using std::string;
using std::ostream;
using std::endl;

class Node;
class Tensor{
	std::vector<float> data;
	std::vector<int> shape;
	std::vector<int> num; //存储到达这一维度的张量分量的元素个数 num[0]=size
	int size;
	friend class Node;
public:
    Tensor(){}
	Tensor(const float& list);
    Tensor(const std::initializer_list<float>& list, const std::initializer_list<int>& dims);
	~Tensor();
	void _reshape(const std::initializer_list<int>& list);
	void _concat();
	void _transpose();
    Tensor operator+(const Tensor& tr);
    Tensor operator-(const Tensor& tr);
    Tensor operator*(const Tensor& tr);
    Tensor operator/ (const Tensor& tr);
  friend ostream& operator<< (ostream& out, Node* const nodeptr);
  friend ostream &operator<< (ostream& output, const Tensor& tensor);
};

class Node {
  protected:
    Tensor value;
  	map<Node *,Node *> grads;
  public:
    void setvalue(const Tensor& v); 
    void setvalue(const float& v);
    
	Tensor getvalue();
    float getfloat();

	void reshape(const std::initializer_list<int>& list);
	void concat();

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
