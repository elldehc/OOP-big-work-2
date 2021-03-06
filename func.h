#ifndef finc_h
#define finc_h

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "Node.h"


Node* Run(Node& des);
//Node* Run(const map <Node*, std::pair<std::initializer_list<float>, std::initializer_list<int>> >& initmap, Node& des);
//Node* Run(const map <Node*,float>& initmap, Node& des);
Node* Run(const map <Node*,Tensor>& initmap, Node& des);

#ifndef notensor
ostream& operator<< (ostream& out, const Tensor& tensor);
#endif
ostream& operator<< (ostream& out, Node* const nodeptr);

float solve(Node *y,Node *x,float x0=0,float eps=1e-12);

#endif /* finc_h */
