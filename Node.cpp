#include "stdops.h"
#include<cmath>

Tensor::Tensor() {
	size=0;
}
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

Tensor Tensor::_matmul(const Tensor& r){
	if (size!=2||r.size!=2||shape[1]!=r.shape[0]) { std::cout<<"input invalid!"<<std::endl; return Tensor(); }
	int m=shape[0];
	int n=shape[1];
	int h=r.shape[1]; //m*n n*h;

	Tensor t=Tensor();
	t.size=2;
	t.shape.push_back(m);t.shape.push_back(h); 
	t.num.push_back(m*h); t.num.push_back(h);
	int num;
	for (int i=0;i<m;i++){
		for (int j=0;j<h;j++){
			num=0;
			for (int k=0;k<n;k++){
				num+=data[i*n+k]*r.data[k*h+j];
			}
			t.data.push_back(num);
		}
	}
	return t;
}
Tensor Tensor::_concat(const Tensor& r, int dim){
 	if (dim>size||dim>r.size||size!=r.size) {std::cout<<"input invalid!"<<std::endl; return Tensor();}

 	for (int i=0; i<size; i++) {
 		if (dim!=i&&shape[i]!=r.shape[i]) {std::cout<<"(Concat) Mismatch!"<<std::endl; return Tensor();}
 	}

 	int vol1,vol2;
 	vol1=(dim<size)?num[dim]:1;
 	vol2=(dim<size)?r.num[dim]:1; 
 	Tensor t=Tensor();
 	int il=0,ir=0;
 	while (il<num[0]){
 		for (int j=il; j<il+vol1; j++)
 			t.data.push_back(data[j]);
 		for (int j=ir; j<ir+vol2; j++)
 			t.data.push_back(r.data[j]);
 		il+=vol1;
 		ir+=vol2;
 	}
 	t.size=size;
 	for (int i=0; i<size; i++){
 		if (i==dim) t.shape.push_back(shape[i]+r.shape[i]);
 			else t.shape.push_back(shape[i]);
 		if (i<=dim) t.num.push_back(num[i]+r.num[i]);
 			else t.num.push_back(num[i]);
 	}
 	if (dim==size) {t.shape.push_back(2); t.num.push_back(2); t.size++; }
 	return t;
}
void Tensor::_transpose() {
	int row=shape.size()-2; int line=row+1;
	if (row<0) return;
	
	int mat=num[row];

	row=shape[row]; line=shape[line]; //row and line
	int it=0;
	int* temp= new int [row*line+5];
	while (it<data.size()) {
		for (int i=it; i<it+mat; i++) {
			temp[i-it]=data[i];
		}
		int x = 0;
		int y = 1;
		for (int i=it; i<it+mat; i++) {
			data[i] = temp[x];
			x = x + line;
			if (x>=mat) {x=y; y++; }

		}
		it += mat;
	}
	num[num.size()-1] = row;

	shape[shape.size()-2] = line;
	shape[shape.size()-1] = row;
	delete [] temp;
}
Tensor tensor_calc(Tensor ts, const string& str){
	
		if (str=="cos") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=cos(*it);} 
		else if (str=="sin") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=sin(*it);} 
		else if (str=="tan") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=tan(*it);} 
		else if (str=="atan") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=atan(*it);} 
		else if (str=="acos") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=acos(*it);}
		else if (str=="asin") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=asin(*it);} 
		else if (str=="cosh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=cosh(*it);} 
		else if (str=="sinh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=sinh(*it);} 
		else if (str=="tanh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=tanh(*it);} 
		else if (str=="acosh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=acosh(*it);} 
		else if (str=="asinh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=asinh(*it);} 
		else if (str=="atanh") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=atanh(*it);} 
		else if (str=="exp") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=exp(*it);} 
		else if (str=="log") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=log(*it);}
		else if (str=="log10") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=log10(*it);} 
		else if (str=="exp2") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=exp2(*it);} 
		else if (str=="expm1") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=expm1(*it);} 
		else if (str=="log1p") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=log1p(*it);}
		else if (str=="log2") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=log2(*it);} 
		else if (str=="sqrt") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=sqrt(*it);}
		else if (str=="erf") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=erf(*it);} 
		else if (str=="erfc") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=erfc(*it);} 
		else if (str=="ceil") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=ceil(*it);} 
		else if (str=="floor") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=floor(*it);} 
		else if (str=="abs") for (auto it=ts.data.begin(); it!=ts.data.end();it++) {(*it)=abs(*it);}
	
	return ts;
}
int Node::get_num(){
	return value.num[0];
}

float Node::getfloat(const int& seq){
    if (seq>=value.num[0]) {std::cout<<"Error)  invalid input!"<<std::endl; return value.data[0];}
    return value.data[seq];
}

Tensor Node::getvalue(){
  return value;
}

void Node::reshape(const std::initializer_list<int>& list){
  value._reshape(list);
}


void Node::transpose() {
	value._transpose();
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
              std::cout<<"Warning)  (Add) Mismatch"<<std::endl;
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
              std::cout<<"Warning)  (Minus) Mismatch"<<std::endl;
              return Tensor();
      }
}
Tensor Tensor::operator*(const Tensor& tr){ //�ٵĳ˷�
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
                std::cout<<"Warning)  (Multiply) Mismatch"<<std::endl;
                return Tensor();
      }
}
Tensor Tensor::operator/(const Tensor& tr){ //�ٵĳ���
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
              std::cout<<"Warning)  (Divide) Mismatch"<<std::endl;
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
