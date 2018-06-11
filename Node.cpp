#include "stdops.h"


void Node::setvalue(float v) {
    value = v;
}

float Node::getvalue() {
    return value;
}

const map<Node *,Node *>& Node::grad()
{
	if(grads.empty())getgrad();
	return grads;
}
Node * Node::grad(Node *p)
{
	auto it=grad().find(p);
	if(it==grad().end())return Zero;else return it->second;
}
Node::~Node() {std::cerr<<"Node destroyed.\n"; }
