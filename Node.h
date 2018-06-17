#ifndef Node_h
#define Node_h

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Node;
class Tensor{
	vector<float> data;
	vector<int> shape;
    vector<int> num; //存储到达这一维度的张量分量的元素个数 num[0]=size
  friend class Node;
	int size;
  //
public:
  Tensor(){}
	Tensor(const float& list) {
    	size=0;
    	data.push_back(list);
    	shape.push_back(0);
    	num.push_back(0);
	}

  Tensor(const initializer_list<float>& list, const initializer_list<int>& dims) {
  	  for (auto it=list.begin();it!=list.end();it++)
   	  {
      	data.push_back(*it);
      }
      int vol=1;
    	for (auto it=dims.begin();it!=dims.end();it++)
    	{
      		shape.push_back(*it);
      		vol*=*it;
   		 }
    	size=shape.size();
    	for (auto it=shape.begin();it!=shape.end();it++)
    	{
      	num.push_back(vol);
      	vol/=*it;
   		 }
    
  }
	~Tensor() {
		data.clear();
		shape.clear();
		num.clear();
	}
  Tensor operator+(const Tensor& tr){


    if (this->shape == tr.shape) {
        auto r_iter=tr.data.begin();
        for (auto iter=this->data.begin(); iter!=this->data.end(); iter++)
        {
          (*iter)+=(*r_iter);
          r_iter++;
        }  

        return *this;
    }
      else {
              cout<<"(Add) Mismatch"<<endl;
              return Tensor();
      }
  }
    Tensor operator-(const Tensor& tr){
    if (this->shape == tr.shape) {
        auto r_iter=tr.data.begin();
        for (auto iter=this->data.begin(); iter!=this->data.end(); iter++)
        {
          (*iter)-=(*r_iter);
          r_iter++;
        }  
        return *this;
    }
      else {
              cout<<"(Minus) Mismatch"<<endl;
              return Tensor();
      }
  }
  Tensor operator*(const Tensor& tr){ //假的乘法
        if (this->shape == tr.shape) {
        auto r_iter=tr.data.begin();
        for (auto iter=this->data.begin(); iter!=this->data.end(); iter++)
        {
          (*iter)*=(*r_iter);
          r_iter++;
        }  
        return *this;
    }
      else {
      			cout<<this->shape.size()<<' '<<tr.shape.size()<<endl;
      			cout<<this->shape[0]<<' '<<tr.shape[0]<<endl;
      			cout<<this->data[0]<<' '<<tr.data[0]<<endl;
              cout<<"(Multiply) Mismatch"<<endl;
              return Tensor();
      }
  }
    Tensor operator/ (const Tensor& tr){ //假的除法
        if (this->shape == tr.shape) {
        auto r_iter=tr.data.begin();
        for (auto iter=this->data.begin(); iter!=this->data.end(); iter++)
        {
          (*iter)*=(*r_iter);
          r_iter++;
        }  
        return *this;
    }
      else {
              cout<<"(Divide) Mismatch"<<endl;
              return Tensor();
      }
  }
  friend ostream& operator<< (ostream& out, Node* const nodeptr);
  friend ostream &operator<< (ostream& output , const Tensor& tensor);
  };


class Node {
  protected:
  	Tensor value;
  	map<Node *,Node *> grads;
  public:
    void setvalue(const Tensor& v); 
    Tensor getvalue();
    virtual Tensor calc(set<Node*>& calced) = 0;
    virtual Node* eval(set<Node*>& calced) = 0;
    virtual void getgrad()=0;
    const map<Node *,Node *>& grad();
    Node * grad(Node *p);
    
    friend ostream& operator>> (ostream& out, Node* const nodeptr);
	friend ostream& operator>> (ostream& out, const Tensor& tensor);
    virtual ~Node();
};
class Constant;
extern Constant* const Zero;
extern Constant* const One;
extern Constant* const MinusOne;
#endif /* Node_h */
