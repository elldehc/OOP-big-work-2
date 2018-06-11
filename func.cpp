#include "func.h"

Node* Run(Node& des) {
    set<Node*> calced;
    return des.eval(calced);
}

Node* Run(const map <Node*, float>& initmap,  Node& des) {
    set<Node*> calced;
    
    //placeholder赋值：迭代器遍历map中所有元素
    for (auto iter = initmap.begin(); iter != initmap.end(); iter++) {
        iter->first->setvalue(iter->second);
        calced.insert(iter->first); //赋值过的结点加入集合calced
    }
    
    //initmap.clear(); //清除用于初始化的map，下次调用run前在主函数重新赋值
    return des.eval(calced);
}

ostream& operator<< (ostream& out, Node* const nodeptr) {
    if (nodeptr == nullptr)
        return out;
    else {
        cout << nodeptr->getvalue();
        return out;
    }
}
