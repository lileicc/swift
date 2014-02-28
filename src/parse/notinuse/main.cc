#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "BlogProgram.h"
using namespace std;
using namespace swift::absyn;

extern BlogProgram* parse(const char*);
main() {
  // open a file handle to a particular file:
  const char* inp = "input.in";
  BlogProgram* test = parse(inp);
  FILE *output = fopen("output.out", "w");
  test->print(output, 0);
  //NumStDecl* st = (NumStDecl*)(blog->get(0));
  //Symbol o = st->getArgOrigin(0);
  //cout << "current val: " << o.getValue() << endl;
  //Evidence* t = (Evidence*)(blog->get(0));
  //cout << "assigned" << endl;
  //NumStRef* left = (NumStRef*)(t->getLeft());
  //cout << "expression extracted" << endl;
  
  //blog->print(output, 0);
  
  
}