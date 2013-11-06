/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <cstdio>
#include <string>
#include "../absyn/BlogProgram.h"
#include "../msg/ErrorMsg.h"
#include "../fabrica/TypeFactory.h"
#include "../fabrica/Functory.h"

namespace swift {
namespace semant {

class Semant {
public:
  Semant();
  ~Semant();
  void process(absyn::BlogProgram* prog);
private:
  /**
   * process all declarations, including
   *   - type declaration
   *   - distinct symbols
   *   - function signature (but not the function body)
   */
  void processDeclarations(absyn::BlogProgram* prog);

  /**
   * process all statement bodies, including
   *   - function declaration body
   *   - number statement body
   *   - evidence
   *   - query
   */
  void processBodies(absyn::BlogProgram* prog);

  void transExpr(absyn::Expr* expr);

  void transExpr(absyn::OpExpr* expr);

  void transExpr(absyn::FuncApp* expr);

  /**
   * create a declared type, shout error message if duplicate
   */
  void transTyDecl(absyn::TypDecl* td);

  /**
   * process distinct/guaranteed symbols
   * e.g.
   *   distinct Blip b[100];
   */
  void transDistinctDecl(absyn::DistinctDecl* dd);

  /**
   * process function declaration, but not the body
   * just process the signature
   */
  void transFuncDecl(absyn::FuncDecl* fd);

  /**
   * process origin function declaration
   */
  void transOriginDecl(absyn::OriginDecl* od);

  /**
   * process function body
   */
  void transFuncBody(absyn::FuncDecl* fd);

  /**
   * process number statement body
   */
  void transNumSt(absyn::NumStDecl* nd);

  /**
   * translate the type in abstract syntax to intermediate representation
   */
  const ir::Ty* transTy(const absyn::Ty & typ);

  /**
   * translate the variable declaration, which can be defined in
   * function header or quantified formula
   */
  const ir::VarDecl* transVarDecl(const absyn::VarDecl & vd);

  /**
   * lookup the nametype in tyFactory, if not exist, produce an error
   * return the found NameTy or NULL
   */
  const ir::NameTy* lookupNameTy(const std::string & name);

  /**
   * translate the array reference to string representation
   */
  static std::string arrayRefToString(const std::string & name, int idx);

  void error(int line, int col, const std::string & info);
  fabrica::TypeFactory tyFactory;
  fabrica::Functory functory;
  msg::ErrorMsg errorMsg;
};

}
} /* namespace swift */
