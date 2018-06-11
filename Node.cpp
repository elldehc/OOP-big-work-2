#include "Node.h"

void Node::setvalue(float v) {
    value = v;
}

float Node::getvalue() {
    return value;
}

Node::~Node() {std::cerr<<"Node destroyed.\n"; }
