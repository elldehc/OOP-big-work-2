#include "stdops.h"

//using namespace std;

int main()
{
    //样例1

   /*  Node* x = new Placeholder("hhh");
     Node* y = new Placeholder("hahaha");
     Node* z= new Constant(3);
     Node* t = sub(x,y);
     Node* res =less(z,t);
     //map<No[x] = 1;
     //initmap[y] = 2;
     cout << Run({{x,1},{y,2}}, *res) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(x))) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(y))) << endl;
     cout << Run({{x,1},{y,3}}, *(res->grad(z))) << endl;
     cout << Run( *(res->grad(t))) << endl;
     //initmap[x] = 1;
     //cout << Run({{x,1}}, *res) << endl;
     delete x;
     delete y;
     delete z;
     delete t;
     delete res;*/

	//sample for matrix    -dy
/*	Node* x=new Placeholder("hhh");
	Node* y =new Placeholder("hahaha");
	Node* t=add(x,y);
    cout << Run({{x,{{1,1,1,1},{2,2}}},{y,{{2,2,2,2},{2,2}}}}, *t) << endl; //每次输入张量就在大括号里改就行
    delete x;
    delete y;
    delete t;*/

	//sample for matrix for reshape&concat  -dy
/* Node* x=new Constant({{1,1,1,1,1,1,1,1},{2,2,2}});
	cout<<x<<endl;
	x->reshape({2,4});
	cout<<x<<endl;
	x->concat();
	cout<<x<<endl;
	delete x;*/


     
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
    
  /*  Parameter* a = new Parameter(3);
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
    
    //样例6:assert and bind
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
    /*auto x = new Placeholder();
	auto y=relu(x);
	cout<<Run({{x,2}},*y)<<'\n';
	cout<<Run({{x,-2}},*y)<<'\n';
	cout<<Run({{x,2}},*(y->grad(x)))<<'\n';
	cout<<Run({{x,-2}},*(y->grad(x)))<<'\n';
	
	delete x;delete y;*/
	
	//样例8:Newton solve
	/*int n;
	int a[101];
	int i,j,k;
	std::cin>>n;
	auto x = placeholder();
	Node *y=Zero;
	for(i=0;i<=n;i++)std::cin>>a[i];
	for(i=n;i>=0;i--)y=add(mul(y,x),constant(a[i]));
	float ans=solve(y,x,-1);
	cout<<ans<<'\n';
    
	delete x;delete y;*/
	
	//样例9:Assign
	/*auto x = parameter(1);
	auto y = parameter(2);
	auto t1 = assign(x, y);
	auto t2 = assign(y, mul(t1,y));
	auto res = mul(mul(t2,x),y);
	cout<<Run(*res)<<'\n';
	//<< 8
	cout<<Run(*x)<<'\n';
	//<< 2
	cout<<Run(*y)<<'\n';
	//<< 4*/

	//sample 10:Transpose
	/*Node* x=new Constant({{1,1,1,1,1,1,1,2},{2,4}});
	Node* y=new Transpose(x);	
	cout<<Run(*y)<<endl;*/

	//sample 11:Concat
	/*Node* x=new Constant({{1,1,1,1,1,1,1,1},{2,4}});
	Node* y=new Constant({{2,2,2,2,2,2,2,2},{2,4}});
	Node* z=new Concat(x,y,2);
	cout<<Run(*z)<<endl;*/
	//sample 11.5:Concat
	/*Node* x=new Constant(1);
	Node* y=new Constant(2);
	Node* z=new Concat(x,y,0);
	cout<<Run(*z)<<endl;*/
	
	//sample 12:Class Reshape
	/*Node* x=new Constant({{1,1,1,1,1,1,1,1},{2,4}});
	Node* y=new Reshape(x, {1,2,1,1,2,1,1,2});
	cout<<Run(*y)<<endl;*/
    //sample 13:Class Matmul
	/*Node* x=new Constant({{1,1,1,1,1,1,1,1},{2,4}});
	Node* y=new Constant({{1,1,1,1,1,1,1,1},{4,2}});
	Node* z=new Matmul(x,y);
	cout<<Run(*z)<<endl;*/
	//sample 14:modifying Tensor
	/*Tensor a({},{3,3,3});
	int i,j,k,l=0;
	for(i=0;i<3;i++)
	for(j=0;j<3;j++)
	for(k=0;k<3;k++)
	{
	   a.at({i,j,k})=++l;
	   cout<<a<<'\n';
	}
	a._reshape({2,4,4});
	cout<<a<<'\n';*/
	//sample 15:gradients on Tensor
	auto x=placeholder();
	Node *a11=sin(x),*a12=cos(x),*a21=exp(x),*a22=log(x);
	auto a=concat(concat(a11,a21,0),concat(a12,a22,0),1);
	auto b=constant({{1,1,-1,1},{2,2}});
	auto ans=matmul(a,b);
	cout<<Run({{x,1}},*ans)<<'\n';
	cout<<Run({{x,1}},*ans->grad(x))<<'\n';
	auto y=placeholder();
	auto ly=matmul(y,transpose(y));
	cout<<Run({{y,{{1,1,1,1},{1,4}}}},*ly->grad(y))<<'\n';
	//sample 16:broadcast of +-*/
	/*Tensor a({1,1,1,1},{2,1,2,1}),b({3,3,3,3,3,3},{3,1,2});
	//Tensor c=a+b;
	auto t=sigmoid(constant(a));
	cout<<Run(*t)<<'\n';
	cout<<a+b<<'\n';
	cout<<a-b<<'\n';
	cout<<a*b<<'\n';
	cout<<a/b<<'\n';*/
	
	//system("pause");
    return 0;
}
