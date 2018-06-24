#include "stdops.h"

Node* Run(Node& des) {
	set<Node*> calced;
	Node *t = des.eval(calced);
	for (auto it : assign_map)it.first->set(it.second);
	assign_map.clear();
	return t;
}

/*Node* Run(const map <Node*, std::pair<std::initializer_list<float>, std::initializer_list<int>> >& initmap, Node& des) {
	set<Node*> calced;

	//placeholder赋值：迭代器遍历map中所有元素
	for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
		iter->first->setvalue(Tensor(iter->second.first, iter->second.second));
		calced.insert(iter->first); //赋值过的结点加入集合calced
	}

	//initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
	Node *t = des.eval(calced);
	for (auto it : assign_map)it.first->set(it.second);
	assign_map.clear();
	return t;
}*/

/*Node* Run(const map <Node*, float>& initmap, Node& des) {
	set<Node*> calced;

	//placeholder赋值：迭代器遍历map中所有元素
	for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
		iter->first->setvalue(iter->second);
		calced.insert(iter->first); //赋值过的结点加入集合calced
	}

	//initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
	Node *t = des.eval(calced);
	for (auto it : assign_map)it.first->set(it.second);
	assign_map.clear();
	return t;
}*/
Node* Run(const map <Node*, Tensor>& initmap, Node& des) {
	set<Node*> calced;

	//placeholder赋值：迭代器遍历map中所有元素
	for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
		iter->first->setvalue(iter->second);
		calced.insert(iter->first); //赋值过的结点加入集合calced
	}

	//initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
	Node *t = des.eval(calced);
	for (auto it : assign_map)it.first->set(it.second);
	assign_map.clear();
	return t;
}
#ifndef notensor
ostream &operator<< (ostream& out, const Tensor& tensor) {
	int dim = tensor.size;
	if (dim == 0) {
		cout << tensor.data[0] << endl;
		return out;
	}
	int stack = dim - 1;
	for (int i = 0; i <= stack; i++) cout << "{";
	int count = 0;
	for (auto iter = tensor.data.begin();iter != tensor.data.end();iter++)
	{
		cout << *iter;
		count++;
		if (count%tensor.num[stack] != 0) cout << ',';
		while (stack>=0&&count%tensor.num[stack] == 0) {
			cout << '}';
			stack--;
		}
		if (count != tensor.num[0])
			while (stack < dim - 1) {
				stack++;
				cout << '{';
			}
	}
	cout << endl;
	return out;
}
#endif

ostream& operator<< (ostream& out, Node* const nodeptr) {
	if (nodeptr == nullptr)
		return out;
	else {
		cout << nodeptr->getvalue();
		return out;
	}
}

float solve(Node *y, Node *x, float x0, float eps)
{
	//Doesn't guarantee to stop in finite time if there is no solution.
	if (Run({ {x,x0} }, *y) == nullptr) { std::cout << "solve error: input " << x0 << " is invalid for f(x).\n";return 0.0 / 0.0; }
	float y0 = y->getfloat();
	while (fabs(y0) > eps)
	{
		std::cout << "now:x=" << x0 << " f(x)=" << y0 << '\n';
		if (Run({ {x,x0} }, *(y->grad(x))) == nullptr) { std::cout << "solve error: input " << x0 << " is invalid for df(x)/dx.\n";return 0.0 / 0.0; }
		float t = y->grad(x)->getfloat();
		std::cout << "f'(x)=" << t << '\n';
		if (fabs(t) < eps) { std::cout << "solve error: arriving at minimum/maximum point " << x0 << " without finding a solution.\n";return 0.0 / 0.0; }
		x0 -= y0 / t;
		if (Run({ {x,x0} }, *y) == nullptr) { std::cout << "solve error: input " << x0 << " is invalid for f(x).\n";return 0.0 / 0.0; }
		y0 = y->getfloat();
	}
	return x0;
}


