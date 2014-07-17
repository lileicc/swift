/*
 * Semant.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#pragma once
#include <cstdio>
#include <memory>
#include <stack>
#include <string>
#include "../absyn/BlogProgram.h"
#include "../msg/ErrorMsg.h"
#include "../ir/BlogModel.h"
#include "../fabrica/TypeFactory.h"
#include "../fabrica/Functory.h"
#include "../fabrica/PreDeclFactory.h"

namespace swift {
namespace semant {

class Semant {
public:
  Semant();
  ~Semant();
  void process(absyn::BlogProgram* prog);
  ir::BlogModel* getModel();
  bool Okay();
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

  std::shared_ptr<ir::Expr> transExpr(absyn::Expr* expr);

  std::shared_ptr<ir::IfThen> transIfThen(absyn::IfExpr* expr);

  std::shared_ptr<ir::Branch> transBranch(absyn::CaseExpr* expr);

  std::shared_ptr<ir::Clause> transClause(absyn::Expr* expr);

  /*
   * Special Type Checking Function for OprExpr
   */
  const ir::Ty* OprExpr_checkType(ir::IRConstant op,
      const std::vector<std::shared_ptr<ir::Expr>>& arg);

  std::shared_ptr<ir::Expr> transExpr(absyn::OpExpr* expr);

  std::shared_ptr<ir::Expr> transExpr(absyn::FuncApp* expr);

  std::shared_ptr<ir::MapExpr> transExpr(absyn::MapExpr* expr);

  std::shared_ptr<ir::CardExpr> transExpr(absyn::CardinalityExpr* expr);

  std::shared_ptr<ir::QuantForm> transExpr(absyn::QuantExpr* expr);

  std::shared_ptr<ir::Expr> transExpr(absyn::VarRef* expr);

  std::shared_ptr<ir::SetExpr> transExpr(absyn::SetExpr* expr);

  std::shared_ptr<ir::ListSet> transExpr(absyn::ListSet* expr);

  std::shared_ptr<ir::CondSet> transExpr(absyn::CondSet* expr);

  std::shared_ptr<ir::Expr> transExpr(absyn::DistrExpr* expr);

  std::shared_ptr<ir::ConstSymbol> transExpr(absyn::Literal* expr);

  std::shared_ptr<ir::Expr> transExpr(absyn::ArrayExpr* expr);

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

  /*
   * process evidence
   */
  void transEvidence(absyn::Evidence* ne);

  /*
   * process query
   */
  void transQuery(absyn::Query* nq);

  /**
   * translate the type in abstract syntax to intermediate representation
   */
  const ir::Ty* transTy(const absyn::Ty & typ);

  /**
   * translate the variable declaration, which can be defined in
   * function header or quantified formula
   */
  const std::shared_ptr<ir::VarDecl> transVarDecl(const absyn::VarDecl & vd);

  /**
   * lookup the nametype in tyFactory, if not exist, produce an error
   * return the found NameTy or NULL
   */
  const ir::NameTy* lookupNameTy(const std::string & name);

  /**
   * lookup a general type in tyFactory, if not exist, produce an error
   * return the found Ty or NULL
   */

  const ir::Ty* lookupTy(const std::string & name);

  /**
   * translate the array reference to string representation
   */
  static std::string arrayRefToString(const std::string & name, int idx);

  // Check whether an expr is : #TypeDomain
  static bool isCardAll(std::shared_ptr<ir::Expr> ptr);

  void error(int line, int col, std::string info);
  void warning(int line, int col, std::string info);

  fabrica::TypeFactory tyFactory;
  fabrica::Functory functory;
  fabrica::PreDeclFactory predeclFactory;
  msg::ErrorMsg errorMsg;
  ir::BlogModel* model;

  //stack used to store local variable
  std::map<std::string, std::stack<std::shared_ptr<ir::VarDecl> > > local_var;

  bool isResultUsed;
};

}
} /* namespace swift */
