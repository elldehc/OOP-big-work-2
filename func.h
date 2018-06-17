#ifndef finc_h
#define finc_h

#include <iostream>
#include <map>
#include <set>
#include <vector> //
#include "Node.h"

Node* Run(Node& des);
Node* Run(const map <Node*,pair<initializer_list<float>, initializer_list<int>>>& initmap,  Node& des);
Node* Run(const map <Node*,float>& initmap, Node& des);
ostream &operator<< (ostream& output , const Tensor& tensor);
ostream& operator<< (ostream& out, Node* const nodeptr);
  
#endif /* finc_h */
