#include "stdops.h"

float Add::calc(set<Node*>& calced) {
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
float Multiply::calc(set<Node*>& calced) {
    return getleft()->getvalue() * getright()->eval(calced)->getvalue();
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
float Minus::calc(set<Node*>& calced) {
    return getleft()->getvalue() - getright()->eval(calced)->getvalue();
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
float Divide::calc(set<Node*>& calced) {
    return getleft()->getvalue() / getright()->eval(calced)->getvalue();
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
float Power::calc(set<Node*>& calced) {
	if(getleft()->getvalue()>0)return exp(getright()->eval(calced)->getvalue()*log(getleft()->getvalue()));
	else if(getleft()->getvalue()==0)return 0;
	else{
		int t=getright()->eval(calced)->getvalue()+0.5;
		float ans=exp(getright()->eval(calced)->getvalue()*log(-getleft()->getvalue()));
		if(t&1)return -ans;else return ans;
	}
    //return pow(getleft()->getvalue(), getright()->eval(calced)->getvalue());
}

Node* Power::eval(set<Node*>& calced) {
    if (getleft()->eval(calced) == nullptr || getright()->eval(calced) == nullptr)
        return nullptr;
    else {
        float l=getleft()->getvalue(), r=getright()->getvalue();
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

Add* add(Node *a,Node *b){return new Add(a,b);}
Minus* sub(Node *a,Node *b){return new Minus(a,b);}
Minus* minus(Node *a,Node *b){return new Minus(a,b);}
Multiply* mul(Node *a,Node *b){return new Multiply(a,b);}
Divide* div(Node *a,Node *b){return new Divide(a,b);}
Power* power(Node *a,Node *b){return new Power(a,b);}
