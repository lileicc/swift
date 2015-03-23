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

void BlogProgram::add(const std::vector<Stmt*>& stmts) {
  args.insert(args.end(), stmts.begin(), stmts.end());
}

Stmt* BlogProgram::get(int k) {
  return args[k];
}

const std::vector<Stmt*>& BlogProgram::getAll() {
  return args;
}

std::vector<Stmt*>& BlogProgram::getAllRef() {
  return args;
}

void BlogProgram::clear() {
  args.clear();
}

// For Debugging Use
void BlogProgram::print(FILE* file, int indent) {
  fprintf(file, "%*s(BLOGProgram:\n", indent, "");
  for (size_t i = 0; i < args.size(); i++)
    if (args[i] != NULL)
      args[i]->print(file, indent+2);
  fprintf(file, "%*s)\n", indent, "");
}

}
}
