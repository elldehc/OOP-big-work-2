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

float Bind::calc(set<Node*>& calced) {
    return getleft()->getvalue();
}
void Bind::getgrad()
{
	grads=getleft()->grad();
	grads[this]=One;
}
