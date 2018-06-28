#include "stdops.h"
#include "MathOps.h"

Tensor Cos::calc(set<Node*>& calced) {

	Tensor t=getop()->getvalue();
    return cos(t);
}
void Cos::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sub(Zero,sin(getop())),it.second);}
	grads[this]=One;
}
Cos* cos(Node *a){auto t=new Cos(a);ptrs.add(t);return t;}

Tensor Sin::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return sin(t);
}
void Sin::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(cos(getop()),it.second);}
	grads[this]=One;
}
Sin* sin(Node *a){auto t=new Sin(a);ptrs.add(t);return t;}

Node* Tan::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i)/(pi/2);
        
        //possible errors
        if(fabs(floor(x+0.5)-x)<1e-9&&((int)(x+0.5)&1)){
            cout << "Error: cannot calculate tan(" << getop()->getfloat(i) << "), since it equals to ("<<(int)(x+0.5)<<"+0.5)pi\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Tan::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return tan(t);
}
void Tan::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqr(cos(getop()))),it.second);}
	grads[this]=One;
}
Tan* tan(Node *a){auto t=new Tan(a);ptrs.add(t);return t;}

Node* Acos::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate acos(" << getop()->getfloat(i) << "), since it's not in [-1,1]\n";
            return nullptr;
        }
    }
        //no errors
       if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Acos::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return acos(t);
}
void Acos::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sub(Zero,div(One,sqrt(sub(One,sqr(getop()))))),it.second);}
	grads[this]=One;
}
Acos* acos(Node *a){auto t=new Acos(a);ptrs.add(t);return t;}

Node* Asin::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x>1||x<-1){
            cout << "Error: cannot calculate asin(" << getop()->getfloat(i) << "), since it's not in [-1,1]\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Asin::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return asin(t);
}
void Asin::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(One,sqr(getop())))),it.second);}
	grads[this]=One;
}
Asin* asin(Node *a){auto t=new Asin(a);ptrs.add(t);return t;}

Tensor Atan::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return atan(t);
}
void Atan::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,add(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atan* atan(Node *a){auto t=new Atan(a);ptrs.add(t);return t;}

Tensor Cosh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return cosh(t);
}
void Cosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sinh(getop()),it.second);}
	grads[this]=One;
}
Cosh* cosh(Node *a){auto t=new Cosh(a);ptrs.add(t);return t;}

Tensor Sinh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return sinh(t);
}
void Sinh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(cosh(getop()),it.second);}
	grads[this]=One;
}
Sinh* sinh(Node *a){auto t=new Sinh(a);ptrs.add(t);return t;}

Tensor Tanh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return tanh(t);
}
void Tanh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqr(cosh(getop()))),it.second);}
	grads[this]=One;
}
Tanh* tanh(Node *a){auto t=new Tanh(a);ptrs.add(t);return t;}

Node* Acosh::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	 for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<1){
            cout << "Error: cannot calculate acosh(" << getop()->getfloat(i) << "), since it's less than 1\n";
            return nullptr;
        }
    }
        //no errors
       if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Acosh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return acosh(t);
}
void Acosh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(sub(sqr(getop()),One))),it.second);}
	grads[this]=One;
}
Acosh* acosh(Node *a){auto t=new Acosh(a);ptrs.add(t);return t;}

Tensor Asinh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return asinh(t);
}
void Asinh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sqrt(add(sqr(getop()),One))),it.second);}
	grads[this]=One;
}
Asinh* asinh(Node *a){auto t=new Asinh(a);ptrs.add(t);return t;}

Node* Atanh::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x>=1||x<=-1){
            cout << "Error: cannot calculate atanh(" << getop()->getfloat(i) << "), since it's not in (-1,1)\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Atanh::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return atanh(t);
}
void Atanh::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,sub(One,sqr(getop()))),it.second);}
	grads[this]=One;
}
Atanh* atanh(Node *a){auto t=new Atanh(a);ptrs.add(t);return t;}

Tensor Exp::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return exp(t);
}
void Exp::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(this,it.second);}
	grads[this]=One;
}
Exp* exp(Node *a){auto t=new Exp(a);ptrs.add(t);return t;}

Node* Log::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log(" << getop()->getfloat(i) << "), since it's not greater than 0.\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Log::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return log(t);
}
void Log::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,getop()),it.second);}
	grads[this]=One;
}
Log* log(Node *a){auto t=new Log(a);ptrs.add(t);return t;}

Node* Log10::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log10(" << getop()->getfloat(i) << "), since it's not greater than 0.\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Log10::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return log10(t);
}
void Log10::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(getop(),constant(log(10)))),it.second);}
	grads[this]=One;
}
Log10* log10(Node *a){auto t=new Log10(a);ptrs.add(t);return t;}

Tensor Exp2::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return exp2(t);
}
void Exp2::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,constant(log(2))),it.second);}
	grads[this]=One;
}
Exp2* exp2(Node *a){auto t=new Exp2(a);ptrs.add(t);return t;}

Tensor Expm1::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return expm1(t);
}
void Expm1::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(exp(getop()),it.second);}
	grads[this]=One;
}
Expm1* expm1(Node *a){auto t=new Expm1(a);ptrs.add(t);return t;}

Node* Log1p::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<=1){
            cout << "Error: cannot calculate log1p(" << getop()->getfloat(i) << "), since it's not greater than -1.\n";
            return nullptr;
        }
    }
        //no errors
        if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Log1p::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return log1p(t);
}
void Log1p::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,add(One,getop())),it.second);}
	grads[this]=One;
}
Log1p* log1p(Node *a){auto t=new Log1p(a);ptrs.add(t);return t;}

Node* Log2::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<=0){
            cout << "Error: cannot calculate log2(" << getop()->getfloat(i) << "), since it's not greater than 0.\n";
            return nullptr;
        }
    }
        //no errors
         if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Log2::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return log2(t);
}
void Log2::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(getop(),constant(log(2)))),it.second);}
	grads[this]=One;
}
Log2* log2(Node *a){auto t=new Log2(a);ptrs.add(t);return t;}

Node* Sqrt::eval(set<Node*>& calced) {
    if (getop()->eval(calced) == nullptr)
        return nullptr;
    else {
    	    	for (int i=0; i<getop()->get_num(); i++)
    	{
        float x=getop()->getfloat(i);
        
        //possible errors
        if(x<0){
            cout << "Error: cannot calculate sqrt(" << getop()->getfloat(i) << "), since it's less than 0.\n";
            return nullptr;
        }
    }
        //no errors
       if (calced.insert(this).second) {
            setvalue(calc(calced));
            return this;
        }
        else {
            return this;
        }
    }
}
Tensor Sqrt::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return sqrt(t);
}
void Sqrt::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(div(One,mul(this,constant(0.5))),it.second);}
	grads[this]=One;
}
Sqrt* sqrt(Node *a){auto t=new Sqrt(a);ptrs.add(t);return t;}

Tensor Sqr::calc(set<Node*>& calced) {
	return getop()->getvalue()*getop()->getvalue();
}
void Sqr::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(getop(),constant(2)),it.second);}
	grads[this]=One;
}
Sqr* sqr(Node *a){auto t=new Sqr(a);ptrs.add(t);return t;}

Tensor Erf::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return erf(t);
}
void Erf::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi))),it.second);}
	grads[this]=One;
}
Erf* erf(Node *a){auto t=new Erf(a);ptrs.add(t);return t;}

Tensor Erfc::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return erfc(t);
}
void Erfc::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(minus(Zero,mul(exp(minus(Zero,sqr(getop()))),constant(2/sqrt(pi)))),it.second);}
	grads[this]=One;
}
Erfc* erfc(Node *a){auto t=new Erfc(a);ptrs.add(t);return t;}

Tensor Ceil::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return ceil(t);
}
void Ceil::getgrad()
{
	grads[this]=One;
}
Ceil* ceil(Node *a){auto t=new Ceil(a);ptrs.add(t);return t;}

Tensor Floor::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return floor(t);
}
void Floor::getgrad()
{
	grads[this]=One;
}
Floor* floor(Node *a){auto t=new Floor(a);ptrs.add(t);return t;}

Tensor Abs::calc(set<Node*>& calced) {
	Tensor t=getop()->getvalue();
    return abs(t);
}
void Abs::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(sgn(getop()),it.second);}
	grads[this]=One;
}
Abs* abs(Node *a){auto t=new Abs(a);ptrs.add(t);return t;}

Tensor Sgn::calc(set<Node*>& calced) {
	//float t=getop()->getfloat();
	//if(t>0)return 1;else if(t<0)return -1;else return 0;
	Tensor t=getop()->getvalue();
	for(int i=0;i<t.num[0];i++)if(t.data[i]>0)t.data[i]=1;else if(t.data[i]<0)t.data[i]=-1;else t.data[i]=0;
	return t;
}
void Sgn::getgrad()
{
	grads[this]=One;
}
Sgn* sgn(Node *a){auto t=new Sgn(a);ptrs.add(t);return t;}

Tensor Sigmoid::calc(set<Node*>& calced) {
	return Tensor(1)/(Tensor(1)+exp(Tensor(0)-getop()->getvalue()));
}
void Sigmoid::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=mul(mul(this,minus(One,this)),it.second);}
	grads[this]=One;
}
Sigmoid* sigmoid(Node *a){auto t=new Sigmoid(a);ptrs.add(t);return t;}

Tensor Relu::calc(set<Node*>& calced) {
	/*float t=getop()->getfloat();
	return t>0?t:0;*/
	Tensor t=getop()->getvalue();
	for(int i=0;i<t.num[0];i++)if(t.data[i]<0)t.data[i]=0;
	return t;
}
void Relu::getgrad()
{
	for(auto it:getop()->grad()){grads[it.first]=cond(greater(getop(),Zero),it.second,Zero);}
	grads[this]=One;
}
Relu* relu(Node *a){auto t=new Relu(a);ptrs.add(t);return t;}

Tensor Softmax::calc(set<Node*>& calced) {
	Tensor one({},getop()->getvalue().getshape()),ex=exp(getop()->getvalue());
	one.fill(1);
	one._transpose();
	return ex/one._matmul(ex);
}
void Softmax::getgrad()
{
	//No! There is no gradient method for a Tensor.
	//for(auto it:getop()->grad()){grads[it.first]=cond(greater(getop(),Zero),it.second,Zero);}
	grads[this]=One;
}
Softmax* softmax(Node *a){auto t=new Softmax(a);ptrs.add(t);return t;}

