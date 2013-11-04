/*
 * BlogProgram.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: yiwu
 */

#include "BlogProgram.h"

namespace swift {
namespace absyn {

BlogProgram::BlogProgram(int l, int c) :
    Absyn(l, c) {
}

BlogProgram::~BlogProgram() {
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      delete args[i];
}

size_t BlogProgram::size() {
  return args.size();
}

void BlogProgram::add(Stmt* decl) {
  args.push_back(decl);
}

Stmt* BlogProgram::get(int k) {
  return args[k];
}

const std::vector<Stmt*>& BlogProgram::getAll() {
  return args;
}

// For Debugging Use
void BlogProgram::print(FILE* file, int indent) {
  fprintf(file, "%*s(BlogProgram:\n", indent, "");
  fprintf(file, "%*s(args:\n", indent + 2, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent + 4);
  fprintf(file, "%*s)\n", indent + 2, "");
  fprintf(file, "%*s)\n", indent, "");
}

}
}
