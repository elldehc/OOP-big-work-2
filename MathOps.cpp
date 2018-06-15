#include "stdops.h"
#include "MathOps.h"
float Cos::calc(set<Node*>& calced) {
	return cos(getop()->getvalue());
}
void Cos::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sub(Zero,sin(getop())),it.second);}
	grads[this]=One;
}
Cos* cos(Node *a){return new Cos(a);}

float Sin::calc(set<Node*>& calced) {
	return sin(getop()->getvalue());
}
void Sin::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(cos(getop()),it.second);}
	grads[this]=One;
}
Sin* sin(Node *a){return new Sin(a);}

Node* Tan::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue()/(pi/2);
        
        //possible errors
        if(fabs(floor(x+0.5)-x)<1e-9&&((int)(x+0.5)&1)){
            cout << "Error: cannot calculate tan(" << getop()->getvalue() << "), since it equals to ("<<(int)(x+0.5)<<"+0.5)pi\n";
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
float Tan::calc(set<Node*>& calced) {
	return tan(getop()->getvalue());
}
void Tan::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqr(cos(getop()))),it.second);}
	grads[this]=One;
}
Tan* tan(Node *a){return new Tan(a);}

Node* Acos::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate acos(" << getop()->getvalue() << "), since it's not in [-1,1]\n";
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
float Acos::calc(set<Node*>& calced) {
	return acos(getop()->getvalue());
}
void Acos::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sub(Zero,div(One,sqrt(sub(One,sqr(getop()))))),it.second);}
	grads[this]=One;
}
Acos* acos(Node *a){return new Acos(a);}

Node* Asin::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate asin(" << getop()->getvalue() << "), since it's not in [-1,1]\n";
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
float Asin::calc(set<Node*>& calced) {
	return asin(getop()->getvalue());
}
void Asin::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(One,sqr(getop())))),it.second);}
	grads[this]=One;
}
Asin* asin(Node *a){return new Asin(a);}

float Atan::calc(set<Node*>& calced) {
	return atan(getop()->getvalue());
}
void Atan::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,add(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atan* atan(Node *a){return new Atan(a);}

float Cosh::calc(set<Node*>& calced) {
	return cosh(getop()->getvalue());
}
void Cosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sinh(getop()),it.second);}
	grads[this]=One;
}
Cosh* cosh(Node *a){return new Cosh(a);}

float Sinh::calc(set<Node*>& calced) {
	return sinh(getop()->getvalue());
}
void Sinh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(cosh(getop()),it.second);}
	grads[this]=One;
}
Sinh* sinh(Node *a){return new Sinh(a);}

float Tanh::calc(set<Node*>& calced) {
	return tanh(getop()->getvalue());
}
void Tanh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqr(cosh(getop()))),it.second);}
	grads[this]=One;
}
Tanh* tanh(Node *a){return new Tanh(a);}

Node* Acosh::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<1){
            cout << "Error: cannot calculate acosh(" << getop()->getvalue() << "), since it's less than 1\n";
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
float Acosh::calc(set<Node*>& calced) {
	return acosh(getop()->getvalue());
}
void Acosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(sqr(getop()),One))),it.second);}
	grads[this]=One;
}
Acosh* acosh(Node *a){return new Acosh(a);}

float Asinh::calc(set<Node*>& calced) {
	return asinh(getop()->getvalue());
}
void Asinh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(add(sqr(getop()),One))),it.second);}
	grads[this]=One;
}
Asinh* asinh(Node *a){return new Asinh(a);}

Node* Atanh::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x>=1||x<=-1){
            cout << "Error: cannot calculate atanh(" << getop()->getvalue() << "), since it's not in (-1,1)\n";
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
float Atanh::calc(set<Node*>& calced) {
	return atanh(getop()->getvalue());
}
void Atanh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sub(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atanh* atanh(Node *a){return new Atanh(a);}

float Exp::calc(set<Node*>& calced) {
	return exp(getop()->getvalue());
}
void Exp::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(this,it.second);}
	grads[this]=One;
}
Exp* exp(Node *a){return new Exp(a);}

Node* Log::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log(" << getop()->getvalue() << "), since it's not greater than 0.\n";
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
float Log::calc(set<Node*>& calced) {
	return log(getop()->getvalue());
}
void Log::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,getop()),it.second);}
	grads[this]=One;
}
Log* log(Node *a){return new Log(a);}

Node* Log10::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log10(" << getop()->getvalue() << "), since it's not greater than 0.\n";
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
float Log10::calc(set<Node*>& calced) {
	return log10(getop()->getvalue());
}
void Log10::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(getop(),constant(log(10)))),it.second);}
	grads[this]=One;
}
Log10* log10(Node *a){return new Log10(a);}

float Exp2::calc(set<Node*>& calced) {
	return exp2(getop()->getvalue());
}
void Exp2::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,constant(log(2))),it.second);}
	grads[this]=One;
}
Exp2* exp2(Node *a){return new Exp2(a);}

float Expm1::calc(set<Node*>& calced) {
	return expm1(getop()->getvalue());
}
void Expm1::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(exp(getop()),it.second);}
	grads[this]=One;
}
Expm1* expm1(Node *a){return new Expm1(a);}

Node* Log1p::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<=1){
            cout << "Error: cannot calculate log1p(" << getop()->getvalue() << "), since it's not greater than -1.\n";
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
float Log1p::calc(set<Node*>& calced) {
	return log1p(getop()->getvalue());
}
void Log1p::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,add(One,getop())),it.second);}
	grads[this]=One;
}
Log1p* log1p(Node *a){return new Log1p(a);}

Node* Log2::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log2(" << getop()->getvalue() << "), since it's not greater than 0.\n";
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
float Log2::calc(set<Node*>& calced) {
	return log2(getop()->getvalue());
}
void Log2::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(getop(),constant(log(2)))),it.second);}
	grads[this]=One;
}
Log2* log2(Node *a){return new Log2(a);}

Node* Sqrt::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
        float x=getop()->getvalue();
        
        //possible errors
        if(x<0){
            cout << "Error: cannot calculate sqrt(" << getop()->getvalue() << "), since it's less than 0.\n";
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
float Sqrt::calc(set<Node*>& calced) {
	return sqrt(getop()->getvalue());
}
void Sqrt::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(this,constant(0.5))),it.second);}
	grads[this]=One;
}
Sqrt* sqrt(Node *a){return new Sqrt(a);}

float Sqr::calc(set<Node*>& calced) {
	return getop()->getvalue()*getop()->getvalue();
}
void Sqr::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(getop(),constant(2)),it.second);}
	grads[this]=One;
}
Sqr* sqr(Node *a){return new Sqr(a);}

float Erf::calc(set<Node*>& calced) {
	return erf(getop()->getvalue());
}
void Erf::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi))),it.second);}
	grads[this]=One;
}
Erf* erf(Node *a){return new Erf(a);}

float Erfc::calc(set<Node*>& calced) {
	return erfc(getop()->getvalue());
}
void Erfc::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(minus(Zero,mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi)))),it.second);}
	grads[this]=One;
}
Erfc* erfc(Node *a){return new Erfc(a);}

float Ceil::calc(set<Node*>& calced) {
	return ceil(getop()->getvalue());
}
void Ceil::getgrad()
{
	grads[this]=One;
}
Ceil* ceil(Node *a){return new Ceil(a);}

float Floor::calc(set<Node*>& calced) {
	return floor(getop()->getvalue());
}
void Floor::getgrad()
{
	grads[this]=One;
}
Floor* floor(Node *a){return new Floor(a);}

float Abs::calc(set<Node*>& calced) {
	return abs(getop()->getvalue());
}
void Abs::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sgn(getop()),it.second);}
	grads[this]=One;
}
Abs* abs(Node *a){return new Abs(a);}

float Sgn::calc(set<Node*>& calced) {
	float t=getop()->getvalue();
	if(t>0)return 1;else if(t<0)return -1;else return 0;
}
void Sgn::getgrad()
{
	grads[this]=One;
}
Sgn* sgn(Node *a){return new Sgn(a);}

float Sigmoid::calc(set<Node*>& calced) {
	return 1/(1+exp(-getop()->getvalue()));
}
void Sigmoid::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,minus(One,this)),it.second);}
	grads[this]=One;
}
Sigmoid* sigmoid(Node *a){return new Sigmoid(a);}

float Relu::calc(set<Node*>& calced) {
	float t=getop()->getvalue();
	return t>0?t:0;
}
void Relu::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=cond(greater(getop(),Zero),it.second,Zero);}
	grads[this]=One;
}
Relu* relu(Node *a){return new Relu(a);}

