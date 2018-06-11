#include <math.h>
#include "Ops.h"

float Add::calc(set<Node*>& calced) {
    return getleft()->getvalue() + getright()->eval(calced)->getvalue();
}

float Multiply::calc(set<Node*>& calced) {
    return getleft()->getvalue() * getright()->eval(calced)->getvalue();
}

float Minus::calc(set<Node*>& calced) {
    return getleft()->getvalue() - getright()->eval(calced)->getvalue();
}

float Divide::calc(set<Node*>& calced) {
    return getleft()->getvalue() / getright()->eval(calced)->getvalue();
}

float Power::calc(set<Node*>& calced) {
    return pow(getleft()->getvalue(), getright()->eval(calced)->getvalue());
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
        else if (l==0 && r<0) {
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
