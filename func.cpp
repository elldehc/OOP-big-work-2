#include "stdops.h"

Node* Run(Node& des) {
    set<Node*> calced;
    return des.eval(calced);
}

Node* Run(const map <Node*, pair<initializer_list<float>,initializer_list<int>> >& initmap,  Node& des) {
    set<Node*> calced;
    
    //placeholder赋值：迭代器遍历map中所有元素 hry
    for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
        iter->first->setvalue(Tensor(iter->second.first,iter->second.second));
        calced.insert(iter->first); //赋值过的结点加入集合calced
    }
    
    //initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
    return des.eval(calced);
}
Node* Run(const map <Node*, float>& initmap, Node& des) {
	set<Node*> calced;

	//placeholder赋值：迭代器遍历map中所有元素
	for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
		cerr<<iter->second<<endl;
		iter->first->setvalue(iter->second);
		calced.insert(iter->first); //赋值过的结点加入集合calced
	}

	//initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
	return des.eval(calced);
}

 ostream &operator<< (ostream& output , const Tensor& tensor) {
      int dim=tensor.size;
      if (dim==0) {
      	cout<<tensor.data[0]<<endl;
      	return output;
      }
      int stack=dim-1;
      for (int i=0; i<=stack; i++) cout<<"{";
      int count=0;
      for (auto iter=tensor.data.begin();iter!=tensor.data.end();iter++)
      {
            cout<<*iter;
            count++;
            if (count%tensor.num[stack]!=0) cout<<',';
            while (count%tensor.num[stack]==0){
                cout<<'}';
                stack--;
            }
            if (count!=tensor.num[0])
            while (stack<dim-1){
              stack++;
              cout<<'{';
            }
      }
      cout<<endl;   
      return output;
}
ostream& operator<< (ostream& out, Node* const nodeptr) {
    if (nodeptr == nullptr)
        return out;
    else {
    	cout<<nodeptr->getvalue()<<endl;
        return out;
    }
}
