/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 * 
 * Issue: @MarkovOrder created on Jul 17, 2014 by yiwu
 */

#include "Semant.h"

#include<iostream>
#include <memory>
#include <utility>
#include <set>

#include "../ir/IRHeader.h"
#include "../predecl/PreDeclList.h"

namespace swift {
namespace semant {

Semant::Semant() :
    errorMsg(stderr) {
  model = std::make_shared<ir::BlogModel>();
  isResultUsed = false;
}

Semant::~Semant() {
}

std::shared_ptr<ir::BlogModel> Semant::getModel() {
  // Note: IMPORTANT
  // Since model uses shared_ptr to store type domains
  // after deleting model, all type domains will be deleted!
  // and they should not be deleted again from tyFactory!
  return model;
}

void Semant::process(absyn::BlogProgram* prog) {
  processDeclarations(prog);
  processBodies(prog);
  // add TypeDomains to model
  for (auto&p : tyFactory.getAllTyTable())
    if (p.second->getTyp() == ir::IRConstant::NAMETY)
      model->addTypeDomain(
          std::shared_ptr<ir::TypeDomain>(
              ((const ir::NameTy*) p.second)->getRefer()));
  // Add Functions
  for (auto&p : functory.getAllFuncList())
    model->addFunction(std::shared_ptr<ir::FuncDefn>(p));
}

void Semant::processDeclarations(absyn::BlogProgram* prog) {
  absyn::TypDecl* td;
  absyn::DistinctDecl* dd;
  absyn::FuncDecl* fd;
  absyn::OriginDecl* od;
  for (auto&st : prog->getAll()) {
    td = dynamic_cast<absyn::TypDecl*>(st);
    if (td != NULL) { // it is type declaration
      transTyDecl(td);
      continue;
    }
  }

  // Note: We assume that function name cannot be the same as type name
  for (auto&st : prog->getAll()) {
    fd = dynamic_cast<absyn::FuncDecl*>(st);
    if (fd != NULL) { // it is function declaration
      transFuncDecl(fd);
      continue;
    }

    od = dynamic_cast<absyn::OriginDecl*>(st);
    if (od != NULL) {
      transOriginDecl(od);
      continue;
    }
  }

  // Note: We assume that distinct name cannot be the same as function name or type name
  for (auto&st : prog->getAll()) {
    dd = dynamic_cast<absyn::DistinctDecl*>(st);
    if (dd != NULL) { // it is distinct declaration
      transDistinctDecl(dd);
      continue;
    }
  }

}

void Semant::processBodies(absyn::BlogProgram* prog) {
  absyn::FuncDecl* fd;
  absyn::NumStDecl* nd;
  absyn::Evidence* ne;
  absyn::Query* nq;
  for (auto&st : prog->getAll()) {
    fd = dynamic_cast<absyn::FuncDecl*>(st);
    if (fd != NULL) { // it is function declaration
      transFuncBody(fd);
      continue;
    }

    nd = dynamic_cast<absyn::NumStDecl*>(st);
    if (nd != NULL) {
      transNumSt(nd);
      continue;
    }

    ne = dynamic_cast<absyn::Evidence*>(st);
    if (ne != NULL) {
      transEvidence(ne);
      continue;
    }

    nq = dynamic_cast<absyn::Query*>(st);
    if (nq != NULL) {
      transQuery(nq);
      continue;
    }
  }
}

void Semant::transTyDecl(absyn::TypDecl* td) {
  if (!tyFactory.addNameTy(td->get().getValue())) {
    error(td->line, td->col,
        "type name < " + td->get().getValue() + " > is defined multiple times");
  }
}

void Semant::transDistinctDecl(absyn::DistinctDecl* dd) {
  const ir::NameTy* nt = lookupNameTy(dd->getTyp().getValue());
  if (nt != NULL) {
    for (size_t i = 0; i < dd->size(); i++) {
      const std::string& name = dd->getVar(i).getValue();
      int k = dd->getLen(i);
      if (k < 1) {
        error(dd->line, dd->col,
            "Dimension of a distinct symbol < " + name + " >must be positive!");
        continue;
      }
      if (k == 1 && lookupNameTy(name) != NULL) {
        error(dd->line, dd->col,
            "Distinct Symbol < " + name + " > already defined as a Type");
        continue;
      }
      if (functory.getFunc(name,
          std::vector<std::shared_ptr<ir::VarDecl>>()) != NULL) {
        error(dd->line, dd->col,
            "Distinct Symbol < " + name + " > already defined as a Function");
        continue;
      }
      if (k == 1) {
        if (!tyFactory.addInstSymbol(nt, name)) {
          error(dd->line, dd->col,
              "Distinct Symbol < " + name + " > already defined");
        }
      } else {
        if (tyFactory.getInstSymbol(name) != NULL) {
          error(dd->line, dd->col,
              "Distinct Symbol < " + name + " > already defined!");
          continue;
        }
        for (int j = 0; j < k; j++) {
          if (!tyFactory.addInstSymbol(nt, arrayRefToString(name, j))) {
            error(dd->line, dd->col,
                "Distinct Symbol < " + name + "[" + std::to_string(j)
                    + "] > already defined");
          }
        }
      }
    }
  } else {
    error(dd->line, dd->col,
        "Type < " + dd->getTyp().getValue() + " > is not defined!");
  }
}

void Semant::transFuncDecl(absyn::FuncDecl* fd) {
  const ir::Ty* rettyp = transTy(fd->getRetTyp());
  const std::string& name = fd->getFuncName().getValue();
  if (rettyp == NULL) {
    error(fd->line, fd->col,
        "Return Type of FunctionDecl < " + name + " >is undefined!");
    return;
  }
  if (lookupNameTy(name) != NULL) {
    error(fd->line, fd->col,
        "Function name < " + name + " >already defined as Type Name");
    return;
  }
  std::vector<std::shared_ptr<ir::VarDecl> > vds;
  for (size_t i = 0; i < fd->argSize(); i++) {
    vds.push_back(transVarDecl(fd->getArg(i)));
  }
  // Function can contain at most one Timestep argument
  int timestep_count = 0;
  for (auto&v : vds) {
    if (v->getTyp() == tyFactory.getTimestepTy())
      ++ timestep_count;
  }
  if (timestep_count > 1) {
    error(fd->line, fd->col, "function < " + name + " > contains more than 1 timestep arguments!");
  }

  if (!functory.addFuncDefn(name, rettyp, vds, fd->isRandom())) {
    error(fd->line, fd->col,
        "function < " + name
            + " > with the same argument type already defined");
  }
  else {
    // Process Timestep
    functory.getFunc(name, vds)->processTemporal(tyFactory.getTimestepTy());
  }
}

void Semant::transOriginDecl(absyn::OriginDecl* od) {
  const ir::NameTy* retTyp = lookupNameTy(od->getTyp().getValue());
  const ir::NameTy* srcTy = lookupNameTy(od->getArg().getValue());
  if (retTyp == NULL) {
    error(od->line, od->col,
        "Return type of Origin Decl <" + od->getTyp().getValue()
            + "> undefined");
    return;
  }
  if (srcTy == NULL) {
    error(od->line, od->col,
        "Source type of Origin Decl <" + od->getTyp().getValue()
            + "> undefined");
    return;
  }
  if (!tyFactory.addOriginAttr(srcTy, retTyp, od->getFunc().getValue())) {
    error(od->line, od->col,
        "origin attribute <" + od->getFunc().getValue() + "> already exist!");
  }
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::Expr *expr) {
  auto ret = std::make_shared<ir::Expr>();
  if (dynamic_cast<absyn::OpExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::OpExpr*) expr));
  if (dynamic_cast<absyn::FuncApp*>(expr) != nullptr)
    return (ret = transExpr((absyn::FuncApp*) expr));
  if (dynamic_cast<absyn::MapExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::MapExpr*) expr));
  if (dynamic_cast<absyn::CardinalityExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::CardinalityExpr*) expr));
  if (dynamic_cast<absyn::QuantExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::QuantExpr*) expr));
  if (dynamic_cast<absyn::SetExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::SetExpr*) expr));
  if (dynamic_cast<absyn::Literal*>(expr) != nullptr)
    return (ret = transExpr((absyn::Literal*) expr));
  if (dynamic_cast<absyn::ArrayExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::ArrayExpr*) expr));

  if (dynamic_cast<absyn::DistrExpr*>(expr) != nullptr) {
    //@Deprecated
    warning(expr->line, expr->col, "Parsing expression to <DistrExpr> in Absyn should be deprecated! FuncApp is recommended!");
    absyn::FuncApp* funcapp = new absyn::FuncApp(expr->line, expr->col, ((absyn::DistrExpr*)expr)->getDistrName());
    for (size_t i = 0; i < expr->size(); ++ i)
      funcapp->add(expr->get(i));
    ret = transExpr(funcapp);

    // delete extra pointer
    funcapp->clearArgs();
    delete funcapp;

    return ret;
  }
  if (dynamic_cast<absyn::VarRef*>(expr) != nullptr) {
    //@Deprecated
    warning(expr->line, expr->col, "Parsing expression to <VarRef> in Absyn should be deprecated! FuncApp is recommended!");
    ret = transVarRef(((absyn::VarRef*) expr)->getVar().getValue());
    if (ret != nullptr) return ret;
  }
  error(expr->line, expr->col, "Semant Error! Illegal Expression!");
  return ret;
}

std::shared_ptr<ir::IfThen> Semant::transIfThen(absyn::IfExpr* expr) {
  if (expr->getCond() == NULL || expr->getThen() == NULL) {
    error(expr->line, expr->col,
        "Error! Condition and Then cannot be empty for IF!");
    return std::make_shared<ir::IfThen>(nullptr, nullptr);
  }
  auto ptr = std::make_shared<ir::IfThen>(transExpr(expr->getCond()),
      transClause(expr->getThen()));
  if (ptr->getThen() == NULL) {
    // TODO: to allow null expression in then clause
    error(expr->line, expr->col, "Then Clause cannot be NULL!");
    return ptr;
  }

  // Type Check
  ptr->setTyp(ptr->getThen()->getTyp());
  if (expr->getElse() != NULL)
    ptr->setElse(transClause(expr->getElse()));
  else
    ptr->setElse(std::make_shared<ir::NullSymbol>());
  if (ptr->getElse()->getTyp() == NULL)
    ptr->getElse()->setTyp(ptr->getTyp());
  else {
    if (ptr->getElse()->getTyp() != ptr->getThen()->getTyp()) {
      error(expr->line, expr->col, "Return type conflict between thenclause<"+
        ptr->getThen()->getTyp()->toString()+"> and elseclause<"+
        ptr->getElse()->getTyp()->toString()+">");
    }
  }

  // Randomness Checking
  ptr->setRandom(ptr->getCond()->isRandom() || ptr->getThen()->isRandom() || ptr->getElse()->isRandom());

  return ptr;
}

int Semant::checkBranchArg(std::shared_ptr<ir::Expr> e) {
  auto dbl = lookupTy(ir::IRConstString::DOUBLE);
  if (e->getTyp() == dbl)
    return -1;
  if (std::dynamic_pointer_cast<ir::ConstSymbol>(e) != nullptr) {
    return 1;
  }
  if (std::dynamic_pointer_cast<ir::ArrayExpr>(e) != nullptr) {
    auto arr = std::dynamic_pointer_cast<ir::ArrayExpr>(e);
    for (size_t i = 0; i < arr->argSize(); ++i) {
      if (std::dynamic_pointer_cast<ir::ConstSymbol>(arr->get(i)) == nullptr)
        return -1;
      if (arr->get(i)->getTyp() == dbl)
        return -1;
    }
    return arr->argSize();
  }
  return -1;
}

std::shared_ptr<ir::Branch> Semant::transBranch(absyn::CaseExpr* expr) {
  std::shared_ptr<ir::Branch> ptr(new ir::Branch());
  if (expr->getTest() == NULL || expr->getMap() == NULL) {
    error(expr->line, expr->col, "Arguments Format Error for < CaseExpr >!");
    return ptr;
  }
  /*
   * Note that We cannot directly apply trans MapExpr here!
   *   since arguments of MapExpr are all Expr
   *   while for Branch, arguments could be clauses
   */
  absyn::MapExpr* mp = (absyn::MapExpr*) (expr->getMap());
  // Similar Type Checking Process to transExpr(MapExpr)
  const ir::Ty* fromTy = NULL;
  int n_from_args = -1; // indicate the number of elements to pass to the case expr
  const ir::Ty* toTy = NULL;
  for (size_t i = 0; i < mp->mapSize(); i++) {
    std::shared_ptr<ir::Expr> symbol = transExpr(mp->getFrom(i));
    std::shared_ptr<ir::Clause> clause = transClause(mp->getTo(i));
    // Support for multicase expression
    //  i.e. case [A,B] in {[true,false]->1, [true,true]->0}
    // symbol could be constSymbol(except Real) and Array of ConstSymbol(except Real)
    int cur_from_args = checkBranchArg(symbol);
    if (cur_from_args < 0) {
      error(mp->getFrom(i)->line, mp->getFrom(i)->col,
        "Illegal From Arguments in the Map of the < CaseExpr >!\
        The type must be [ConstSymbol (except Real) | Array of ConstSymbol (except Real)].");
      return ptr;
    }
    if (n_from_args < 0) n_from_args = cur_from_args;
    else {
      if (n_from_args != cur_from_args) {
        error(mp->getFrom(i)->line, mp->getFrom(i)->col,
          "All the FROM arguments in the Map of the < CaseExpr > must have the SAME Dimension!");
        return ptr;
      }
    }
    if (symbol->getTyp() != NULL) {
      if (fromTy == NULL)
        fromTy = symbol->getTyp();
      else {
        if (fromTy != symbol->getTyp()) {
          error(mp->getFrom(i)->line, mp->getFrom(i)->col,
              "From Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    if (clause->getTyp() != NULL) {
      if (toTy == NULL)
        toTy = clause->getTyp();
      else {
        if (toTy != clause->getTyp()) {
          error(mp->getTo(i)->line, mp->getTo(i)->col,
              "To Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    // Add a new Branch
    ptr->addBranch(symbol, clause);
  }
  if (fromTy == NULL) {
    error(mp->line, mp->col, "Type of *From* terms cannot be determined!");
    return ptr;
  }
  if (toTy == NULL) {
    warning(mp->line, mp->col, "Type of *To* terms cannot be determined!");
  }
  // Fill the type field of NullExpr
  for (auto&c : ptr->getConds())
    if (c->getTyp() == NULL)
      c->setTyp(fromTy);
  for (auto&b : ptr->getBranches())
    if (b->getTyp() == NULL)
      b->setTyp(toTy);
  ptr->setTyp(toTy);
  ptr->setVar(transExpr(expr->getTest()));
  if (ptr->getVar()->getTyp() != fromTy) {
    error(expr->getTest()->line, expr->getTest()->col, 
      "The type of *Test Var* does not match the from Type of the Map in < CaseExpr >!");
    return ptr;
  }
  if (n_from_args > 1) {
    if (std::dynamic_pointer_cast<ir::ArrayExpr>(ptr->getVar()) == nullptr
      || (int)ptr->getVar()->argSize() != n_from_args) {
      error(expr->getTest()->line, expr->getTest()->col,
        "The Dimension of *Test Var* differs from the From Type of the Map in < CaseExpr >!");
      return ptr;
    }
    ptr->setArgDim(n_from_args);
  }

  // Randomness Checking
  if (ptr->getVar()->isRandom())
    ptr->setRandom(true);
  for (auto&b : ptr->getBranches())
    if (b->isRandom()) {
      ptr->setRandom(true);
      break;
    }
  return ptr;
}

std::shared_ptr<ir::Clause> Semant::transClause(absyn::Expr* expr) {
  if (dynamic_cast<absyn::IfExpr*>(expr) != NULL)
    return transIfThen((absyn::IfExpr*) expr);
  if (dynamic_cast<absyn::CaseExpr*>(expr) != NULL)
    return transBranch((absyn::CaseExpr*) expr);
  return transExpr(expr);
}

std::shared_ptr<ir::MapExpr> Semant::transExpr(absyn::MapExpr* expr) {
  // Note: We assume expr -> expr
  // Type Checking
  auto ptr = std::make_shared<ir::MapExpr>();
  const ir::Ty* fromTy = NULL;
  const ir::Ty* toTy = NULL;
  for (size_t i = 0; i < expr->mapSize(); i++) {
    ptr->addMap(transExpr(expr->getFrom(i)), transExpr(expr->getTo(i)));
    // Check and Update From Type
    if (ptr->getFrom(i)->getTyp() != NULL) {
      if (fromTy == NULL)
        fromTy = ptr->getFrom(i)->getTyp();
      else {
        if (fromTy != ptr->getFrom(i)->getTyp()) {
          error(expr->line, expr->col,
              "From Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    // Check and Update To Type
    if (ptr->getTo(i)->getTyp() != NULL) {
      if (toTy == NULL)
        toTy = ptr->getTo(i)->getTyp();
      else {
        if (toTy != ptr->getTo(i)->getTyp()) {
          error(expr->line, expr->col,
              "To Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
  }
  if (fromTy == NULL || toTy == NULL) {
    error(expr->line, expr->col,
        "There must be at least one non-null term in From Terms or To Terms!");
    return ptr;
  }
  // Fill type for NullExpr
  for (size_t i = 0; i < expr->mapSize(); i++) {
    if (ptr->getFrom(i)->getTyp() == NULL)
      ptr->getFrom(i)->setTyp(fromTy);
    if (ptr->getTo(i)->getTyp() == NULL)
      ptr->getTo(i)->setTyp(toTy);
  }
  // Set Type
  ptr->setFromTyp(fromTy);
  ptr->setToTyp(toTy);
  ptr->setTyp(tyFactory.getUpdateTy(new ir::MapTy(fromTy, toTy)));

  // Randomness Checking
  for (size_t i = 0; i < ptr->mapSize(); ++ i)
    if (ptr->getFrom(i)->isRandom() || ptr->getTo(i)->isRandom()) {
      ptr->setRandom(true);
      break;
    }
  return ptr;
}

ir::IRConstant OprExpr_convertOpConst(absyn::AbsynConstant op) {
  using absyn::AbsynConstant;
  using ir::IRConstant;
  switch (op) {
  case AbsynConstant::PLUS:
    return IRConstant::PLUS;
  case AbsynConstant::MINUS:
    return IRConstant::MINUS;
  case AbsynConstant::MUL:
    return IRConstant::MUL;
  case AbsynConstant::DIV:
    return IRConstant::DIV;
  case AbsynConstant::MOD:
    return IRConstant::MOD;
  case AbsynConstant::POWER:
    return IRConstant::POWER;
  case AbsynConstant::EQ:
    return IRConstant::EQ;
  case AbsynConstant::NEQ:
    return IRConstant::NEQ;
  case AbsynConstant::LT:
    return IRConstant::LT;
  case AbsynConstant::GT:
    return IRConstant::GT;
  case AbsynConstant::LE:
    return IRConstant::GE;
  case AbsynConstant::AND:
    return IRConstant::AND;
  case AbsynConstant::OR:
    return IRConstant::OR;
  case AbsynConstant::NOT:
    return IRConstant::NOT;
  case AbsynConstant::IMPLY:
    return IRConstant::IMPLY;
  case AbsynConstant::SUB:
    return IRConstant::SUB;
  default:
    return IRConstant::NA;
  }
}

bool OprExpr_isPrimitive(const ir::Ty* t) {
  return (t != NULL)
      && (t->getTyp() == ir::IRConstant::INT
          || t->getTyp() == ir::IRConstant::DOUBLE
          || t->getTyp() == ir::IRConstant::BOOL
          || t->getTyp() == ir::IRConstant::STRING
          || t->getTyp() == ir::IRConstant::TIMESTEP);
}

bool OprExpr_isNumerical(const ir::Ty* t) {
  return (t != NULL)
      && (t->getTyp() == ir::IRConstant::INT
          || t->getTyp() == ir::IRConstant::DOUBLE
          || t->getTyp() == ir::IRConstant::MATRIX);
}

const ir::Ty* Semant::OprExpr_checkType(ir::IRConstant op,
    const std::vector<std::shared_ptr<ir::Expr>>& arg) {
  using ir::IRConstant;
  using ir::IRConstString;
  switch (op) {
  // Bool
  // Unary Operator
  case IRConstant::NOT:
    if (arg[0]->getTyp() != lookupTy(IRConstString::BOOL))
      return NULL;
    return arg[0]->getTyp();
    // Logical Operator
  case IRConstant::AND:
  case IRConstant::OR:
  case IRConstant::IMPLY:
    if (arg[0]->getTyp() != lookupTy(IRConstString::BOOL)
        || arg[1]->getTyp() != lookupTy(IRConstString::BOOL))
      return NULL;
    return arg[0]->getTyp();
  case IRConstant::LT:
  case IRConstant::GT:
  case IRConstant::LE:
  case IRConstant::GE:
    if (!OprExpr_isPrimitive(arg[0]->getTyp())
        || !OprExpr_isPrimitive(arg[1]->getTyp()))
      return NULL;
    if ((arg[0]->getTyp()->getTyp() == ir::IRConstant::STRING 
          || arg[1]->getTyp()->getTyp() == ir::IRConstant::STRING)
      && arg[0]->getTyp() != arg[1]->getTyp())
      return NULL;
    return lookupTy(IRConstString::BOOL);
  case IRConstant::NEQ:
  case IRConstant::EQ:
    // Check Null Type
    if (arg[0]->getTyp() == NULL && arg[1]->getTyp() != NULL)
      arg[0]->setTyp(arg[1]->getTyp());
    if (arg[0]->getTyp() != NULL && arg[1]->getTyp() == NULL)
      arg[1]->setTyp(arg[0]->getTyp());
    if (arg[0]->getTyp() != arg[1]->getTyp())
      return NULL;
    return lookupTy(IRConstString::BOOL);
    // Numerical Operator
  case IRConstant::MOD:
    // Special Check for TimeStep (MOD)
    if (isSubType(arg[0]->getTyp(), arg[1]->getTyp())
      && arg[0]->getTyp() == lookupTy(ir::IRConstString::TIMESTEP))
      return arg[0]->getTyp();
    if (arg[0]->getTyp() != arg[1]->getTyp() // For MOD, current everything should be INT
        || arg[0]->getTyp() != lookupTy(IRConstString::INT))
      return NULL;
    return arg[0]->getTyp();
  case IRConstant::PLUS:
    // Special case for positive sign: i.e. +1
    if (arg.size() == 1) {
      if (arg[0]->getTyp() == lookupTy(IRConstString::INT)
        || arg[0]->getTyp() == lookupTy(IRConstString::DOUBLE))
        return arg[0]->getTyp();
      else
        return NULL;
    }
    // Special Case for String Concatenation
    if (arg[0]->getTyp() == arg[1]->getTyp()
        && arg[0]->getTyp() == lookupTy(IRConstString::STRING))
      return arg[0]->getTyp();
  case IRConstant::MINUS:
    // Special case for minus sign: i.e. -1.0
    if (arg.size() == 1) {
      if (arg[0]->getTyp() == lookupTy(IRConstString::INT)
        || arg[0]->getTyp() == lookupTy(IRConstString::DOUBLE))
        return arg[0]->getTyp();
      else
        return NULL;
    }
  case IRConstant::MUL:
  case IRConstant::DIV:
    // Special Check for TimeStep (PLUS, MINUS, MUL, DIV)
    if (getSuperType(arg[0]->getTyp(), arg[1]->getTyp()) == lookupTy(ir::IRConstString::TIMESTEP))
      return lookupTy(ir::IRConstString::TIMESTEP);
  case IRConstant::POWER:
    if (getSuperType(arg[0]->getTyp(), arg[1]->getTyp()) == NULL
        || !OprExpr_isNumerical(arg[0]->getTyp())
        || !OprExpr_isNumerical(arg[1]->getTyp()))
      return NULL;
    if (op == IRConstant::POWER) {
      if (arg[1]->getTyp()->getTyp() == ir::IRConstant::MATRIX) {
        return NULL;
      }
      if (arg[0]->getTyp()->getTyp() == ir::IRConstant::MATRIX) 
        return lookupTy(IRConstString::MATRIX);
      return lookupTy(IRConstString::DOUBLE);
    }
    return getSuperType(arg[0]->getTyp(), arg[1]->getTyp());

    // Address Operator
  case IRConstant::SUB: {
    if (arg[0]->getTyp() == NULL) return NULL;
    if (arg[1]->getTyp() != tyFactory.getTy(ir::IRConstString::INT)
        || (arg[0]->getTyp()->getTyp() != ir::IRConstant::ARRAY
            && arg[0]->getTyp()->getTyp() != ir::IRConstant::MATRIX))
      return NULL;
    if (arg[0]->getTyp()->getTyp() == ir::IRConstant::MATRIX) // We assume that RealMatrix[] always return *DOUBLE*
      return lookupTy(ir::IRConstString::DOUBLE);
    const ir::ArrayTy* arr = (const ir::ArrayTy*) (arg[0]->getTyp());
    if (arr->getDim() == 1)
      return arr->getBase();
    else
      return tyFactory.getUpdateTy(
          new ir::ArrayTy(arr->getBase(), arr->getDim() - 1));
  }
    break;
  default:
    return NULL;
  }
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::OpExpr* expr) {
  // Special check for TimeStep: e.g. @1 <=> AT(1)
  if (expr->getOp() == absyn::AbsynConstant::AT) {
    if (expr->getLeft() != NULL || expr->getRight() == NULL) {
      error(expr->line, expr->col, "Invalid/Incomplete Operator for @<AT> Operator!");
      return std::make_shared<ir::NullSymbol>();
    }
    auto arg = transExpr(expr->getRight());
    if (arg == nullptr || arg->getTyp() != lookupTy(ir::IRConstString::INT)) {
      error(expr->line, expr->col, "Invalid Argument for @<AT> Operator! The correct format should be <NULL> AT <INT>.");
      return std::make_shared<ir::NullSymbol>();
    }
    if (std::dynamic_pointer_cast<ir::IntLiteral>(arg) != nullptr) {
      auto val = std::dynamic_pointer_cast<ir::IntLiteral>(arg);
      auto ret = std::make_shared<ir::TimestepLiteral>(val->getValue());
      ret->setTyp(lookupTy(ir::IRConstString::TIMESTEP));
      // TODO: Currently is a Hacking Implementation
      //     Should Move to Analyser Finally!!!!
      if (ret->getValue() > model->getTempLimit())
        model->setTempLimit(ret->getValue());
      return ret;
    }
    else {
      // In this case, AT just plays the role of type conversion
      arg->setTyp(lookupTy(ir::IRConstString::TIMESTEP));
      return arg;
    }
  }

  auto ret = std::make_shared<ir::OprExpr>(
      OprExpr_convertOpConst(expr->getOp()));
  if (ret->getOp() == ir::IRConstant::NA
      || (ret->getOp() == ir::IRConstant::NOT
          && (expr->getLeft() != NULL || expr->getRight() == NULL))
      || (ret->getOp() != ir::IRConstant::NOT
          && expr->getRight() == NULL)
      || (ret->getOp() != ir::IRConstant::NOT
          && ret->getOp() != ir::IRConstant::PLUS && ret->getOp() != ir::IRConstant::MINUS
          && expr->getLeft() == NULL)) {
    error(expr->line, expr->col, "Invalid/Incomplete Operator for OprExpr!");
    return ret;
  }

  // Special Case: 
  //         Replace OprExpr with a InstSymbolRef
  // Note: isRandom() == false
  if (ret->getOp()
      == ir::IRConstant::SUB 
      && ((dynamic_cast<absyn::FuncApp*>(expr->getLeft())) != NULL || (dynamic_cast<absyn::VarRef*>(expr->getLeft())) != NULL) 
      // Although VarRef is deprecated, we did the checking here!
      && (dynamic_cast<absyn::IntLiteral*>(expr->getRight())) != NULL) {
    std::string var;
    if ((dynamic_cast<absyn::VarRef*>(expr->getLeft())) != NULL)
      var = ((absyn::VarRef*) (expr->getLeft()))->getVar().getValue();
    else
      var = ((absyn::FuncApp*) (expr->getLeft()))->getFuncName().getValue();
    int k = ((absyn::IntLiteral*) (expr->getRight()))->getValue();
    if (k >= 0) {
      auto sym = tyFactory.getInstSymbol(arrayRefToString(var, k));
      if (sym != NULL && local_var.count(var) == 0) {
        auto ref = std::make_shared<ir::InstSymbolRef>(sym);
        ref->setTyp(lookupNameTy(sym->getRefer()->getName()));
        return ref;
      }
    }
  }

  // Unary Operator
  if (ret->getOp() == ir::IRConstant::NOT) {
    ret->addArg(transExpr(expr->getRight()));
  } else 
  if ((ret->getOp() == ir::IRConstant::PLUS || ret->getOp() == ir::IRConstant::MINUS) && expr->getLeft() == NULL) {
    ret->addArg(transExpr(expr->getRight()));
  } else {
    ret->addArg(transExpr(expr->getLeft()));
    ret->addArg(transExpr(expr->getRight()));
  }
  // Type Checking
  ret->setTyp(OprExpr_checkType(ret->getOp(), ret->getArgs()));
  if (ret->getTyp() == NULL) {
    // Special Checking for RealMatrix[][]
    // We need to convert RealMatrix[i][j] to RealMatrix(i,j)
    bool isGetMatrixEntry = false;
    if (ret->getOp() == ir::IRConstant::SUB
      && std::dynamic_pointer_cast<ir::OprExpr>(ret->get(0)) != nullptr) {
      auto left_sub = std::dynamic_pointer_cast<ir::OprExpr>(ret->get(0));
      if (left_sub->getOp() == ir::IRConstant::SUB
        && left_sub->get(0)->getTyp() == lookupTy(ir::IRConstString::MATRIX)) { // Here is the Case!
        std::vector<std::shared_ptr<ir::Expr>> args;
        args.push_back(left_sub->get(0));
        args.push_back(left_sub->get(1));
        args.push_back(ret->get(1));
        ret = std::make_shared<ir::OprExpr>(ir::IRConstant::PARENTHESES);
        ret->setArgs(args);
        ret->setTyp(lookupTy(ir::IRConstString::DOUBLE));
        isGetMatrixEntry = true;
      }
    }

    if (!isGetMatrixEntry)
      error(expr->line, expr->col, "Error Type Matching for OprExpr!");
  }
  /*
   * TODO: Add crucial check for Markov Order! Now it is a hack!! (@MarkovOrder)
   *   we only check the case of:
   *    MINUS-EXPR: (A) - @k
   *      k will be the markov order
   */
  if (ret->getTyp() == lookupTy(ir::IRConstString::TIMESTEP)
      && ret->getOp() == ir::IRConstant::MINUS && ret->getArgs().size() == 2
      && std::dynamic_pointer_cast<ir::TimestepLiteral>(ret->get(1)) != nullptr)
      model->updateMarkovOrder(std::dynamic_pointer_cast<ir::TimestepLiteral>(ret->get(1))->getValue());

  // Randomness Checking
  for (auto&a : ret->getArgs())
    if (a->isRandom()) {
      ret->setRandom(true);
      break;
    }
  return ret;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::FuncApp* expr) {
  std::string func = expr->getFuncName().getValue();
  // Parse Arguments
  std::vector<std::shared_ptr<ir::Expr>> args;
  std::vector<std::shared_ptr<ir::VarDecl>> decl;
  for (size_t i = 0; i < expr->size(); i++) {
    args.push_back(transExpr(expr->get(i)));
    decl.push_back(std::make_shared<ir::VarDecl>(args.back()->getTyp(), ""));
  }

  if (args.size() == 0) {
    // Single Variable Reference
    std::shared_ptr<ir::Expr> varRef = transVarRef(func);
    if (varRef != nullptr) return varRef;
  }

  //TODO: Think more about size()  @sizefunction
  // Currently a hack for size()
  if (expr->getFuncName().getValue() == "size") {
    if (expr->size() != 1) {
      error(expr->line, expr->col, "size() only accept exactly one argument!");
      return processCardExpr(NULL);
    } else
      return processCardExpr(expr->get(0));
  }

  // Check Builtin Functions and Distributions
  //   Note: Especially for Prev()!!!!
  auto fc = predeclFactory.getDecl(func);
  if (fc != nullptr) {

    auto ptr = fc->getNew(args, &tyFactory);
    if (ptr == nullptr) {
      warning(expr->line, expr->col, "Function/Distribution < " + func + " > is Built-in! Type Checking Error for Built-in Function/Distribution!");
    }
    else {
      // TODO: here is a hack!!!! Better Checking for Markov Order (@MarkovOrder)
      // Special Check : (hack, @MarkovOrder)
      //   when ptr is Prev(t, k) then k will become the markov order!
      if (std::dynamic_pointer_cast<ir::FunctionCall>(ptr) != nullptr) {
        auto ref = std::dynamic_pointer_cast<ir::FunctionCall>(ptr);
        if (ref->isBuiltin() && ref->getBuiltinRefer()->getName() == "prev") {
          model->updateMarkovOrder(std::dynamic_pointer_cast<ir::IntLiteral>(ref->get(0))->getValue());
        }
      }
      return ptr;
    }
  }

  // Special Case for Origin Function
  if (decl.size() == 1
      && (dynamic_cast<const ir::NameTy*>(decl[0]->getTyp()) != NULL)) {
    auto att = tyFactory.getOriginAttr((const ir::NameTy*) decl[0]->getTyp(),
        func);
    if (att != NULL) {
      auto ptr = std::make_shared<ir::OriginRefer>(att, args[0]);
      // type checking
      ptr->setTyp(att->getTyp());
      // Randomness checking
      ptr->setRandom(true);
      return ptr;
    }
  }

  auto ptr = std::make_shared<ir::FunctionCall>(functory.getFunc(func, decl));

  if (ptr->getRefer() == nullptr) {
    // No Corresponding Function found!
    //  assume it is a distribution
    return transDistrb(func, args, expr->line, expr->col);
  }

  // Type Checking
  ptr->setTyp(ptr->getRefer()->getRetTyp());
  ptr->setArgs(args);

  // Random Checking
  ptr->setRandom(ptr->getRefer()->isRand());
  for (auto&a : args)
    if (a->isRandom()) {
      ptr->setRandom(true);
      break;
    }

  // Special Check for Temporal FunctionCall
  if (ptr->getRefer()->isTemporal())
    ptr->processTemporal(tyFactory.getTimestepTy());
  return ptr;
}

std::shared_ptr<ir::CardExpr> Semant::processCardExpr(absyn::Expr* expr) {
  std::shared_ptr<ir::CardExpr> cd(new ir::CardExpr());
  cd->setTyp(lookupTy(ir::IRConstString::INT));
  std::shared_ptr<ir::Expr> b = transExpr(expr);
  std::shared_ptr<ir::SetExpr> st = std::dynamic_pointer_cast<ir::SetExpr>(b);
  if (st == nullptr) {
    error(expr->line, expr->col,
      "Invalid Cardinality Expression! Body must be a SetExpr!");
    return cd;
  }
  cd->setBody(st);
  // randomness checking
  cd->setRandom(st->isRandom());
  return cd;
}

std::shared_ptr<ir::CardExpr> Semant::transExpr(absyn::CardinalityExpr* expr) {
  std::shared_ptr<ir::CardExpr> cd(new ir::CardExpr());
  cd->setTyp(lookupTy(ir::IRConstString::INT));
  if (expr->size() != 1) {
    error(expr->line, expr->col, "Invalid Cardinality Expression!");
    return cd;
  }
  return processCardExpr(expr->get(0));
}

std::shared_ptr<ir::QuantForm> Semant::transExpr(absyn::QuantExpr* expr) {
  auto ptr = std::make_shared<ir::QuantForm>(
      expr->getTyp() == absyn::AbsynConstant::FORALL ?
          ir::IRConstant::FORALL : ir::IRConstant::EXISTS);
  ptr->setTyp(lookupTy(ir::IRConstString::BOOL));
  ptr->addVar(transVarDecl(expr->getVar()));
  if (lookupNameTy(expr->getVar().getVar().getValue()) != NULL) {
    error(expr->line, expr->col,
        "Variable <" + expr->getVar().getVar().getValue()
            + "> in Quant Form cannot be a type name!");
  }
  // Add Local Variable
  local_var[ptr->getVar()->getVarName()].push(ptr->getVar());

  ptr->setCond(transExpr(expr->getCond()));

  if (ptr->get(0)->getTyp() != lookupTy(ir::IRConstString::BOOL)) {
    error(expr->line, expr->col,
        "Condition in Quant Form must return boolean value!");
  }

  // Remove Local Variable
  auto it = local_var.find(ptr->getVar()->getVarName());
  it->second.pop();
  if (it->second.empty())
    local_var.erase(it);
  // randomness
  // TODO: to check randomness in some special cases
  ptr->setRandom(true);
  return ptr;
}

std::shared_ptr<ir::Expr> Semant::transVarRef(std::string var) {
  // 3 cases: local variable, voidfunccall, const symbol
  if (local_var.count(var) != 0) {
    // Local Variable
    std::shared_ptr<ir::VarRefer> ret = std::make_shared<ir::VarRefer>(
        local_var[var].top());
    ret->setTyp(ret->getRefer()->getTyp());
    return ret; // randomness is false
  }
  auto func = functory.getFunc(var,
      std::vector<std::shared_ptr<ir::VarDecl> >());
  if (func != NULL) {
    // Void Function Call
    // TODO: To Change to Void Function Call
    //std::shared_ptr<ir::VoidFuncCall> ret(new ir::VoidFuncCall(func));
    auto ret = std::make_shared<ir::FunctionCall>(func);
    ret->setTyp(func->getRetTyp());
    // randomness
    ret->setRandom(func->isRand());
    return ret;
  }
  auto sym = tyFactory.getInstSymbol(var);
  if (sym != NULL) {
    // Const Symbol
    std::shared_ptr<ir::InstSymbolRef> ret(new ir::InstSymbolRef(sym));
    ret->setTyp(lookupNameTy(sym->getRefer()->getName()));
    return ret; // randomness = false;
  }
  return nullptr;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::SetExpr* expr) {
  if (dynamic_cast<absyn::TupleSetExpr*>(expr) != NULL)
    return transExpr((absyn::TupleSetExpr*) expr);
  if (dynamic_cast<absyn::CondSet*>(expr) != NULL)
    return transExpr((absyn::CondSet*) expr);
  if (dynamic_cast<absyn::ListSet*>(expr) != NULL)
    return transExpr((absyn::ListSet*) expr);
  error(expr->line, expr->col, "Parsing Error! Illegal SetExpr!");
  return std::make_shared<ir::SetExpr>(ir::IRConstant::NA);
}

std::shared_ptr<ir::ListSet> Semant::transExpr(absyn::ListSet* expr) {
  auto ptr = std::make_shared<ir::ListSet>();
  const ir::Ty* base = NULL;
  for (size_t i = 0; i < expr->size(); ++i) {
    ptr->addArg(transExpr(expr->get(i)));
    auto e = ptr->get(i);
    if (e->getTyp() != NULL) {
      if (base == NULL)
        base = e->getTyp();
      else {
        if (base != e->getTyp()) {
          error(expr->line, expr->col,
              "Set must contain instances of the same type!");
          break;
        }
      }
    } else {
      error(expr->line, expr->col, "Set cannot contain NULL!");
      break;
    }
    if (std::dynamic_pointer_cast<ir::ConstSymbol>(e) == nullptr) {
      error(expr->line, expr->col, "Set must contain constant symbols!");
      break;
    }
  }
  // Note: when base == NULL, this is an empty set
  ptr->setTyp(tyFactory.getUpdateTy(new ir::SetTy(base)));
  // randomness checking
  for (auto&a : ptr->getArgs())
    if (a->isRandom()) {
      ptr->setRandom(true);
      break;
    }
  return ptr;
}

std::shared_ptr<ir::CondSet> Semant::transExpr(absyn::CondSet* expr) {
  std::shared_ptr<ir::VarDecl> var = transVarDecl(expr->getVar());

  // Add Local Variable
  if (var->getTyp() != NULL
      && var->getVarName().size() > 0&& expr->getCond() != NULL)
    local_var[var->getVarName()].push(var);
  std::shared_ptr<ir::Expr> e =
      expr->getCond() == NULL ? nullptr : transExpr(expr->getCond());
  // Remove Local Variable
  if (var->getTyp() != NULL
      && var->getVarName().size() > 0&& expr->getCond() != NULL) {
    auto it = local_var.find(var->getVarName());
    it->second.pop();
    if (it->second.empty())
      local_var.erase(it);
  }
  auto ptr = std::make_shared<ir::CondSet>(var, nullptr, e);

  if (e != nullptr && e->getTyp() != tyFactory.getTy(ir::IRConstString::BOOL)) {
    error(expr->line, expr->col,
        "Condition of the set must return Boolean Value!");
  }

  ptr->setTyp(tyFactory.getUpdateTy(new ir::SetTy(var->getTyp())));

  // randomness checking
  // TODO: to check randomness in special cases
  ptr->setRandom(true);
  return ptr;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::TupleSetExpr* expr) {
  if (expr->getVarDecls().size() != expr->getExps().size()) {
    error(expr->line, expr->col, "The length of Expr List does not match the length of VarDecl List for < TupleSetExpr >");
  }
  if (expr->getVarDecls().size() == 0) {
    error(expr->line, expr->col, "< TupleSetExpr > should contain at least one variable!");
    return std::shared_ptr<ir::CondSet>(new ir::CondSet(nullptr,nullptr));
  }
  if (expr->getVarDecls().size() > 1) {
    warning(expr->line,expr->col,"We now only suppor < TupleSetExpr > with one variable! By default we will only pick the first variable.");
    // TODO:
    // @TupleSetExpr
    // To support general TupleSetExpr
  }

  std::shared_ptr<ir::VarDecl> var = transVarDecl(expr->getVarDecl(0));

  // Add Local Variable
  if (var->getTyp() != NULL
    && var->getVarName().size() > 0)
    local_var[var->getVarName()].push(var);
  std::shared_ptr<ir::Expr> cond =
    expr->getCond() == NULL ? nullptr : transExpr(expr->getCond());
  std::shared_ptr<ir::Expr> func = 
    expr->getExp(0) == NULL ? nullptr : transExpr(expr->getExp(0));
  // Remove Local Variable
  if (var->getTyp() != NULL
    && var->getVarName().size() > 0) {
    auto it = local_var.find(var->getVarName());
    it->second.pop();
    if (it->second.empty())
      local_var.erase(it);
  }

  // Process Expression applied on variable defined in the setExpr
  if (std::dynamic_pointer_cast<ir::ConstSymbol>(func) != nullptr) {
    return func;
  }
  if (std::dynamic_pointer_cast<ir::VarRefer>(func) != nullptr) { // just normal condset
    auto v = std::dynamic_pointer_cast<ir::VarRefer>(func);
    if (v->getRefer().get() == var.get())
      func = nullptr;
  }

  auto ptr = std::make_shared<ir::CondSet>(var, func, cond);

  if (cond != nullptr && cond->getTyp() != tyFactory.getTy(ir::IRConstString::BOOL)) {
    error(expr->line, expr->col,
      "Condition of the set must return Boolean Value!");
  }

  if (func == nullptr)
    ptr->setTyp(tyFactory.getUpdateTy(new ir::SetTy(var->getTyp())));
  else
    ptr->setTyp(tyFactory.getUpdateTy(new ir::SetTy(func->getTyp())));

  // randomness checking
  // TODO: to check randomness in special cases
  ptr->setRandom(true);
  return ptr;
}

std::shared_ptr<ir::Expr> Semant::transDistrb(
  std::string name, std::vector<std::shared_ptr<ir::Expr>> args,
  int line, int col) {
  // TODO: add type checking for predecl distribution
  const predecl::PreDecl* distr = predeclFactory.getDecl(name);
  
  if (distr == NULL) {
    // not predeclared distribution
    warning(line, col, "No function defined for <" + name + ">! Customized distribution assumed! No type checking will be performed!");
    
    auto dist = std::make_shared<ir::Distribution>(name);
    dist->setArgs(args);
    dist->setRandom(true);
    dist->processArgRandomness();
    return dist;
  }

  auto ret = distr->getNew(args, &tyFactory);
  if (ret == nullptr) {
    error(line, col,
        "Type Checking failed for <" + name + "> distribution!");
    return std::make_shared<ir::Distribution>(name, distr);
  }
  return ret;
}

std::shared_ptr<ir::ConstSymbol> Semant::transExpr(absyn::Literal* expr) {
  // int, double, string, boolean, timestep, null
  if (dynamic_cast<absyn::NullLiteral*>(expr) != NULL) {
    // TODO: type of NULL Symbol should be assigned later!
    //       NULL will appear in MAP, OpExpr, If, Branch, FunctionDefn
    return std::shared_ptr<ir::NullSymbol>(new ir::NullSymbol());
  }
  if (dynamic_cast<absyn::IntLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::IntLiteral> ret(
        new ir::IntLiteral(((absyn::IntLiteral*) expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::INT));
    return ret;
  }
  if (dynamic_cast<absyn::DoubleLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::DoubleLiteral> ret(
        new ir::DoubleLiteral(((absyn::DoubleLiteral*) expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::DOUBLE));
    return ret;
  }
  if (dynamic_cast<absyn::BoolLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::BoolLiteral> ret(
        new ir::BoolLiteral(((absyn::BoolLiteral*) expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::BOOL));
    return ret;
  }
  if (dynamic_cast<absyn::StringLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::StringLiteral> ret(
        new ir::StringLiteral(((absyn::StringLiteral*) expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::STRING));
    return ret;
  }
  if (dynamic_cast<absyn::TimeStampLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::TimestepLiteral> ret = std::make_shared<ir::TimestepLiteral>((dynamic_cast<absyn::TimeStampLiteral*>(expr))->getValue());
    ret->setTyp(lookupTy(ir::IRConstString::TIMESTEP));
    // TODO: Currently is a Hacking Implementation
    //     Should Move to Analyser Finally!!!!
    if (ret->getValue() > model->getTempLimit())
      model->setTempLimit(ret->getValue());
    return ret;
  }
  error(expr->line, expr->col, "Illegal Literal!");
  return std::make_shared<ir::NullSymbol>();
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::ArrayExpr* expr) {
  std::shared_ptr<ir::Expr> ret = std::make_shared<ir::ArrayExpr>();
  int dim = expr->getDim();
  for (size_t i = 0; i < expr->size(); ++i) {
    ret->addArg(transExpr(expr->get(i)));
  }
  const ir::Ty* intarray_ty = tyFactory.getUpdateTy(new ir::ArrayTy(lookupTy(ir::IRConstString::INT), 1));
  const ir::Ty* mat_ty = tyFactory.getTy(ir::IRConstString::MATRIX);
  const ir::Ty* base = NULL;
  for (size_t i = 0; i < ret->argSize(); ++i)
    if (ret->get(i)->getTyp() != NULL) {
      if (base == NULL || isSubType(base, ret->get(i)->getTyp())
        || (base == intarray_ty && ret->get(i)->getTyp()->getTyp() == ir::IRConstant::MATRIX))
        base = ret->get(i)->getTyp();
    }

  // Special Check for MatrixExpr
  bool isMatrix = false;
  if (base != NULL) {
    if (base->getTyp() == ir::IRConstant::DOUBLE && dim == 1) {
      // special check for RowVector
      bool okay = true;
      for (size_t i = 0; i < ret->argSize() && okay; ++i) {
        const ir::Ty* t = ret->get(i)->getTyp();
        if (t == NULL || !isSubType(t, base)) okay = false;
      }
      if (okay) {
        std::shared_ptr<ir::MatrixExpr> mat_ret = std::make_shared<ir::MatrixExpr>();
        mat_ret->setArgs(ret->getArgs());
        mat_ret->setTyp(mat_ty);
        mat_ret->setRowVecFlag(true);
        mat_ret->setColVecFlag(ret->argSize() == 1);
        ret=mat_ret;
        isMatrix = true;
      }
    }
    else
    if (base->getTyp() == ir::IRConstant::MATRIX && dim == 2) {
      // special check for ColVector and RealMatrix
      bool okay_colvec = true, okay_mat = true;
      bool has_intarray = false;
      for (size_t i = 0; i < ret->argSize() && okay_mat; ++i) {
        // check whether it is a int array
        if (ret->get(i)->getTyp() == intarray_ty && std::dynamic_pointer_cast<ir::ArrayExpr>(ret->get(i)) != nullptr) {
          auto intarr = std::dynamic_pointer_cast<ir::ArrayExpr>(ret->get(i));
          if (intarr->argSize() > 1)
            okay_colvec = false;
          has_intarray = true;
          continue;
        }
        if (std::dynamic_pointer_cast<ir::MatrixExpr>(ret->get(i)) != nullptr) {
          auto mat_expr = std::dynamic_pointer_cast<ir::MatrixExpr>(ret->get(i));
          if (mat_expr->isRowVec()) { // must be a row vector!
            if (mat_expr->argSize() > 1) // one row has more than 1 element ==> must not be a col vector
              okay_colvec = false;
          } else
            okay_mat = false;
        } else
          okay_mat = false; // not a valid row matrix in this case
      }
      if (okay_mat) {
        if (has_intarray) { // convert all Int ArrayExpr to Real Row Vectors
          std::vector<std::shared_ptr<ir::Expr>> args = ret->getArgs();
          for (size_t i = 0; i < ret->argSize(); ++i) {
            if (ret->get(i)->getTyp() == intarray_ty) {
              auto row_vec = std::make_shared<ir::MatrixExpr>();
              row_vec->setArgs(ret->get(i)->getArgs());
              row_vec->setRandom(ret->get(i)->isRandom());
              row_vec->setTyp(base);
              row_vec->setRowVecFlag(true);
              row_vec->setColVecFlag(ret->get(i)->argSize() == 1);
              args[i] = row_vec; // replace the ArrayExpr with a new MatrixExpr(rowvec = true)
            }
          }
          ret->setArgs(args);
        }
        std::shared_ptr<ir::MatrixExpr> mat_ret = std::make_shared<ir::MatrixExpr>();
        if (okay_colvec) {
          std::vector<std::shared_ptr<ir::Expr>> colvec_args;
          for (size_t i = 0; i < ret->argSize(); ++ i)
            colvec_args.push_back(ret->get(i)->get(0));
          mat_ret->setArgs(colvec_args);
        } else
          mat_ret->setArgs(ret->getArgs());
        mat_ret->setTyp(mat_ty);
        mat_ret->setRowVecFlag(ret->argSize() == 1);
        mat_ret->setColVecFlag(okay_colvec);
        ret = mat_ret;
        isMatrix = true;
      }
    }
  }

  // Normal ArrayExpr Case
  if (!isMatrix) { // Not Converted to MatrixExpr
    if (base == NULL
      || (base->getTyp() == ir::IRConstant::ARRAY
      && ((const ir::ArrayTy*) base)->getDim() != expr->getDim() - 1)
      || (base->getTyp() != ir::IRConstant::ARRAY && expr->getDim() != 1)) {
      error(expr->line, expr->col, "Illegal Array Expr");
    }
    else {
      for (size_t i = 0; i < ret->argSize(); ++i) {
        const ir::Ty* t = ret->get(i)->getTyp();
        if (t == NULL)
          ret->get(i)->setTyp(base);
        else if (t != base && !isSubType(t, base)) {
          error(expr->line, expr->col, "Illegal Array Expr");
          break;
        }
      }
      ret->setTyp(tyFactory.getUpdateTy(new ir::ArrayTy(base, dim)));
    }
  }

  // randomness
  for (auto&a: ret->getArgs())
    if (a->isRandom()) {
      ret->setRandom(true);
      break;
    }
  return ret;
}

void Semant::transFuncBody(absyn::FuncDecl* fd) {
  const ir::Ty* rettyp = transTy(fd->getRetTyp());
  const std::string& name = fd->getFuncName().getValue();
  std::vector<std::shared_ptr<ir::VarDecl> > vds;
  for (size_t i = 0; i < fd->argSize(); i++) {
    vds.push_back(transVarDecl(fd->getArg(i)));
  }
  std::shared_ptr<ir::FuncDefn> fun = functory.getFunc(name, vds);
  if (fun != NULL) {
    // Add Local Variables
    for (auto&v : fun->getArgs())
      local_var[v->getVarName()].push(v);
    // Add Temporal Variables
    if (fun->isTemporal())
      local_var[fun->getTemporalArg()->getVarName()].push(fun->getTemporalArg());

    fun->setBody(transClause(fd->getExpr()));
    // Type checking for Function Declaration
    if (fun->getBody()->getTyp() == NULL)
      fun->getBody()->setTyp(rettyp);
    else {
      if (!isSubType(fun->getBody()->getTyp(), rettyp)) { // Type Checking Failed!
        bool special_case = false;
        // Special Case checking for Real func() = RealMatrix * RealMatrix
        // We only raise a warning and return the first element of the result matrix
        if (rettyp == lookupTy(ir::IRConstString::DOUBLE)
          && fun->getBody()->getTyp() == lookupTy(ir::IRConstString::MATRIX)) {
          auto body = std::dynamic_pointer_cast<ir::Expr>(fun->getBody());
          if (body != nullptr && std::dynamic_pointer_cast<ir::MatrixExpr>(body) == nullptr) {
            /*
              The computation result of the body is a RealMatrix.
              However, the declaration of the function is Real.
              We assume that the return value will always become a 1x1 RealMatrix. A warnning will be raised.
              e.g. Real fun() = A * B ===> Real fun() = as_scalar(A * B)
            */
            std::vector<std::shared_ptr<ir::Expr> > args;
            args.push_back(body);
            auto mat = predecl::PreDeclList::asScalarFuncDecl.getNew(args, &tyFactory);
            fun->setBody(mat);
            warning(fd->line, fd->col, "The return type of the body is RealMatrix. But the Declared Type is Real! The first element of the result matrix will be returned.");
            special_case = true;
          }
        }
        if (!special_case) {
          fprintf(stderr, "func<%s> rettyp = %s  bodytyp = %s\n", fun->getName().c_str(), fun->getRetTyp()->toString().c_str(),
            fun->getBody()->getTyp()->toString().c_str());
          error(fd->line, fd->col, "The type of the function body does not match its declaration!");
        }
      }
    }

    // Check Randomness
    if (fun->getBody()->isRandom() != fun->isRand()) {
      error(fd->line, fd->col, "Incorrect Randomness Declaration!");
    }

    // if it is random, then need to add the link from arg --> thisfunction
    if (fun->isRand()) {
      for (auto&arg : fun->getArgs()) {
        auto nty = dynamic_cast<const ir::NameTy*>(arg->getTyp());
        if (nty)
          nty->getRefer()->addReferFun(std::shared_ptr<ir::FuncDefn>(fun));
      }
    }

    // Remove Temporal Variables
    if(fun->isTemporal()) {
      auto it = local_var.find(fun->getTemporalArg()->getVarName());
      it->second.pop();
      if (it->second.empty())
        local_var.erase(it);
    }
    // Remove Local Variables
    for (auto&v : fun->getArgs()) {
      auto it = local_var.find(v->getVarName());
      it->second.pop();
      if (it->second.empty())
        local_var.erase(it);
    }
  }
}

void Semant::transNumSt(absyn::NumStDecl* nd) {
  std::string name = nd->getTyp().getValue();
  const ir::NameTy* ty = tyFactory.getNameTy(name);
  if (ty == NULL) {
    error(nd->line, nd->col,
        "Invalid Number Statement! No corresponding type definition!");
    return;
  }
  auto numst = std::make_shared<ir::NumberStmt>(ty->getRefer());
  std::set<std::string> defined_var, defined_att;
  bool success = true;
  for (size_t k = 0; k < nd->argSize(); k++) {
    std::string var = nd->getArgVar(k).getValue();
    std::string att = nd->getArgOrigin(k).getValue();
    if (defined_var.count(var) != 0) {
      error(nd->line, nd->col,
          std::to_string(k + 1) + "th arg var <" + var
              + ">of NumberStmt is already defined in this number statement!");
      success = false;
    }
    if (tyFactory.getTy(var) != NULL) {
      error(nd->line, nd->col,
          std::to_string(k + 1) + "th arg var <" + var
              + "> of NumberStmt cannot be a type!");
      success = false;
    }
    defined_var.insert(var);
    if (defined_att.count(att) != 0) {
      error(nd->line, nd->col,
          std::to_string(k + 1) + "th origin field <" + att
              + "> is already declared in this number statement!");
      success = false;
    }
    const ir::OriginAttr* o = tyFactory.getOriginAttr(ty, att);
    if (o == NULL) {
      error(nd->line, nd->col,
          std::to_string(k + 1) + "th origin field <" + att
              + "> is not declared in the program!");
      success = false;
    }
    defined_att.insert(att);
    if (!success)
      break;

    numst->addArg(o, var);
  }
  if (!success) {
    return;
  }

  // Add Local Variable
  for (auto&v : numst->getAllVars())
    local_var[v->getVarName()].push(v);
  numst->setBody(transClause(nd->getExpr()));

  for (auto&v : numst->getAllVars()) {
    auto it = local_var.find(v->getVarName());
    it->second.pop();
    if (it->second.empty())
      local_var.erase(it);
  }

  if (numst->getBody()->getTyp() != lookupTy(ir::IRConstString::INT)) {
    error(nd->line, nd->col,
        "Body of Number Statement must return Integer value!");
    return;
  }

  tyFactory.addNumberStmt(numst);
}

void Semant::transEvidence(absyn::Evidence* ne) {
  auto lhs = transExpr(ne->getLeft());
  auto rhs = transExpr(ne->getRight());
  if (std::dynamic_pointer_cast<ir::Expr>(lhs) == nullptr) {
    error(ne->line, ne->col, "Left hand side of Evidence must be an Expression!");
    return;
  }
  if (std::dynamic_pointer_cast<ir::Expr>(rhs) == nullptr) {
    error(ne->line, ne->col, "Right hand side of Evidence must be an Expression!");
    return;
  }

  // type checking for equality
  if (lhs->getTyp() == NULL && rhs->getTyp() != NULL)
    lhs->setTyp(rhs->getTyp());
  if (lhs->getTyp() != NULL && rhs->getTyp() == NULL)
    rhs->setTyp(lhs->getTyp());
  if (lhs->getTyp() == NULL) // Both are NULL! always hold!
    return;
  if (!isSubType(rhs->getTyp(), lhs->getTyp()) ||
      (lhs->getTyp()->getTyp() == ir::IRConstant::MATRIX && rhs->getTyp() != lhs->getTyp())) {
    error(ne->line, ne->col, "Types not match for equality in Evidence!");
    return;
  }
  // Format Checking
  //     we assume that :
  //         left side  : function call | #TypeName
  //         right side : non-random expression
  if (rhs->isRandom()
      || ((std::dynamic_pointer_cast<ir::FunctionCall>(lhs) == nullptr)
          && !isCardAll(lhs))) {
    error(ne->line, ne->col,
        "Evidence format not correct! We assume < FunctionCall | #TypeName = Non-Random Expr >!");
    return; // TODO: build internal function to avoid this
  }
  // Temporal Evidence Checking
  // TODO: currently we only allowed temporal evidence with timestep = TS_Literal
  //    --> to support arbitrary timestep argument in future
  if (std::dynamic_pointer_cast<ir::FunctionCall>(lhs) != nullptr) {
    auto func = std::dynamic_pointer_cast<ir::FunctionCall>(lhs);
    if (func->isTemporal()) {
      if (std::dynamic_pointer_cast<ir::TimestepLiteral>(func->getTemporalArg()) == nullptr) {
        error(ne->line, ne->col,
          "Illegal Timestep Argument in the left hand side!\
           We currently only accept fixed timestep as argument in temporal evidence.");
        return ;
      }
    }
  }
  model->addEvidence(
      std::make_shared<ir::Evidence>(lhs, rhs));
}

void Semant::transQuery(absyn::Query* nq) {
  auto ptr = transExpr(nq->getExpr());
  if (!isCardAll(ptr)
      && (std::dynamic_pointer_cast<ir::FunctionCall>(ptr) == nullptr)) {
    /* General Case: Arbitrary Expr
    TODO: check if we need to build a internal Void Function Call to represent this expr
      */
    model->addQuery(std::make_shared<ir::Query>(ptr, nq->getExpr()->toString(), true));
  }
  else {// Special Case: function call
    auto fun = std::dynamic_pointer_cast<ir::FunctionCall>(ptr);
    if (fun->isTemporal()) {
      if (std::dynamic_pointer_cast<ir::TimestepLiteral>(fun->getTemporalArg()) == nullptr) {
        error(nq->line, nq->col,
          "Illegal Timestep Argument in query expression!\
                     We currently only accept fixed timestep as argument for temporal variables.");
        return;
      }
    }
    model->addQuery(std::make_shared<ir::Query>(ptr, nq->getExpr()->toString()));
  }
}

const ir::Ty* Semant::transTy(const absyn::Ty& typ) {
  int dim = typ.getDim();
  const ir::Ty* ty = tyFactory.getTy(typ.getTyp().getValue());
  if (ty == NULL) {
    error(typ.line, typ.col,
        "Type < " + typ.getTyp().getValue() + " > not found");
    return NULL;
  }

  // Check if use Matrix
  if (ty->getTyp() == ir::IRConstant::MATRIX)
    model->setUseMatrix(true);

  if (dim == 0) {
    return ty;
  } else {
    return tyFactory.getUpdateTy(new ir::ArrayTy(ty, dim));
  }
}

const std::shared_ptr<ir::VarDecl> Semant::transVarDecl(
    const absyn::VarDecl & vd) {
  const ir::Ty* ty = transTy(vd.getTyp());
  return std::make_shared<ir::VarDecl>(ty, vd.getVar().getValue());
}

bool Semant::isCardAll(std::shared_ptr<ir::Expr> ptr) {
  auto card = std::dynamic_pointer_cast<ir::CardExpr>(ptr);
  if (card == nullptr) {
    return false;
  }
  auto st = std::dynamic_pointer_cast<ir::CondSet>(card->getBody());
  if (st == nullptr) {
    return false;
  }
  return st->getCond() == nullptr; // Nothing to do with func!
}

void Semant::error(int line, int col, std::string info) {
  errorMsg.error(line, col, info);
}

void Semant::warning(int line, int col, std::string info) {
  errorMsg.warning(line, col, info);
}

const ir::NameTy* Semant::lookupNameTy(const std::string & name) {
  return tyFactory.getNameTy(name);
}

const ir::Ty* Semant::lookupTy(const std::string & name) {
  if (name == ir::IRConstString::BLOG_MATRIX
      || name == ir::IRConstString::MATRIX)
      model->setUseMatrix(true);
  return tyFactory.getTy(name);
}

std::string Semant::arrayRefToString(const std::string & name, int idx) {
  return name + "[" + std::to_string(idx) + "]";
}

bool Semant::isSubType(const ir::Ty* A, const ir::Ty*B) {
  if (A==NULL || B==NULL) return false;
  if (A->getTyp() == B->getTyp()) return true;
  // special case for A = INT && B = UNSIGNED(TIMESTEP)
  if (A->getTyp() == ir::IRConstant::INT && B->getTyp() == ir::IRConstant::TIMESTEP)
    return true;
  // special case for A = INT && B = DOUBLE
  if(A->getTyp() == ir::IRConstant::INT && B->getTyp() == ir::IRConstant::DOUBLE)
    return true;
  // special cases for RealMatrix
  if ((A->getTyp() == ir::IRConstant::INT || A->getTyp() == ir::IRConstant::DOUBLE)
      && B->getTyp() == ir::IRConstant::MATRIX)
      return true;
  return false;
}

const ir::Ty* Semant::getSuperType(const ir::Ty* A, const ir::Ty* B) {
  if (isSubType(A, B)) return B;
  if (isSubType(B, A)) return A;
  return NULL;
}

bool Semant::Okay() {
  return errorMsg.Okay();
}

}
} /* namespace swift */
