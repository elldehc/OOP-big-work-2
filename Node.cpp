#include "stdops.h"

Tensor::Tensor(const float& list) { //0-dimension tensor
    	size=0;
    	data.push_back(list);
    	shape.push_back(0);
    	num.push_back(0);
}
Tensor::Tensor(const std::initializer_list<float>& list, const std::initializer_list<int>& dims) { //size-dimension tensor
  	  for (auto it=list.begin();it!=list.end();it++){
      	data.push_back(*it);
      }
      int vol=1;
	  for (auto it=dims.begin();it!=dims.end();it++){
      		shape.push_back(*it);
      		vol*=*it;
   		 }
	  size=shape.size();
      for (auto it=shape.begin();it!=shape.end();it++){
      	num.push_back(vol);
      	vol/=*it;
   	     }
    
}
Tensor::~Tensor() {
		data.clear();
		shape.clear();
		num.clear();
}
void Tensor::_reshape(const std::initializer_list<int>& list){
	int req_vol=1;
	for (auto it=list.begin();it!=list.end();it++){
		req_vol*=(*it);
	}
	if (req_vol!=num[0]) {
		std::cout<<"Request `Reshape` invalid"<<std::endl;
		return;
	}
	shape.clear();
	num.clear();
	int vol=1;
	  for (auto it=list.begin();it!=list.end();it++){
      		shape.push_back(*it);
      		vol*=*it;
   		 }
	  size=shape.size();
      for (auto it=shape.begin();it!=shape.end();it++){
      	num.push_back(vol);
      	vol/=*it;
   	     }
}
void Tensor::_concat(){
	size=1;
	shape.clear();
	num.clear();
	shape.push_back(data.size());
	num.push_back(data.size());
}

float Node::getfloat(){
  if (value.size==0) return value.data[0];
  else {
    std::cout<<"Warning: the dimension of tensor bigger than 1"<<std::endl;
    return value.data[0];
  }
}
Tensor Node::getvalue(){
  return value;
}

void Node::reshape(const std::initializer_list<int>& list){
  value._reshape(list);
}
void Node::concat() {
   value._concat();	
}

Tensor Tensor::operator+(const Tensor& tr){
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
              std::cout<<"Warning: (Add) Mismatch"<<std::endl;
              return Tensor();
      }
}
Tensor Tensor::operator-(const Tensor& tr){
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
              std::cout<<"Warning: (Minus) Mismatch"<<std::endl;
              return Tensor();
      }
}
Tensor Tensor::operator*(const Tensor& tr){ //假的乘法
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
                std::cout<<"Warning: (Multiply) Mismatch"<<std::endl;
                return Tensor();
      }
}
Tensor Tensor::operator/(const Tensor& tr){ //假的除法
        if (this->shape == tr.shape) {
        auto r_iter=tr.data.begin();
        for (auto iter=this->data.begin(); iter!=this->data.end(); iter++)
        {
          (*iter)/=(*r_iter);
          r_iter++;
        }  
        return *this;
    }
      else {
              std::cout<<"Warning: (Divide) Mismatch"<<std::endl;
              return Tensor();
      }
}

void Node::setvalue(const Tensor& v) {
    value = v;
}
void Node::setvalue(const float& v) {
   value.size=0;
   value.data.clear();
   value.shape.clear();
   value.num.clear();
   value.data.push_back(v);
   value.shape.push_back(0);
}




const map<Node *,Node *>& Node::grad()
{
	if(grads.empty())getgrad();
	return grads;
}
Node * Node::grad(Node *p)
{
	auto it=grad().find(p);
	if(it==grad().end())return Zero;else return it->second;
}
Node::~Node() {std::cerr<<"Node destroyed.\n"; }
