#include "stdops.h"

//using namespace std;

int main()
{
	//sample 1:assert and bind
    /*auto x = placeholder();
	auto y = placeholder();
	auto t = add(x,y);
	auto t1 = bind(t, assert(greater(y,x)));
	auto res = bind(t, assert(less(y,add(x,constant(2)))));
	cout << Run({{x,1},{y,2}}, *res) << endl;//3
	cout << Run({{x,1},{y,4}}, *res) << endl;//fail
	cout << Run({{x,1},{y,-1}}, *t1) << endl;//fail*/
	
	//sample 2.1:gradients (for scalar only)
	/*auto x = placeholder();
	auto y = mul(x,constant(3));
	auto z = mul(x,constant(2));
	auto L = add(y,z);
	std::cout<<Run({{x,3}},*L->grad(y))<<'\n';//1
	std::cout<<Run({{x,3}},*L->grad(x))<<'\n';//5
	auto t = add(L->grad(x),L->grad(y));
	std::cout<<Run({{x,3}},*t)<<'\n';//6*/
	
	//sample 2.2:gradients (for scalar only)
	/*auto x = placeholder();
	auto y = placeholder();
	auto t=mul(x,x);
	auto L=mul(t,y);
	std::cout<<Run({{x,3},{y,2}},*L->grad(y))<<'\n';//9
	std::cout<<Run({{x,3},{y,2}},*L->grad(t))<<'\n';//2
	std::cout<<Run({{x,3},{y,2}},*L->grad(x))<<'\n';//12*/

	//sample 2.3:gradients (for scalar only)
	/*auto x = placeholder();
	auto y = placeholder();
	auto t1=mul(x,y);
	auto t2=add(mul(x,t1),y);
	auto t3=add(mul(y,t2),x);
	auto L=add(mul(t1,t2),t3);
	auto res=add(L->grad(x),L->grad(y));
	std::cout<<Run({{x,2},{y,3}},*res)<<'\n';//244*/

	//sample 3:Newton solve
	/*int n;
	int a[101];
	int i,j,k;
	std::cin>>n;//5
	auto x = placeholder();
	Node *y=Zero;
	for(i=0;i<=n;i++)std::cin>>a[i];//1 1 2 3 0 1
	for(i=n;i>=0;i--)y=add(mul(y,x),constant(a[i]));
	float ans=solve(y,x,-1);
	cout<<ans<<'\n';//-0.720862*/

	//sample 4:sin exp log
	/*auto x = placeholder();
	auto y = placeholder();
	auto z = constant(3);
	auto t = add(sin(z),log(y));
	auto res = mul(t,exp(x));
	std::cout<<Run({{x,1},{y,2}},*res)<<'\n';//2.267773339
	std::cout<<Run({{x,1},{y,-1}},*res)<<'\n';//error
	std::cout<<Run({{y,1}},*t)<<'\n';//0.1411200081*/
	
	//sample 5:Assign
	/*auto x = parameter(1);
	auto y = parameter(2);
	auto t1 = assign(x, y);
	auto t2 = assign(y, mul(t1,y));
	auto res = mul(mul(t2,x),y);
	cout<<Run(*res)<<'\n';//8
	cout<<Run(*x)<<'\n';//2
	cout<<Run(*y)<<'\n';//4*/

	//sample 6:gradients (for scalar only)
	/*auto x=placeholder();
	auto y=placeholder();
	auto t=print(exp(div(sub(log(x),y),add(sin(x),cos(y)))),"t=");
	std::cout<<Run({{x,pi/2},{y,-pi/2}},*t->grad(x))<<'\n';//4.810477381
	std::cout<<Run({{x,pi/2},{y,-pi/2}},*t->grad(y))<<'\n';//-22.83794284
	std::cout<<Run({{x,pi/2},{y,-pi/2}},*assert(t)->grad(x))<<'\n';//0
	std::cout<<Run({{x,pi/2},{y,-pi/2}},*bind(t,assert(t))->grad(x))<<'\n';//4.810477381
	return 0;*/
	
	//sample 6.5:double gradients and condition operator
    /*Node* x = placeholder();
	Node* y = placeholder();
	Node* z= constant(3);
	Node* t = add(x, mul(y,constant(0.5)));
	Node* res =cond(sin(x),tan(mul(t,z)),cos(mul(t,z)));//cond(a,b,c):return a>0?b:c
	cout << Run({{x,pi/2},{y,pi}}, *res) << endl;//0
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x))) << endl;//3
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y))) << endl;//1.5
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x)->grad(x))) << endl;//0
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(x)->grad(y))) << endl;//0
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y)->grad(x))) << endl;//0
	cout << Run({{x,pi/2},{y,pi}}, *(res->grad(y)->grad(y))) << endl;//0
	cout << Run({{x,-pi/2},{y,pi}}, *res) << endl;//1
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x))) << endl;//0
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y))) << endl;//0
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x)->grad(x))) << endl;//-9
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(x)->grad(y))) << endl;//-4.5
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y)->grad(x))) << endl;//-4.5
	cout << Run({{x,-pi/2},{y,pi}}, *(res->grad(y)->grad(y))) << endl;//-2.25
	delete x;
	delete y;
	delete z;
	delete t;
	delete res;*/
	
	//sample 7:Relu and sigmoid
    /*auto x = placeholder();
	auto y=relu(x);
	cout<<Run({{x,2}},*y)<<'\n';//2
	cout<<Run({{x,-2}},*y)<<'\n';//0
	cout<<Run({{x,2}},*(y->grad(x)))<<'\n';//1
	cout<<Run({{x,-2}},*(y->grad(x)))<<'\n';//0
	auto z=sigmoid(x);
	cout<<Run({{x,2}},*z)<<'\n';//0.880797078
	cout<<Run({{x,-2}},*z)<<'\n';//0.119202922
	cout<<Run({{x,2}},*(z->grad(x)))<<'\n';//0.1049935854
	cout<<Run({{x,-2}},*(z->grad(x)))<<'\n';//0.1049935854*/
	
	//sample 8:Tensor operators
	/*Node* x=constant({{1,1,1,1,1,1,1,2},{2,4}});
	Node* y=constant({{2,2,2,2,2,2,2,2},{2,4}});
	cout<<Run(*transpose(x))<<endl;//{{1,1}{1,1}{1,1}{1,2}}
	cout<<Run(*concat(x,y,0))<<endl;//{{1,1,1,1}{1,1,1,2}{2,2,2,2}{2,2,2,2}}
	cout<<Run(*concat(x,y,1))<<endl;//{{1,1,1,1,2,2,2,2}{1,1,1,2,2,2,2,2}}
	cout<<Run(*concat(x,y,2))<<endl;//{{{1,2}{1,2}{1,2}{1,2}}{{1,2}{1,2}{1,2}{2,2}}}
	cout<<Run(*reshape(x, {1,2,1,2,1,1,2}))<<endl;//{{{{{{{1,1}}}{{{1,1}}}}}{{{{{1,1}}}{{{1,2}}}}}}}
	cout<<Run(*sigmoid(x))<<'\n';//{{0.731059,0.731059,0.731059,0.731059}{0.731059,0.731059,0.731059,0.880797}}
	*/
	
    //sample 9:Matmul
	/*Node* x=constant({{1,1,1,1,1,1,1,1},{2,4}});
	Node* y=constant({{1,1,1,1,1,1,1,1},{4,2}});
	Node* z=matmul(x,y);
	cout<<Run(*z)<<endl;//{{4,4}{4,4}}*/
	
	//sample 10:broadcast of +-*/
	/*Tensor a({1,1,1,1},{2,1,2,1}),b({3,3,3,3,3,3},{3,1,2});
	auto x=constant(a),y=constant(b);
	cout<<a+b<<'\n';//{{{{4,4}{4,4}}{{4,4}{4,4}}{{4,4}{4,4}}}{{{4,4}{4,4}}{{4,4}{4,4}}{{4,4}{4,4}}}}
	cout<<a-b<<'\n';//{{{{-2,-2}{-2,-2}}{{-2,-2}{-2,-2}}{{-2,-2}{-2,-2}}}{{{-2,-2}{-2,-2}}{{-2,-2}{-2,-2}}{{-2,-2}{-2,-2}}}}
	cout<<a*b<<'\n';//{{{{3,3}{3,3}}{{3,3}{3,3}}{{3,3}{3,3}}}{{{3,3}{3,3}}{{3,3}{3,3}}{{3,3}{3,3}}}}
	cout<<a/b<<'\n';//{{{{0.333333,0.333333}{0.333333,0.333333}}{{0.333333,0.333333}{0.333333,0.333333}}{{0.333333,0.333333}{0.333333,0.333333}}}{{{0.333333,0.333333}{0.333333,0.333333}}{{0.333333,0.333333}{0.333333,0.333333}}{{0.333333,0.333333}{0.333333,0.333333}}}}
	cout<<Run(*add(x,y))<<'\n';//the same as above
	cout<<Run(*sub(x,y))<<'\n';
	cout<<Run(*mul(x,y))<<'\n';
	cout<<Run(*div(x,y))<<'\n';*/
	
    return 0;
}
