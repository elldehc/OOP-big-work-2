#include "stdops.h"

//using namespace std;

int main()
{
    //样例1
    
     /*Node* x = new Placeholder("hhh");
     Node* y = new Placeholder("hahaha");
     Node* z= new Constant(3);
     Node* t = sub(x,y);
     Node* res =less(z,t);
     //map<Node*, float> initmap;
     //initmap[x] = 1;
     //initmap[y] = 2;
     cout << Run({{x,1},{y,2}}, *res) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(x))) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(y))) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(z))) << endl;
     cout << Run({}, *(res->grad(t))) << endl;
     //initmap[x] = 1;
     //cout << Run({{x,1}}, *res) << endl;
     delete x;
     delete y;
     delete z;
     delete t;
     delete res;*/
     
     //Sample 1.5
     
     
     /*Node* x = placeholder("hhh");
     Node* y = placeholder("hahaha");
     Node* z= constant(3);
     Node* t = add(x, mul(y,constant(0.5)));
     Node* res =cond(sin(x),tan(mul(t,z)),cos(mul(t,z)));
     cout << Run({{x,pi/2},{y,pi}}, *res) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x))) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y))) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x)->grad(x))) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x)->grad(y))) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y)->grad(x))) << endl;
     cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y)->grad(y))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *res) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x)->grad(x))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x)->grad(y))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y)->grad(x))) << endl;
     cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y)->grad(y))) << endl;
     //initmap[x] = 1;
     //cout << Run({{x,1}}, *res) << endl;
     delete x;
     delete y;
     delete z;
     delete t;
     delete res;*/
    
    //样例2
    
     /*Node* x = new Placeholder("hhh");
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
     delete res;*/
    
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
    
    //样例6:Assert and Bind
    /*auto x = new Placeholder();
	auto y = new Placeholder();
	auto t = add(x,y);
	auto t1 = new Bind(t, new Assert(new Greater(y,x)));
	auto res = new Bind(t, new Assert(new Less(y,add(x,new Constant(2)))));//这么长！！！需要想办法精简
	cout << Run({{x,1},{y,2}}, *res) << endl;//0
	cout << Run({{x,1},{y,4}}, *res) << endl;//fail
	cout << Run({{x,1},{y,-1}}, *t1) << endl;//fail
	delete x;delete y;delete t;delete t1;delete res;*/
	
	//样例7:Relu
    auto x = new Placeholder();
	auto y=relu(x);
	cout<<Run({{x,2}},*y)<<'\n';
	cout<<Run({{x,-2}},*y)<<'\n';
	cout<<Run({{x,2}},*(y->grad(x)))<<'\n';
	cout<<Run({{x,-2}},*(y->grad(x)))<<'\n';
	
	delete x;delete y;


    return 0;
}
