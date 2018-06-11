#ifndef finc_h
#define finc_h

#include <iostream>
#include <map>
#include <set>

#include "Node.h"

Node* Run(Node& des);
Node* Run(const map <Node*, float>& initmap,  Node& des);

ostream& operator<< (ostream& out, Node* const nodeptr);

#endif /* finc_h */
