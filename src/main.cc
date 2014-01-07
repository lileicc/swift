#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include "BlogProgram.h"
using namespace std;
using namespace swift::absyn;

extern BlogProgram* parse(const char*);
main(int argc, char* argv[]) {
  // open a file handle to a particular file:
  if (argc != 5){
    cout << "Incorrect number of arguments: " << argc << endl;
    exit(0);
  }
  const char* inp;
  const char* out;
  
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-i") == 0) inp = argv[i+1];
    if(strcmp(argv[i], "-o") == 0) out = argv[i+1];
  }
  BlogProgram* test = parse(inp);
  FILE *output = fopen(out, "w");
  test->print(output, 0);
}