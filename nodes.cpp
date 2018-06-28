#include "stdops.h"

//Constant
/*Constant::Constant(const std::initializer_list<float>& list, const std::initializer_list<int>& dims) {
    setvalue(Tensor(list,dims));
}

Constant::Constant(const float& value) {
    setvalue(Tensor(value));
}*/

Constant::Constant(const Tensor& value) {
    setvalue(value);
}

Tensor Constant::calc(set<Node*>& calced) {
    return getvalue();
}

Node* Constant::eval(set<Node*>& calced) {
    return this;
}

void Constant::getgrad()
{
	grads[this]=One;
}

Constant* const Zero=new Constant(0);
Constant* const One=new Constant(1);
Constant* const MinusOne=new Constant(-1);

//Placeholder
Placeholder::Placeholder(string myname): name(myname) { }

Tensor Placeholder::calc(set<Node*>& calced) {
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
Print::Print(Node* node,const string &_info): dest(node),info(_info) { }

Tensor Print::calc(set<Node*>& calced) {
    setvalue(dest->eval(calced)->getvalue());
    return dest->getvalue();
}

Node* Print::eval(set<Node*>& calced) {
    if (dest->eval(calced) == nullptr)
        return nullptr;
    else if (calced.insert(this).second) {
        setvalue(dest->eval(calced)->getvalue());
        cout << info << dest->getvalue() << '\n';
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
Tensor Parameter::calc(::set<Node*>& calced) {
    return getvalue();
}
Parameter::Parameter(/*float*/const Tensor& number) {
    setvalue(number);
}
Parameter::Parameter(const float& number) {
    setvalue(Tensor(number));
}

void Parameter::set(/*float*/const Tensor& number) {
    setvalue(number);
}

void Parameter::add(/*float*/const Tensor& number) {
    setvalue(getvalue() + number);
}

void Parameter::multiply(/*float*/const Tensor& number) {
    setvalue(getvalue() * number);
}

void Parameter::minus(/*float*/const Tensor& number) {
    setvalue(getvalue() - number);
}

void Parameter::divide(/*float*/const Tensor& number) {
    setvalue(getvalue() / number);
}


Node* Parameter::eval(::set<Node*>& calced) {
    return this;
}
void Parameter::getgrad()
{
    grads[this]=One;
}

Assign::Assign(Parameter* para,Node* node):src(node),tar(para){}
void Assign::getgrad()
{
	grads=src->grad();
	grads[this]=One;
}
Tensor Assign::calc(set<Node*>& calced) {
    assign_map[tar]=src->getvalue();
    return src->getvalue();
}
	
Node* Assign::eval(set<Node*>& calced) {
    if (src->eval(calced) == nullptr)
        return nullptr;
    else if (calced.insert(this).second) {
        setvalue(calc(calced));
        
        return this;
    }
    else
        return this;
}

map<Parameter*,Tensor> assign_map;
    
Constant* constant(const Tensor &a){auto t=new Constant(a);ptrs.add(t);return t;}
Placeholder* placeholder(string name){auto t=new Placeholder(name);ptrs.add(t);return t;}
Print* print(Node *a,const string &b){auto t=new Print(a,b);ptrs.add(t);return t;}
Parameter* parameter(const Tensor &a){auto t=new Parameter(a);ptrs.add(t);return t;}
Assign* assign(Parameter *para,Node *node){auto t=new Assign(para,node);ptrs.add(t);return t;}

