#include <string>
#include <iostream>
#include <map>
#include <set>
#include <math.h>

#include "Node.h"
#include "nodes.h"
#include "Operator.h"
#include "Ops.h"
#include "func.h"

using namespace std;

int main()
{
    //样例1
    
     Node* x = new Placeholder("hhh");
     Node* y = new Placeholder("hahaha");
     Node* z= new Constant(3);
     Node* t = new Add(x, y);
     Node* res =new Multiply(t,z);
     map<Node*, float> initmap;
     initmap[x] = 1;
     initmap[y] = 2;
     cout << Run(initmap, *res) << endl;
     initmap[x] = 1;
     cout << Run(initmap, *res) << endl;
     delete x;
     delete y;
     delete z;
     delete t;
     delete res;
    
    //样例2
    /*
     Node* x = new Placeholder("hhh");
     Node* y = new Placeholder("hahaha");
     Node* z = new Placeholder("hohoho");
     Node* t = new Print((Node*)(new Add(x, y)));
     Node* res = new Add(t,z);
     map<Node*, float> initmap;
     initmap[x] = 1;
     initmap[y] = 2;
     initmap[z] = 3;
     cout << Run(initmap, *res) << endl;
     delete x;
     delete y;
     delete z;
     delete t;
     delete res;
    */
    //样例3
    /*
     Node* x = new Placeholder("hhh");
     Node* t = new Print(x);
     Node* y = new Constant(1);
     Node* a0 = new Add(t,y);
     Node* a1 = new Add(t,a0);
     Node* a2 = new Add(t,a1);
     map<Node*,float> initmap;
     initmap[x] = 1;
     cout << Run(initmap,*a2) << endl;
     delete x;
     delete y;
     delete a0;
     delete a1;
     delete a2;
    */
    //样例4
    /*
     Node* x = new Placeholder("11");
     Parameter* y = new Parameter(1);
     Node* res = new Add(x, y);
     y->set(2);
     map<Node*, float>initmap;
     initmap[x] = 1;
     cout << Run(initmap, *res) << endl;
     y->add(1);
     initmap[x] = 1;
     cout << Run(initmap, *res) << endl;
     delete x;
     delete y;
     delete res;
    */
    //样例5:Power
    /*
    Parameter* a = new Parameter(3);
    Node* b = new Constant(5);
    Node* c = new Minus(a,b);
    Node* d = new Divide(b,(Node*)(new Minus(b,a)));
    Node* t1 = new Power(a,b);
    cout << Run(*t1) << endl;
    Node* t2 = new Power(c,d);
    cout << Run(*t2) << endl;
    a->set(0);
    Node* t3 = new Power(a,c);
    cout << Run(*t3) << endl;
     delete a;
     delete b;
     delete c;
     delete d;
     delete t1;
     delete t2;
     delete t3;
    */
    return 0;
}
