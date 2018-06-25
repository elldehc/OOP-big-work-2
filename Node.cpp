#include "stdops.h"
#include<cmath>

#ifndef notensor
Tensor::Tensor() {
	size=0;
}
Tensor::Tensor(const float& list) { //0-dimension tensor
    	size=0;
    	data.push_back(list);
    	//shape.push_back(0);
    	num.push_back(1);
}
Tensor::Tensor(const std::vector<float>& list, const std::vector<int>& dims) { //size-dimension tensor
  	  for (auto it=list.begin();it!=list.end();it++){
      	data.push_back(*it);
      }
      int vol=1;
	  for (auto it=dims.begin();it!=dims.end();it++){
      		shape.push_back(*it);
      		vol*=*it;
   		 }
   		data.resize(vol);
	  size=shape.size();
      for (auto it=shape.begin();it!=shape.end();it++){
      	num.push_back(vol);
      	vol/=*it;
   	     }
   	  num.push_back(1);
    
}
Tensor::~Tensor() {
		data.clear();
		shape.clear();
		num.clear();
}
void Tensor::_reshape(const std::vector<int>& list){
	int req_vol=1;
	for (auto it=list.begin();it!=list.end();it++){
		req_vol*=(*it);
	}
	if (req_vol!=num[0]) {
		data.resize(req_vol);
		//std::cout<<"Request `Reshape` invalid"<<std::endl;
		//return;
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
   	  num.push_back(1);
}

Tensor Tensor::_matmul(const Tensor& r){
	if(size==2&&r.size==2)
	{
		if (shape[1]!=r.shape[0]) { std::cout<<"matmul:input invalid!"<<std::endl; return Tensor(); }
		int m=shape[0];
		int n=shape[1];
		int h=r.shape[1]; //m*n n*h;

		Tensor t=Tensor();
		t.data.clear();
		t.size=2;
		t.shape.push_back(m);t.shape.push_back(h); 
		t.num.push_back(m*h); t.num.push_back(h);t.num.push_back(1);
		float num;
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
	else if(size==0&&r.size==2)
	{
		Tensor t=r;
		for(int i=0;i<t.num[0];i++)t.data[i]*=data[0];
		return t;
	}
	else if(size==2&&r.size==0)
	{
		Tensor t=*this;
		for(int i=0;i<t.num[0];i++)t.data[i]*=r.data[0];
		return t;
	}
	else if(size==1&&r.size==2)
	{
		if(shape[0]!=r.shape[0]){ std::cout<<"matmul:input invalid!"<<std::endl; return Tensor(); }
		Tensor t=*this;
		for(int i=0;i<shape[0];i++)
		{
			t.data[i]=0;
			for(int j=0;j<r.shape[1];j++)t.data[i]+=data[i]*r.data[i*r.num[1]+j];
		}
		return t;
	}
	else if(size==2&&r.size==1)
	{
		if(shape[1]!=r.shape[0]){ std::cout<<"matmul:input invalid!"<<std::endl; return Tensor(); }
		Tensor t=r;
		for(int i=0;i<r.shape[0];i++)
		{
			t.data[i]=0;
			for(int j=0;j<shape[0];j++)t.data[i]+=data[j*num[1]+i]*r.data[i];
		}
		return t;
	}
	else { std::cout<<"matmul:input invalid!"<<std::endl; return Tensor(); }
}
Tensor Tensor::_concat(const Tensor& r, int dim){
 	if (dim>size||dim>r.size||size!=r.size) {std::cout<<"concat:input invalid!"<<std::endl; return Tensor();}

 	for (int i=0; i<size; i++) {
 		if (dim!=i&&shape[i]!=r.shape[i]) {std::cout<<"(Concat) Mismatch!"<<std::endl; return Tensor();}
 	}

 	int vol1,vol2;
 	vol1=(dim<size)?num[dim]:1;
 	vol2=(dim<size)?r.num[dim]:1; 
 	Tensor t=Tensor();
 	if(size==0)return Tensor({data[0],r.data[0]},{2});
 	t.data.clear();
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
 	num.push_back(1);
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
	num[num.size()-2] = row;

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

#else
float Node::getfloat(const int& seq){
    return value;
}

int Node::get_num(){
	return 0;
}

Tensor tensor_calc(Tensor ts, const string& str){
	
		if (str=="cos") return cos(ts);
		else if (str=="sin") return sin(ts);
		else if (str=="tan") return tan(ts);
		else if (str=="atan") return atan(ts);
		else if (str=="acos") return acos(ts);
		else if (str=="asin") return asin(ts);
		else if (str=="cosh") return cosh(ts);
		else if (str=="sinh") return sinh(ts);
		else if (str=="tanh") return tanh(ts);
		else if (str=="acosh") return acosh(ts);
		else if (str=="asinh") return asinh(ts);
		else if (str=="atanh") return atanh(ts);
		else if (str=="exp") return exp(ts);
		else if (str=="log") return log(ts);
		else if (str=="log10") return log10(ts);
		else if (str=="exp2") return exp2(ts);
		else if (str=="expm1") return expm1(ts);
		else if (str=="log1p") return log1p(ts);
		else if (str=="log2") return log2(ts);
		else if (str=="sqrt") return sqrt(ts);
		else if (str=="erf") return erf(ts);
		else if (str=="erfc") return erfc(ts);
		else if (str=="ceil") return ceil(ts);
		else if (str=="floor") return floor(ts);
		else if (str=="abs") return abs(ts);
	
	return ts;
}
#endif


Tensor Node::getvalue(){
  return value;
}

#ifndef notensor
void Node::reshape(const std::vector<int>& list){
  value._reshape(list);
}


void Node::transpose() {
	value._transpose();
}

float& Tensor::at(const std::vector<int>& dims)
{
	int s=0;
	int i,j,k;
	auto it=dims.begin();
	for(i=1;it!=dims.end()&&i<shape.size();it++,i++)s+=num[i]*(*it);
	s+=*it;
	return data[s];
}
const std::vector<int>& Tensor::getshape()const{return shape;}	
Tensor Tensor::operator+(const Tensor& tr){
    /*if (this->shape == tr.shape) {
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
      }*/
    int i,j,k;
	Tensor ans;
	ans.size=size>tr.size?size:tr.size;
	ans.shape.resize(ans.size);
	for(i=0;i<ans.size;i++)
	{
		if(i>=size)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else if(i>=tr.size)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==shape[size-i-1])ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==1)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(shape[size-i-1]==1)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else{std::cerr<<"Error in +:sizes don't match.\n";return ans;}
	}
	ans.num.resize(ans.size+1);
	ans.num[ans.size]=1;
	for(i=ans.size-1;i>=0;i--)ans.num[i]=ans.num[i+1]*ans.shape[i];
	ans.data.resize(ans.num[0]);
	std::vector<int> ind(ans.size);
	int w1=0,w2=0;
	for(i=0;i<ans.num[0];i++)
	{
		ans.data[i]=data[w1]+tr.data[w2];
		for(j=0;j<ans.size;j++)
		{
			ind[ans.size-1-j]++;
			if(size>0&&shape[size-1-j]>1)w1+=num[size-j];
			if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2+=tr.num[tr.size-j];
			if(ind[ans.size-1-j]>=ans.num[ans.size-1-j])
			{
				ind[ans.size-1-j]-=ans.num[ans.size-1-j];
				if(size>0&&shape[size-1-j]>1)w1-=ans.num[ans.size-1-j]*num[size-j];
				if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2-=ans.num[ans.size-1-j]*tr.num[tr.size-j];
			}
			else break;
		}
	}
	return ans;
}
			
Tensor Tensor::operator-(const Tensor& tr){
    /*if (this->shape == tr.shape) {
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
      }*/
	int i,j,k;
	Tensor ans;
	ans.size=size>tr.size?size:tr.size;
	ans.shape.resize(ans.size);
	for(i=0;i<ans.size;i++)
	{
		if(i>=size)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else if(i>=tr.size)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==shape[size-i-1])ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==1)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(shape[size-i-1]==1)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else{std::cerr<<"Error in -:sizes don't match.\n";return ans;}
	}
	ans.num.resize(ans.size+1);
	ans.num[ans.size]=1;
	for(i=ans.size-1;i>=0;i--)ans.num[i]=ans.num[i+1]*ans.shape[i];
	ans.data.resize(ans.num[0]);
	std::vector<int> ind(ans.size);
	int w1=0,w2=0;
	for(i=0;i<ans.num[0];i++)
	{
		ans.data[i]=data[w1]-tr.data[w2];
		for(j=0;j<ans.size;j++)
		{
			ind[ans.size-1-j]++;
			if(size>0&&shape[size-1-j]>1)w1+=num[size-j];
			if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2+=tr.num[tr.size-j];
			if(ind[ans.size-1-j]>=ans.num[ans.size-1-j])
			{
				ind[ans.size-1-j]-=ans.num[ans.size-1-j];
				if(size>0&&shape[size-1-j]>1)w1-=ans.num[ans.size-1-j]*num[size-j];
				if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2-=ans.num[ans.size-1-j]*tr.num[tr.size-j];
			}
			else break;
		}
	}
	return ans;
}
Tensor Tensor::operator*(const Tensor& tr){ //假的乘法

        /*if (this->shape == tr.shape) {
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
      }*/
	int i,j,k;
	Tensor ans;
	ans.size=size>tr.size?size:tr.size;
	ans.shape.resize(ans.size);
	for(i=0;i<ans.size;i++)
	{
		if(i>=size)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else if(i>=tr.size)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==shape[size-i-1])ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==1)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(shape[size-i-1]==1)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else{std::cerr<<"Error in *:sizes don't match.\n";return ans;}
	}
	ans.num.resize(ans.size+1);
	ans.num[ans.size]=1;
	for(i=ans.size-1;i>=0;i--)ans.num[i]=ans.num[i+1]*ans.shape[i];
	ans.data.resize(ans.num[0]);
	std::vector<int> ind(ans.size);
	int w1=0,w2=0;
	for(i=0;i<ans.num[0];i++)
	{
		ans.data[i]=data[w1]*tr.data[w2];
		for(j=0;j<ans.size;j++)
		{
			ind[ans.size-1-j]++;
			if(size>0&&shape[size-1-j]>1)w1+=num[size-j];
			if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2+=tr.num[tr.size-j];
			if(ind[ans.size-1-j]>=ans.num[ans.size-1-j])
			{
				ind[ans.size-1-j]-=ans.num[ans.size-1-j];
				if(size>0&&shape[size-1-j]>1)w1-=ans.num[ans.size-1-j]*num[size-j];
				if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2-=ans.num[ans.size-1-j]*tr.num[tr.size-j];
			}
			else break;
		}
	}
	return ans;
}
Tensor Tensor::operator/(const Tensor& tr){ //假的除法
        /*if (this->shape == tr.shape) {
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
      }*/
	int i,j,k;
	Tensor ans;
	ans.size=size>tr.size?size:tr.size;
	ans.shape.resize(ans.size);
	for(i=0;i<ans.size;i++)
	{
		if(i>=size)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else if(i>=tr.size)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==shape[size-i-1])ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(tr.shape[tr.size-i-1]==1)ans.shape[ans.size-i-1]=shape[size-i-1];
		else if(shape[size-i-1]==1)ans.shape[ans.size-i-1]=tr.shape[tr.size-i-1];
		else{std::cerr<<"Error in /:sizes don't match.\n";return ans;}
	}
	ans.num.resize(ans.size+1);
	ans.num[ans.size]=1;
	for(i=ans.size-1;i>=0;i--)ans.num[i]=ans.num[i+1]*ans.shape[i];
	ans.data.resize(ans.num[0]);
	std::vector<int> ind(ans.size);
	int w1=0,w2=0;
	for(i=0;i<ans.num[0];i++)
	{
		ans.data[i]=data[w1]/tr.data[w2];
		for(j=0;j<ans.size;j++)
		{
			ind[ans.size-1-j]++;
			if(size>0&&shape[size-1-j]>1)w1+=num[size-j];
			if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2+=tr.num[tr.size-j];
			if(ind[ans.size-1-j]>=ans.num[ans.size-1-j])
			{
				ind[ans.size-1-j]-=ans.num[ans.size-1-j];
				if(size>0&&shape[size-1-j]>1)w1-=ans.num[ans.size-1-j]*num[size-j];
				if(tr.size>0&&tr.shape[tr.size-1-j]>1)w2-=ans.num[ans.size-1-j]*tr.num[tr.size-j];
			}
			else break;
		}
	}
	return ans;
}

void Node::setvalue(const float& v) {
   /*value.size=0;
   value.data.clear();
   value.shape.clear();
   value.num.clear();

   value.data.push_back(v);
   value.shape.push_back(0);*/
   value=Tensor(v);
}

#endif

void Node::setvalue(const Tensor& v) {
    value = v;
}




const map<Node *,Node *>& Node::grad()
{
	if(grads.empty())
	{
		//static int s=0;
		//s++;
		//std::cerr<<s<<"getgrad "<<"\n";
		getgrad();
	}
	return grads;
}
Node * Node::grad(Node *p)
{
	//static int s=0;
	//s++;
	auto it=grad().find(p);
	//if(s%10000==0)std::cerr<<s<<"grad "<<"\n";
	if(it==grad().end())return Zero;else return it->second;
}
Node::~Node() {std::cerr<<"Node destroyed.\n"; }
