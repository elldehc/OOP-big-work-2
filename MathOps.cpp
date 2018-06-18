#include "stdops.h"
#include "MathOps.h"
Tensor Cos::calc(set<Node*>& calced) {
	return Tensor(cos(getop()->getfloat()));
}
void Cos::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sub(Zero,sin(getop())),it.second);}
	grads[this]=One;
}
Cos* cos(Node *a){return new Cos(a);}

Tensor Sin::calc(set<Node*>& calced) {
	return Tensor(sin(getop()->getfloat()));
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
        float x=getop()->getfloat()/(pi/2);
        
        //possible errors
        if(fabs(floor(x+0.5)-x)<1e-9&&((int)(x+0.5)&1)){
            cout << "Error: cannot calculate tan(" << getop()->getfloat() << "), since it equals to ("<<(int)(x+0.5)<<"+0.5)pi\n";
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
Tensor Tan::calc(set<Node*>& calced) {
	return tan(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate acos(" << getop()->getfloat() << "), since it's not in [-1,1]\n";
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
Tensor Acos::calc(set<Node*>& calced) {
	return acos(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate asin(" << getop()->getfloat() << "), since it's not in [-1,1]\n";
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
Tensor Asin::calc(set<Node*>& calced) {
	return asin(getop()->getfloat());
}
void Asin::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(One,sqr(getop())))),it.second);}
	grads[this]=One;
}
Asin* asin(Node *a){return new Asin(a);}

Tensor Atan::calc(set<Node*>& calced) {
	return atan(getop()->getfloat());
}
void Atan::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,add(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atan* atan(Node *a){return new Atan(a);}

Tensor Cosh::calc(set<Node*>& calced) {
	return cosh(getop()->getfloat());
}
void Cosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sinh(getop()),it.second);}
	grads[this]=One;
}
Cosh* cosh(Node *a){return new Cosh(a);}

Tensor Sinh::calc(set<Node*>& calced) {
	return sinh(getop()->getfloat());
}
void Sinh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(cosh(getop()),it.second);}
	grads[this]=One;
}
Sinh* sinh(Node *a){return new Sinh(a);}

Tensor Tanh::calc(set<Node*>& calced) {
	return tanh(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<1){
            cout << "Error: cannot calculate acosh(" << getop()->getfloat() << "), since it's less than 1\n";
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
Tensor Acosh::calc(set<Node*>& calced) {
	return acosh(getop()->getfloat());
}
void Acosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(sqr(getop()),One))),it.second);}
	grads[this]=One;
}
Acosh* acosh(Node *a){return new Acosh(a);}

Tensor Asinh::calc(set<Node*>& calced) {
	return asinh(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x>=1||x<=-1){
            cout << "Error: cannot calculate atanh(" << getop()->getfloat() << "), since it's not in (-1,1)\n";
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
Tensor Atanh::calc(set<Node*>& calced) {
	return atanh(getop()->getfloat());
}
void Atanh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sub(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atanh* atanh(Node *a){return new Atanh(a);}

Tensor Exp::calc(set<Node*>& calced) {
	return exp(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log(" << getop()->getfloat() << "), since it's not greater than 0.\n";
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
Tensor Log::calc(set<Node*>& calced) {
	return log(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log10(" << getop()->getfloat() << "), since it's not greater than 0.\n";
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
Tensor Log10::calc(set<Node*>& calced) {
	return log10(getop()->getfloat());
}
void Log10::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(getop(),constant(log(10)))),it.second);}
	grads[this]=One;
}
Log10* log10(Node *a){return new Log10(a);}

Tensor Exp2::calc(set<Node*>& calced) {
	return exp2(getop()->getfloat());
}
void Exp2::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,constant(log(2))),it.second);}
	grads[this]=One;
}
Exp2* exp2(Node *a){return new Exp2(a);}

Tensor Expm1::calc(set<Node*>& calced) {
	return expm1(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<=1){
            cout << "Error: cannot calculate log1p(" << getop()->getfloat() << "), since it's not greater than -1.\n";
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
Tensor Log1p::calc(set<Node*>& calced) {
	return log1p(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log2(" << getop()->getfloat() << "), since it's not greater than 0.\n";
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
Tensor Log2::calc(set<Node*>& calced) {
	return log2(getop()->getfloat());
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
        float x=getop()->getfloat();
        
        //possible errors
        if(x<0){
            cout << "Error: cannot calculate sqrt(" << getop()->getfloat() << "), since it's less than 0.\n";
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
Tensor Sqrt::calc(set<Node*>& calced) {
	return sqrt(getop()->getfloat());
}
void Sqrt::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(this,constant(0.5))),it.second);}
	grads[this]=One;
}
Sqrt* sqrt(Node *a){return new Sqrt(a);}

Tensor Sqr::calc(set<Node*>& calced) {
	return getop()->getfloat()*getop()->getfloat();
}
void Sqr::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(getop(),constant(2)),it.second);}
	grads[this]=One;
}
Sqr* sqr(Node *a){return new Sqr(a);}

Tensor Erf::calc(set<Node*>& calced) {
	return erf(getop()->getfloat());
}
void Erf::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi))),it.second);}
	grads[this]=One;
}
Erf* erf(Node *a){return new Erf(a);}

Tensor Erfc::calc(set<Node*>& calced) {
	return erfc(getop()->getfloat());
}
void Erfc::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(minus(Zero,mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi)))),it.second);}
	grads[this]=One;
}
Erfc* erfc(Node *a){return new Erfc(a);}

Tensor Ceil::calc(set<Node*>& calced) {
	return ceil(getop()->getfloat());
}
void Ceil::getgrad()
{
	grads[this]=One;
}
Ceil* ceil(Node *a){return new Ceil(a);}

Tensor Floor::calc(set<Node*>& calced) {
	return floor(getop()->getfloat());
}
void Floor::getgrad()
{
	grads[this]=One;
}
Floor* floor(Node *a){return new Floor(a);}

Tensor Abs::calc(set<Node*>& calced) {
	return abs(getop()->getfloat());
}
void Abs::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sgn(getop()),it.second);}
	grads[this]=One;
}
Abs* abs(Node *a){return new Abs(a);}

Tensor Sgn::calc(set<Node*>& calced) {
	float t=getop()->getfloat();
	if(t>0)return 1;else if(t<0)return -1;else return 0;
}
void Sgn::getgrad()
{
	grads[this]=One;
}
Sgn* sgn(Node *a){return new Sgn(a);}

Tensor Sigmoid::calc(set<Node*>& calced) {
	return 1/(1+exp(-getop()->getfloat()));
}
void Sigmoid::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,minus(One,this)),it.second);}
	grads[this]=One;
}
Sigmoid* sigmoid(Node *a){return new Sigmoid(a);}

Tensor Relu::calc(set<Node*>& calced) {
	float t=getop()->getfloat();
	return t>0?t:0;
}
void Relu::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=cond(greater(getop(),Zero),it.second,Zero);}
	grads[this]=One;
}
Relu* relu(Node *a){return new Relu(a);}

