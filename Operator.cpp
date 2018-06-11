#include "stdops.h"

Operator::Operator(Node* node1, Node* node2): left(node1), right(node2) { }

Node* Operator::getleft() {
    return left;
}

Node* Operator::getright() {
    return right;
}

Node* Operator::eval(set<Node*>& calced) {
    if (getleft()->eval(calced) == nullptr || getright()->eval(calced) == nullptr)
        return nullptr;
    else if (calced.insert(this).second) {
        setvalue(calc(calced));
        return this;
    } //insert().second为bool型，代表像这一集合插入元素是否成功，也即代表集合中原本是否有该元素
    else {
        return this;
    }
}
