#include "stdops.h"
float Less::calc(set<Node*>& calced) {
    return getleft()->getvalue() < getright()->getvalue();
}
void Less::getgrad()
{
	grads[this]=One;
}

float Greater::calc(set<Node*>& calced) {
    return getleft()->getvalue() > getright()->getvalue();
}
void Greater::getgrad()
{
	grads[this]=One;
}

float Leq::calc(set<Node*>& calced) {
    return getleft()->getvalue() <= getright()->getvalue();
}
void Leq::getgrad()
{
	grads[this]=One;
}

float Geq::calc(set<Node*>& calced) {
    return getleft()->getvalue() >= getright()->getvalue();
}
void Geq::getgrad()
{
	grads[this]=One;
}

float Equal::calc(set<Node*>& calced) {
    return getleft()->getvalue() == getright()->getvalue();
}
void Equal::getgrad()
{
	grads[this]=One;
}

float Ineq::calc(set<Node*>& calced) {
    return getleft()->getvalue() < getright()->getvalue();
}
void Ineq::getgrad()
{
	grads[this]=One;
}

float Assert::calc(set<Node*>& calced) {
    return 0;
}

Node* Assert::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        //possible errors
        if (x<=0) {
            cout << "Assertion failed:"<<x<<"<=0";
            return nullptr;
        }
        else if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
void Assert::getgrad()
{
	grads[this]=One;
}

Node* Bind::eval(set<Node*>& calced) {
	getright()->eval(calced);
    if (getleft()->eval(calced) == nullptr)
        return nullptr;
    else if (calced.insert(this).second) {
        setvalue(calc(calced));
        return this;
    } 
    else {
        return this;
    }
}
float Bind::calc(set<Node*>& calced) {
    return getleft()->getvalue();
}
void Bind::getgrad()
{
	grads=getleft()->grad();
	grads[this]=One;
}

Cond::Cond(Node* node1, Node* node2,Node* node3):co(node1),ans1(node2),ans2(node3){}
Node* Cond::eval(set<Node*>& calced) {
	
    if (co->eval(calced) == nullptr||co->getvalue()<=0)
    {
    	if(ans2->eval(calced)==nullptr)return nullptr;
    	else if (calced.insert(this).second) {
		    setvalue(calc(calced));
		    return this;
		} 
		else {
		    return this;
		}
	}
	else
	{
		if(ans1->eval(calced)==nullptr)return nullptr;
    	else if (calced.insert(this).second) {
		    setvalue(calc(calced));
		    return this;
		} 
		else {
		    return this;
		}
	}
}
float Cond::calc(set<Node*>& calced)
{
	if (co->eval(calced) == nullptr||co->getvalue()<=0)return ans2->getvalue();else return ans1->getvalue();
}
void Cond::getgrad()
{
	for(auto it:ans1->grad())grads[it.first]=nullptr;
	for(auto it:ans2->grad())grads[it.first]=nullptr;
	for(auto &it:grads)it.second=cond(co,ans1->grad(it.first),ans2->grad(it.first));
	grads[this]=One;
}
Less* less(Node *a,Node *b){return new Less(a,b);}
Greater* greater(Node *a,Node *b){return new Greater(a,b);}
Leq* leq(Node *a,Node *b){return new Leq(a,b);}
Geq* geq(Node *a,Node *b){return new Geq(a,b);}
Equal* equal(Node *a,Node *b){return new Equal(a,b);}
Ineq* ineq(Node *a,Node *b){return new Ineq(a,b);}
Assert* assert(Node *a){return new Assert(a);}
Bind* bind(Node *a,Node *b){return new Bind(a,b);}
Cond* cond(Node *a,Node *b,Node *c){return new Cond(a,b,c);}