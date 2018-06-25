#include "stdops.h"

Tensor Add::calc(set<Node*>& calced) {
    return getleft()->getvalue() + getright()/*->eval(calced)*/->getvalue();
}
void Add::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Add(left->grad(it.first),right->grad(it.first));
	}
	grads[this]=One;
}
Tensor Multiply::calc(set<Node*>& calced) {
    return getleft()->getvalue() * getright()/*->eval(calced)*/->getvalue();
}
void Multiply::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Add(new Multiply(left->grad(it.first),right),new Multiply(left,right->grad(it.first)));
	}
	grads[this]=One;
}
Tensor Minus::calc(set<Node*>& calced) {
    return getleft()->getvalue() - getright()/*->eval(calced)*/->getvalue();
}
void Minus::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Minus(left->grad(it.first),right->grad(it.first));
	}
	grads[this]=One;
}
Tensor Divide::calc(set<Node*>& calced) {
    return getleft()->getvalue() / getright()/*->eval(calced)*/->getvalue();
}
void Divide::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Minus(new Multiply(left->grad(it.first),right),new Multiply(left,right->grad(it.first)));
		it.second=new Divide(it.second,new Multiply(right,right));
	}
	grads[this]=One;
}
Tensor Power::calc(set<Node*>& calced) {
	if(getleft()->getfloat()>0)return exp(getright()->eval(calced)->getfloat()*log(getleft()->getfloat()));
	else if(getleft()->getfloat()==0)return 0;
	else{
		int t=getright()->eval(calced)->getfloat()+0.5;
		float ans=exp(getright()->eval(calced)->getfloat()*log(-getleft()->getfloat()));
		if(t&1)return Tensor(-ans);else return Tensor(ans);
	}
    //return pow(getleft()->getvalue(), getright()->eval(calced)->getvalue());
}

Node* Power::eval(set<Node*>& calced) {
    if (getleft()->eval(calced) == nullptr || getright()->eval(calced) == nullptr)
        return nullptr;
    else {
        float l=getleft()->getfloat(), r=getright()->getfloat();
        //possible errors
        if (l<0 && (int)r!=r) {
            cout << "Error: cannot calculate " << l << "^" << r << ", since base is negative and exp is non-interger\n";
            return nullptr;
        }
        else if (l==0 && r<=0) {
            cout << "Error: cannot calculate " << l << "^" << r << ", since base is zero and exp is negative\n";
            return nullptr;
        }
        //no errors
        else if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
void Power::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=mul(this,add(mul(right->grad(it.first),log(left)),div(mul(left->grad(it.first),right),left)));
	}
	grads[this]=One;
}

#ifndef notensor
Tensor Transpose::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    t._transpose();
	return t;

}
void Transpose::getgrad()
{
	for(auto it:op->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Transpose(op->grad(it.first));
	}
	grads[this]=One;
}

Tensor Concat::calc(set<Node*>& calced) {
    return getleft()->getvalue()._concat(getright()->getvalue(),dim);
}
void Concat::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Concat(left->grad(it.first),right->grad(it.first),dim);
	}
	grads[this]=One;
}

Tensor Reshape::calc(set<Node*>& calced) {
    Tensor t=getop()->getvalue();
    t._reshape(list);
    return t;
}

void Reshape::getgrad()
{
	for(auto it:op->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Reshape(op->grad(it.first),list);
	}
	grads[this]=One;
}

Tensor Reshape2::calc(set<Node*>& calced) {
	Tensor t=getleft()->getvalue();
	t._reshape(getright()->getvalue().getshape());
    return t;//
}
void Reshape2::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Reshape2(left->grad(it.first),right);
	}
	grads[this]=One;
}

Tensor Matmul::calc(set<Node*>& calced) {
    return getleft()->getvalue()._matmul(getright()->eval(calced)->getvalue());//
}
void Matmul::getgrad()
{
	for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Add(new Matmul(left->grad(it.first),right),new Matmul(left,right->grad(it.first)));
	}
	grads[this]=One;
}
#endif

Tensor Addn::calc(set<Node*>& calced) {
	Tensor s=0;
	for(auto it:getop())s=s+it->getvalue();
    return s;
}
void Addn::getgrad()
{
	for(auto it:getop())
	for(auto jt:it->grad())grads[jt.first]=nullptr;
	for(auto &it:grads)
	{
		std::vector<Node*> v;
		for(auto jt:getop())v.push_back(jt->grad(it.first));
		it.second=addn(v);
	}
	
	/*for(auto it:left->grad())grads[it.first]=nullptr;
	for(auto it:right->grad())grads[it.first]=nullptr;
	for(auto &it:grads)
	{
		it.second=new Add(left->grad(it.first),right->grad(it.first));
	}*/
	grads[this]=One;
}

Add* add(Node *a,Node *b){return new Add(a,b);}
Minus* sub(Node *a,Node *b){return new Minus(a,b);}
Minus* minus(Node *a,Node *b){return new Minus(a,b);}
Multiply* mul(Node *a,Node *b){return new Multiply(a,b);}
Divide* div(Node *a,Node *b){return new Divide(a,b);}
Power* power(Node *a,Node *b){return new Power(a,b);}
#ifndef notensor
Transpose* transpose(Node *a){return new Transpose(a);}
Concat* concat(Node *a,Node *b,int c){return new Concat(a,b,c);}
Reshape* reshape(Node *a,const std::vector<int>& b){return new Reshape(a,b);}
Reshape2* reshape2(Node *a,Node *b){return new Reshape2(a,b);}
Matmul* matmul(Node *a,Node *b){return new Matmul(a,b);}
#endif
Addn* addn(const std::vector<Node*> &a){return new Addn(a);}
