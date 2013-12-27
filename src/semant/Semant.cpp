/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#include "Semant.h"

#include <memory>
#include <utility>
#include <set>

#include "../ir/IRHeader.h"

namespace swift {
namespace semant {

Semant::Semant() :
    errorMsg(stderr) {
  // TODO Auto-generated constructor stub
  model = new ir::BlogModel();
}

Semant::~Semant() {
  // TODO Auto-generated destructor stub
  delete model;
}

ir::BlogModel* Semant::getModel() {
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
  for (auto p : tyFactory.getAllTyTable()) 
    if (p.second->getTyp() == ir::IRConstant::NAMETY)
      model->addTypeDomain(std::shared_ptr<ir::TypeDomain>(((const ir::NameTy*)p.second)->getRefer()));
  // Add Functions
  for (auto p : functory.getAllFuncTable())
    model->addFunction(std::shared_ptr<ir::FuncDefn>(p.second));
}

void Semant::processDeclarations(absyn::BlogProgram* prog) {
  absyn::TypDecl* td;
  absyn::DistinctDecl* dd;
  absyn::FuncDecl* fd;
  absyn::OriginDecl* od;
  for (auto st : prog->getAll()) {
    td = dynamic_cast<absyn::TypDecl*>(st);
    if (td != NULL) { // it is type declaration
      transTyDecl(td);
      continue;
    }
  }

  for (auto st : prog->getAll()) {
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

  for (auto st : prog->getAll()) {
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
  for (auto st : prog->getAll()) {
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
        "type name " + td->get().getValue() + " is defined multiple times");
  }
}

void Semant::transDistinctDecl(absyn::DistinctDecl* dd) {
  ir::NameTy const* nt = lookupNameTy(dd->getTyp().getValue());
  if (nt != NULL) {
    for (size_t i = 0; i < dd->size(); i++) {
      const std::string& name = dd->getVar(i).getValue();
      int k = dd->getLen(i);
      if (k < 1) {
        error(dd->line, dd->col, "Dimension of a distinct symbol must be positive!");
        continue;
      }
      if (lookupNameTy(name) != NULL) {
        error(dd->line, dd->col, "Distinct Symbol already defined as a Type");
        continue;
      }
      if (functory.getFunc(name, std::vector<std::shared_ptr<ir::VarDecl>>()) != NULL) {
        error(dd->line, dd->col, "Distinct Symbol already defined as a Function");
        continue;
      }
      if (k == 1) {
        if (tyFactory.getInstSymbol(arrayRefToString(name, 0)) != NULL
            || !tyFactory.addInstSymbol(nt, name)) {
          error(dd->line, dd->col, "Symbol " + name + " already defined");
        }
      } else {
        if (tyFactory.getInstSymbol(name) != NULL) {
          error(dd->line, dd->col, "Symbol " + name + " cannot be defined twice!");
          continue;
        }
        for (int j = 0; j < k; j++) {
          if (!tyFactory.addInstSymbol(nt, arrayRefToString(name, j))) {
            error(dd->line, dd->col,
                "Symbol " + name + "[" + std::to_string(j)
                    + "] already defined");
          }
        }
      }
    }
  }
}

void Semant::transFuncDecl(absyn::FuncDecl* fd) {
  const ir::Ty* rettyp = transTy(fd->getRetTyp());
  if (rettyp == NULL) return ;
  const std::string& name = fd->getFuncName().getValue();
  if (lookupNameTy(name) != NULL) {
    error(fd->line, fd->col, "Function name already defined as Type Name");
    return;
  }
  std::vector<std::shared_ptr<ir::VarDecl> > vds;
  for (size_t i = 0; i < fd->argSize(); i++) {
    vds.push_back(transVarDecl(fd->getArg(i)));
  }
  if (!functory.addFuncDefn(name, rettyp, vds, fd->isRandom())) {
    error(fd->line, fd->col,
        "function " + name + " with the same argument type already defined");
  }
}

void Semant::transOriginDecl(absyn::OriginDecl* od) {
  const ir::NameTy* retTyp = lookupNameTy(od->getTyp().getValue());
  const ir::NameTy* srcTy = lookupNameTy(od->getArg().getValue());
  if ((retTyp != NULL) && (srcTy != NULL)
      && (!tyFactory.addOriginAttr(srcTy, retTyp, od->getFunc().getValue()))) {
    error(od->line, od->col, "origin attribute already exist!");
  }
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::Expr *expr) {
  std::shared_ptr<ir::Expr> ret = nullptr;
  if (dynamic_cast<absyn::OpExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::OpExpr*) expr));
  if (dynamic_cast<absyn::FuncApp*>(expr) != NULL)
    return (ret = transExpr((absyn::FuncApp*) expr));
  if (dynamic_cast<absyn::Expr*>(expr) != NULL)
    return (ret = transExpr((absyn::DistrExpr*) expr));
  if (dynamic_cast<absyn::MapExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::MapExpr*) expr));
  if (dynamic_cast<absyn::CardinalityExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::CardinalityExpr*) expr));
  if (dynamic_cast<absyn::QuantExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::QuantExpr*) expr));
  if (dynamic_cast<absyn::VarRef*>(expr) != NULL)
    return (ret = transExpr((absyn::VarRef*) expr));
  if (dynamic_cast<absyn::SetExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::SetExpr*) expr));
  if (dynamic_cast<absyn::Literal*>(expr) != NULL)
    return (ret = transExpr((absyn::Literal*) expr));
  if (dynamic_cast<absyn::ArrayExpr*>(expr) != NULL)
    return (ret = transExpr((absyn::ArrayExpr*) expr));
  return ret;
}

std::shared_ptr<ir::IfThen> Semant::transIfThen(absyn::IfExpr* expr) {
  if (expr->getCond() == NULL || expr->getThen() == NULL) {
    error(expr->line, expr->col, "Error! Condition and Then cannot be empty for IF!");
    return nullptr;
  }
  std::shared_ptr<ir::IfThen> ptr(new ir::IfThen(transExpr(expr->getCond()), transClause(expr->getThen())));
  if (ptr->getThen()->getTyp() == NULL) {
    error(expr->line, expr->col, "Error! Then Clause cannot be NULL!");
    return ptr;
  }

  // Type Check
  ptr->setTyp(ptr->getThen()->getTyp());
  if (expr->getElse() != NULL)
    ptr->setElse(transExpr(expr->getElse()));
  else
    ptr->setElse(std::shared_ptr<ir::NullSymbol>(new ir::NullSymbol()));
  if (ptr->getElse()->getTyp() == NULL)
    ptr->getElse()->setTyp(ptr->getTyp());

  return ptr;
}

std::shared_ptr<ir::Branch> Semant::transBranch(absyn::DistrExpr* expr) {
  if (expr->size() != 2 || dynamic_cast<absyn::MapExpr*>(expr->get(0)) == NULL) {
    error(expr->line, expr->col, "Wrong Arguments Format for <TabularCPD>!");
    return nullptr;
  }
  std::shared_ptr<ir::Branch> ptr(new ir::Branch());
  /*
   * Note that We cannot directly apply trans MapExpr here!
   *   since arguments of MapExpr are all Expr
   *   while for Branch, arguments could be clauses
   */
  absyn::MapExpr* mp = (absyn::MapExpr*)(expr->get(0));
  // Similar Type Checking Process to transExpr(MapExpr)
  const ir::Ty* fromTy = NULL;
  const ir::Ty* toTy = NULL;
  for (size_t i = 0; i < mp->mapSize(); i++) {
    std::shared_ptr<ir::Expr> symbol = transExpr(mp->getFrom(i));
    std::shared_ptr<ir::Clause> clause = transClause(mp->getTo(i));
    if (dynamic_cast<ir::ConstSymbol*>(symbol.get()) == NULL) {
      error(expr->line, expr->col, "From Terms of the MapExpr in < TabularCPD > must be constant symbols!");
      return ptr;
    }
    if (symbol->getTyp() != NULL) {
      if (fromTy == NULL) fromTy = symbol->getTyp();
      else {
        if (fromTy != symbol->getTyp()) {
          error(mp->line, mp->col, "From Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    if (clause->getTyp() != NULL) {
      if (toTy == NULL) toTy = clause->getTyp();
      else {
        if (toTy != clause->getTyp()) {
          error(mp->line, mp->col, "To Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    // Add a new Branch
    ptr->addBranch(std::dynamic_pointer_cast<ir::ConstSymbol>(symbol), clause);
  }
  if (fromTy == NULL || toTy == NULL) {
    error(expr->line, expr->col, "From terms or To terms of MapExpr cannot be all NULL!");
    return ptr;
  }
  // Fill the type field of NullExpr
  for (auto c : ptr->getConds())
    if (c->getTyp() == NULL) c->setTyp(fromTy);
  for (auto b : ptr->getBranches())
    if (b->getTyp() == NULL) b->setTyp(toTy);
  ptr->setTyp(toTy);
  ptr->setVar(transExpr(expr->get(1)));
  if (ptr->getVar()->getTyp() != toTy) {
    error(expr->line, expr->col, "Argument type does not match!");
    return ptr;
  }
  return ptr;
}

std::shared_ptr<ir::Clause> Semant::transClause(absyn::Expr* expr) {
  if (dynamic_cast<absyn::IfExpr*>(expr) != NULL)
    return transIfThen((absyn::IfExpr*) expr);
  if (dynamic_cast<absyn::DistrExpr*>(expr) != NULL &&
    ((absyn::DistrExpr*)expr)->getDistrName().getValue() == "TabularCPD")
    return transBranch((absyn::DistrExpr*) expr);
  return transExpr(expr);
}

std::shared_ptr<ir::MapExpr> Semant::transExpr(absyn::MapExpr* expr) {
  // Type Checking
  std::shared_ptr<ir::MapExpr> ptr(new ir::MapExpr());
  const ir::Ty* fromTy = NULL;
  const ir::Ty* toTy = NULL;
  for (size_t i = 0; i < expr->mapSize(); i++) {
    ptr->addMap(transExpr(expr->getFrom(i)), transExpr(expr->getTo(i)));
    // Check and Update From Type
    if (ptr->getFrom(i)->getTyp() != NULL) {
      if (fromTy != NULL) fromTy = ptr->getFrom(i)->getTyp();
      else {
        if (fromTy != ptr->getFrom(i)->getTyp()) {
          error(expr->line, expr->col, "From Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    // Check and Update To Type
    if (ptr->getTo(i)->getTyp() != NULL) {
      if (toTy != NULL) toTy = ptr->getTo(i)->getTyp();
      else {
        if (toTy != ptr->getTo(i)->getTyp()) {
          error(expr->line, expr->col, "To Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
  }
  if (fromTy == NULL || toTy == NULL) {
    error(expr->line, expr->col, "There must be at least one non-null term in From Terms or To Terms!");
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

  return ptr;
}

ir::IRConstant OprExpr_convertOpConst(absyn::AbsynConstant op) {
  using absyn::AbsynConstant;
  using ir::IRConstant;
  switch (op) {
  case AbsynConstant::PLUS: return IRConstant::PLUS;
  case AbsynConstant::MINUS: return IRConstant::MINUS;
  case AbsynConstant::MUL: return IRConstant::MUL;
  case AbsynConstant::DIV: return IRConstant::DIV;
  case AbsynConstant::MOD: return IRConstant::MOD;
  case AbsynConstant::POWER: return IRConstant::POWER;
  case AbsynConstant::EQ: return IRConstant::EQ;
  case AbsynConstant::NEQ: return IRConstant::NEQ;
  case AbsynConstant::LT: return IRConstant::LT;
  case AbsynConstant::GT: return IRConstant::GT;
  case AbsynConstant::LE: return IRConstant::GE;
  case AbsynConstant::AND: return IRConstant::AND;
  case AbsynConstant::OR: return IRConstant::OR;
  case AbsynConstant::NOT: return IRConstant::NOT;
  case AbsynConstant::IMPLY: return IRConstant::IMPLY;
  case AbsynConstant::SUB: return IRConstant::SUB;
  default: return IRConstant::NA;
  }
}

bool OprExpr_isPrimitive(const ir::Ty* t) {
  return t->getTyp() == ir::IRConstant::INT
         || t->getTyp() == ir::IRConstant::DOUBLE
         || t->getTyp() == ir::IRConstant::BOOL
         || t->getTyp() == ir::IRConstant::STRING;
}

bool OprExpr_isNumerical(const ir::Ty* t) {
  return t->getTyp() == ir::IRConstant::INT
    || t->getTyp() == ir::IRConstant::DOUBLE;
}

const ir::Ty* Semant::OprExpr_checkType(ir::IRConstant op, const std::vector<std::shared_ptr<ir::Expr>>& arg) {
  using ir::IRConstant;
  using ir::IRConstString;
  switch (op) {
  // Bool
  // Unary Operator
  case IRConstant::NOT:
    if (arg[0]->getTyp() != lookupTy(IRConstString::BOOL)) return NULL;
    return arg[0]->getTyp();
  // Logical Operator
  case IRConstant::AND:
  case IRConstant::OR:
  case IRConstant::IMPLY:
    if (arg[0]->getTyp() != lookupTy(IRConstString::BOOL)
      || arg[1]->getTyp() != lookupTy(IRConstString::BOOL)) return NULL;
    return arg[0]->getTyp();
  case IRConstant::LT:
  case IRConstant::GT:
  case IRConstant::LE:
  case IRConstant::GE:
    if (!OprExpr_isPrimitive(arg[0]->getTyp()) || !OprExpr_isPrimitive(arg[1]->getTyp()))
      return NULL;
    return lookupTy(IRConstString::BOOL);
  case IRConstant::NEQ:
  case IRConstant::EQ:
    // Check Null Type
    if (arg[0]->getTyp() == NULL && arg[1]->getTyp() != NULL)
      arg[0]->setTyp(arg[1]->getTyp());
    if (arg[0]->getTyp() != NULL && arg[1]->getTyp() == NULL)
      arg[1]->setTyp(arg[0]->getTyp());
    if (arg[0]->getTyp() != arg[1]->getTyp()) return NULL;
    return lookupTy(IRConstString::BOOL);
  // Numerical Operator
  case IRConstant::MOD:
    if (arg[0]->getTyp() != arg[1]->getTyp() || arg[0]->getTyp() != lookupTy(IRConstString::INT))
      return NULL;
    return arg[0]->getTyp();
  case IRConstant::PLUS:
    if (arg[0]->getTyp() == arg[1]->getTyp() && arg[0]->getTyp() == lookupTy(IRConstString::STRING))
      return arg[0]->getTyp();
  case IRConstant::MINUS:
  case IRConstant::MUL:
  case IRConstant::DIV:
  case IRConstant::POWER:
    if (arg[0]->getTyp() != arg[1]->getTyp() || !OprExpr_isNumerical(arg[0]->getTyp()))
      return NULL;
    if (op == IRConstant::POWER)
      return lookupTy(IRConstString::DOUBLE);
    return arg[0]->getTyp();

  // Address Operator
  case IRConstant::SUB: 
    {
      if (arg[1]->getTyp() != tyFactory.getTy(ir::IRConstString::INT)
          || (dynamic_cast<const ir::ArrayTy*>(arg[0]->getTyp()) == NULL))
        return NULL;
      const ir::ArrayTy* arr = (const ir::ArrayTy*)(arg[0]->getTyp());
      if (arr->getDim() == 1)
        return arr->getBase();
      else
        return 
          tyFactory.getUpdateTy(new ir::ArrayTy(arr->getBase(), arr->getDim() - 1));
    }
    break;
  default: return NULL;
  }
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::OpExpr* expr) {
  std::shared_ptr<ir::OprExpr> ret(new ir::OprExpr(OprExpr_convertOpConst(expr->getOp())));
  if (ret->getOp() == ir::IRConstant::NA
      || (ret->getOp() == ir::IRConstant::NOT && (expr->getLeft() != NULL || expr->getRight() == NULL))
      || (ret->getOp() != ir::IRConstant::NOT && (expr->getLeft() == NULL || expr->getRight() == NULL))) {
    error(expr->line, expr->col, "Invalid/Incomplete Operator!");
    return nullptr;
  }

  // Special Case: 
  //         Replace OprExpr with a InstSymbolRef
  if (ret->getOp() == ir::IRConstant::SUB
    && (dynamic_cast<absyn::VarRef*>(expr->getLeft())) != NULL
    && (dynamic_cast<absyn::IntLiteral*>(expr->getRight())) != NULL) {
    std::string var = ((absyn::VarRef*)(expr->getLeft()))->getVar().getValue();
    int k = ((absyn::IntLiteral*)(expr->getRight()))->getValue();
    auto sym = tyFactory.getInstSymbol(arrayRefToString(var, k));
    if (sym != NULL && local_var.count(var) == 0) {
      auto ref = std::shared_ptr<ir::InstSymbolRef>(new ir::InstSymbolRef(sym));
      ref->setTyp(lookupNameTy(sym->getRefer()->getName()));
      return ref;
    }
  }

  // Unary Operator
  if (ret->getOp() == ir::IRConstant::NOT)  {
      ret->addArg(transExpr(expr->getRight()));
    if (ret->get(0) == nullptr) return nullptr;
  } 
  else {
    ret->addArg(transExpr(expr->getLeft()));
    ret->addArg(transExpr(expr->getRight()));
    if (ret->get(0) == nullptr || ret->get(1) == nullptr) return nullptr;
  }
  // Type Checking
  ret->setTyp(OprExpr_checkType(ret->getOp(), ret->getArgs()));
  if (ret->getTyp() == NULL) {
    error(expr->line, expr->col, "Error Type Matching for OprExpr!");
    return nullptr;
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
    if (args.back() != nullptr)
      decl.push_back(
        std::shared_ptr<ir::VarDecl>
          (new ir::VarDecl(args.back()->getTyp(), "")));
  }

  if (decl.size() == 1 && (dynamic_cast<const ir::NameTy*>(decl[0]->getTyp()) != NULL)) {
    auto att = tyFactory.getOriginAttr((const ir::NameTy*)decl[0]->getTyp(), func);
    if (att != NULL) {
      std::shared_ptr<ir::OriginRefer> ptr(new ir::OriginRefer(att, args[0]));
      // type checking
      ptr->setTyp(att->getTyp());
      return ptr;
    }
  }

  std::shared_ptr<ir::FunctionCall> ptr(
    new ir::FunctionCall(functory.getFunc(func, decl)));
  
  if (ptr->getRefer() == NULL) {
    error(expr->line, expr->col, "Error on Function Call! No Such Function.");
    return ptr;
  }

  // Type Checking
  ptr->setTyp(ptr->getRefer()->getRetTyp());
  return ptr;
}

std::shared_ptr<ir::CardExpr> Semant::transExpr(absyn::CardinalityExpr* expr) {
  if (expr->size() != 1) {
    error(expr->line, expr->col, "Invalid Cardinality Expression!");
    return nullptr;
  }
  std::shared_ptr<ir::Expr> b = transExpr(expr->get(0));
  std::shared_ptr<ir::SetExpr> st = std::dynamic_pointer_cast<ir::SetExpr>(b);
  if (st == nullptr) {
    error(expr->line, expr->col, "Invalid Cardinality Expression!");
    return nullptr;
  }
  std::shared_ptr<ir::CardExpr> cd(new ir::CardExpr());
  cd->setBody(st);
  cd->setTyp(lookupTy(ir::IRConstString::INT));
  return cd;
}

std::shared_ptr<ir::QuantForm> Semant::transExpr(absyn::QuantExpr* expr) {
  //TODO
  return nullptr;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::VarRef* expr) {
  // 3 cases: local variable, voidfunccall, const symbol
  std::string var = expr->getVar().getValue();
  if (local_var.count(var) != 0) {
    // Local Variable
    std::shared_ptr<ir::VarRefer> ret(new ir::VarRefer(local_var[var].top()));
    ret->setTyp(ret->getRefer()->getTyp());
    return ret;
  }
  auto func = functory.getFunc(var, std::vector<std::shared_ptr<ir::VarDecl> >());
  if (func != NULL) {
    // Void Function Call
    std::shared_ptr<ir::VoidFuncCall> ret(new ir::VoidFuncCall(func));
    ret->setTyp(func->getRetTyp());
    return ret;
  }
  auto sym = tyFactory.getInstSymbol(var);
  if (sym != NULL) {
    // Const Symbol
    std::shared_ptr<ir::InstSymbolRef>ret(new ir::InstSymbolRef(sym));
    ret->setTyp(lookupNameTy(sym->getRefer()->getName()));
    return ret;
  }
  error(expr->line, expr->col, "Illegal Symbol Reference!");
  return nullptr;
}

std::shared_ptr<ir::SetExpr> Semant::transExpr(absyn::SetExpr* expr) {
  //TODO
  return nullptr;
}

std::shared_ptr<ir::ListSet> Semant::transExpr(absyn::ListSet* expr) {
  //TODO
  return nullptr;
}

std::shared_ptr<ir::CondSet> Semant::transExpr(absyn::CondSet* expr) {
  //TODO
  return nullptr;
}

std::shared_ptr<ir::Distribution> Semant::transExpr(absyn::DistrExpr* expr) {
  // TODO: add type checking for predecl distribution
  std::string name = expr->getDistrName().getValue();
  const predecl::PreDeclDistr* distr = predeclFactory.getDistr(name);

  if (distr == NULL) {
    // TODO: to allow costumized distribution
    //warning(expr->line, expr->col, "<" + name + "> costumized distribution assumed! No type checking will be performed!");
    error(expr->line, expr->col, "distribution not defined");
    return std::make_shared<ir::Distribution>(name);
  }

  std::vector<std::shared_ptr<ir::Expr>> args;
  for (size_t i = 0; i < expr->size(); ++i) {
    args.push_back(transExpr(expr->get(i)));
    if (args.back() == nullptr) args.pop_back();
  }

  std::shared_ptr<ir::Distribution> ret = distr->getNew(args, &tyFactory);
  if (ret == nullptr) {
    error(expr->line, expr->col, "Type Checking failed for <" + name + "> distribution!");
    return std::make_shared<ir::Distribution>(name, distr);
  }
  return ret;
}

std::shared_ptr<ir::ConstSymbol> Semant::transExpr(absyn::Literal* expr) {
  // int, double, string, boolean, null
  if (dynamic_cast<absyn::NullLiteral*>(expr) != NULL) {
    // TODO: type of NULL Symbol should be assigned later!
    //       NULL will appear in MAP, OpExpr, If, Branch, FunctionDefn
    return std::shared_ptr<ir::NullSymbol>(new ir::NullSymbol());
  }
  if (dynamic_cast<absyn::IntLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::IntLiteral> ret
      (new ir::IntLiteral(((absyn::IntLiteral*)expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::INT));
    return ret;
  }
  if (dynamic_cast<absyn::DoubleLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::DoubleLiteral> ret
      (new ir::DoubleLiteral(((absyn::DoubleLiteral*)expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::DOUBLE));
    return ret;
  }
  if (dynamic_cast<absyn::BoolLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::BoolLiteral> ret
      (new ir::BoolLiteral(((absyn::BoolLiteral*)expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::BOOL));
    return ret;
  }
  if (dynamic_cast<absyn::StringLiteral*>(expr) != NULL) {
    std::shared_ptr<ir::StringLiteral> ret
      (new ir::StringLiteral(((absyn::StringLiteral*)expr)->getValue()));
    ret->setTyp(lookupTy(ir::IRConstString::STRING));
    return ret;
  }
  error(expr->line, expr->col, "Illegal Literal!");
  return nullptr;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::ArrayExpr* expr) {
  std::shared_ptr<ir::ArrayExpr> ret = std::make_shared<ir::ArrayExpr>();
  for (size_t i = 0; i < expr->size(); ++i) {
    auto ptr = transExpr(expr->get(i));
    if (ptr != nullptr)
      ret->addArg(ptr);
  }
  const ir::Ty* base = NULL;
  for (size_t i = 0; i < ret->argSize(); ++i)
    if (ret->get(i)->getTyp() != NULL)
       base = ret->get(i)->getTyp();
  if (base == NULL || base->getTyp() != ir::IRConstant::ARRAY || ((const ir::ArrayTy*)base)->getDim() != expr->getDim()-1) {
    error(expr->line, expr->col, "Illegal Array Expr");
  }
  else {
    for (size_t i = 0; i < ret->argSize(); ++i) {
      const ir::Ty* t = ret->get(i)->getTyp();
      if (t == NULL)
        ret->get(i)->setTyp(base);
      else
      if (t != base) {
        error(expr->line, expr->col, "Illegal Array Expr");
        break;
      }
    }
    ret->setTyp(tyFactory.getUpdateTy(new ir::ArrayTy(base, expr->getDim())));
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
  ir::FuncDefn * fun = functory.getFunc(name, vds);
  if (fun != NULL) {
    // Add Local Variables
    for (auto v : vds)
      local_var[v->getVar()].push(v.get());

    fun->setBody( transClause(fd->getExpr()) );

    for (auto v : vds) {
      auto it = local_var.find(v->getVar());
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
    error(nd->line, nd->col, "Invalid Number Statement! No corresponding type definition!");
    return ;
  }
  ir::NumberStmt* numst = new ir::NumberStmt(ty->getRefer());
  std::set<std::string> defined_var, defined_att;
  bool success = true;
  for (size_t k = 0; k < nd->argSize(); k++) {
    std::string var = nd->getArgVar(k).getValue();
    std::string att = nd->getArgOrigin(k).getValue();
    if (defined_var.count(var) != 0) {
      error(nd->line, nd->col, std::to_string(k+1) + "th arg var is already defined in this number statement!");
      success = false;
    }
    if (tyFactory.getTy(var) != NULL) {
      error(nd->line, nd->col, std::to_string(k + 1) + "th arg var cannot be a type!");
      success = false;
    }
    defined_var.insert(var);
    if (defined_att.count(att) != 0) {
      error(nd->line, nd->col, std::to_string(k + 1) + "th origin field is already declared in this number statement!");
      success = false;
    }
    const ir::OriginAttr* o = tyFactory.getOriginAttr(ty, att);
    if (o == NULL) {
      error(nd->line, nd->col, std::to_string(k + 1) + "th origin field is not declared in the program!");
      success = false;
    }
    defined_att.insert(att);
    if (!success) break;

    numst->addArg(o, var);
  }
  if (!success) {
    delete numst;
    return ;
  }

  // Add Local Variable
  for (auto v : numst->getAllVars())
    local_var[v->getVar()].push(v.get());
  numst->setExpr(transClause(nd->getExpr()));
  for (auto v : numst->getAllVars()) {
    auto it = local_var.find(v->getVar());
    it->second.pop();
    if (it->second.empty()) local_var.erase(it);
  }
  tyFactory.addNumberStmt(numst);
}

void Semant::transEvidence(absyn::Evidence* ne) {
  auto lhs = transExpr(ne->getLeft());
  auto rhs = transExpr(ne->getRight());
  // type checking for equality
  if (lhs->getTyp() == NULL && rhs->getTyp() != NULL)
    lhs->setTyp(rhs->getTyp());
  if (lhs->getTyp() != NULL && rhs->getTyp() == NULL)
    rhs->setTyp(lhs->getTyp());
  if (lhs->getTyp() == NULL) // Both are NULL! always hold!
    return ;
  if (lhs->getTyp() != rhs->getTyp()) {
    error(ne->line, ne->col, "Types not match for equality!");
    return ;
  }
  // Format Checking
  //     we assume that :
  //         left side  : function call
  //         right side : const symbol
  if ((std::dynamic_pointer_cast<ir::ConstSymbol>(rhs)) == nullptr
    || (std::dynamic_pointer_cast<ir::FunctionCall>(lhs)) == nullptr) {
    error(ne->line, ne->col, "Evidence format not correct! We assume < FunctionCall = ConstSymbol >!");
    return ; // TODO: build internal function to avoid this
  }
  model->addEvidence(std::shared_ptr<ir::Evidence>
    (new ir::Evidence(std::dynamic_pointer_cast<ir::FunctionCall>(lhs),
     std::dynamic_pointer_cast<ir::ConstSymbol>(rhs))));
}

void Semant::transQuery(absyn::Query* nq) {
  std::shared_ptr<ir::FunctionCall> ptr
    (std::dynamic_pointer_cast<ir::FunctionCall>(transExpr(nq->getExpr())));
  if (ptr == nullptr) {
    //TODO: build a internal Void Function Call to represent this expr
    error(nq->line, nq->col, "Currently we only accept function call in the query statement!");
    return ;
  }
  std::shared_ptr<ir::Query> q(new ir::Query(ptr));
  model->addQuery(q);
}

const ir::Ty* Semant::transTy(const absyn::Ty& typ) {
  int dim = typ.getDim();
  const ir::Ty* ty = tyFactory.getTy(typ.getTyp().getValue());
  if (ty == NULL) {
    error(typ.line, typ.col, "Type " + typ.getTyp().getValue() + " not found");
    return NULL;
  }
  if (dim == 0) {
    return ty;
  } else {
    return tyFactory.getUpdateTy(new ir::ArrayTy(ty, dim));
  }
}

const std::shared_ptr<ir::VarDecl> Semant::transVarDecl(const absyn::VarDecl & vd) {
  const ir::Ty* ty = transTy(vd.getTyp());
  return std::make_shared<ir::VarDecl>(ty, vd.getVar().getValue());
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
  return tyFactory.getTy(name);
}

std::string Semant::arrayRefToString(const std::string & name, int idx) {
  return name + "[" + std::to_string(idx) + "]";
}

}
} /* namespace swift */
