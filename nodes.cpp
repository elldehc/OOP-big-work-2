#include "stdops.h"

//Constant
Constant::Constant(float number) {
    setvalue(number);
}

float Constant::calc(set<Node*>& calced) {
    return getvalue();
}

Node* Constant::eval(set<Node*>& calced) {
    return this;
}

void Constant::getgrad()
{
	grads[this]=One;
}

extern Constant* const Zero=new Constant(0);
extern Constant* const One=new Constant(1);
extern Constant* const MinusOne=new Constant(-1);

//Placeholder
Placeholder::Placeholder(string myname): name(myname) { }

float Placeholder::calc(set<Node*>& calced) {
    return getvalue();
}

Node* Placeholder::eval(set<Node*>& calced) {
    if (calced.find(this) != calced.end()) //if found；如果没有找到目标元素则结束时find(this)结果为end()
        return this;
    else {
        cout << "Error: Placeholder " << name << " not found\n";
        return nullptr;
    }
}

void Placeholder::getgrad()
{
	grads[this]=One;
}


//Print
Print::Print(Node* node): dest(node) { }

float Print::calc(set<Node*>& calced) {
    setvalue(dest->eval(calced)->getvalue());
    return dest->getvalue();
}

Node* Print::eval(set<Node*>& calced) {
    if (dest->eval(calced) == nullptr)
        return nullptr;
    else if (calced.insert(this).second) {
        setvalue(dest->eval(calced)->getvalue());
        cout << "Print Operator: " << dest->getvalue() << endl;
        return this;
    }
    else
        return this;
}

void Print::getgrad()
{
	grads=dest->grad();
	grads[this]=One;
}

//Parameter
float Parameter::calc(::set<Node*>& calced) {
    return getvalue();
}
Parameter::Parameter(float number) {
    setvalue(number);
}

void Parameter::set(float number) {
    setvalue(number);
}

void Parameter::add(float number) {
    setvalue(getvalue() + number);
}

void Parameter::multiply(float number) {
    setvalue(getvalue() * number);
}

void Parameter::minus(float number) {
    setvalue(getvalue() - number);
}

void Parameter::divide(float number) {
    setvalue(getvalue() / number);
}

Node* Parameter::eval(::set<Node*>& calced) {
    return this;
}
void Parameter::getgrad()
{
	grads[this]=One;
}

