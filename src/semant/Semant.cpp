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
  model = new ir::BlogModel();
  isResultUsed = false;
}

Semant::~Semant() {
  // model should be externally deleted
  // if the model is not used through getModel(), then delete the model
  if (!isResultUsed)
    delete model;
}

ir::BlogModel* Semant::getModel() {
  // Note: IMPORTANT
  // Since model uses shared_ptr to store type domains
  // after deleting model, all type domains will be deleted!
  // and they should not be deleted again from tyFactory!
  isResultUsed = true;
  return model;
}

void Semant::process(absyn::BlogProgram* prog) {
  processDeclarations(prog);
  processBodies(prog);
  // add TypeDomains to model
  for (auto p : tyFactory.getAllTyTable())
    if (p.second->getTyp() == ir::IRConstant::NAMETY)
      model->addTypeDomain(
          std::shared_ptr<ir::TypeDomain>(
              ((const ir::NameTy*) p.second)->getRefer()));
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

  // Note: We assume that function name cannot be the same as type name
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

  // Note: We assume that distinct name cannot be the same as function name or type name
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
  if (!functory.addFuncDefn(name, rettyp, vds, fd->isRandom())) {
    error(fd->line, fd->col,
        "function < " + name
            + " > with the same argument type already defined");
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
  if (dynamic_cast<absyn::DistrExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::DistrExpr*) expr));
  if (dynamic_cast<absyn::MapExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::MapExpr*) expr));
  if (dynamic_cast<absyn::CardinalityExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::CardinalityExpr*) expr));
  if (dynamic_cast<absyn::QuantExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::QuantExpr*) expr));
  if (dynamic_cast<absyn::VarRef*>(expr) != nullptr)
    return (ret = transExpr((absyn::VarRef*) expr));
  if (dynamic_cast<absyn::SetExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::SetExpr*) expr));
  if (dynamic_cast<absyn::Literal*>(expr) != nullptr)
    return (ret = transExpr((absyn::Literal*) expr));
  if (dynamic_cast<absyn::ArrayExpr*>(expr) != nullptr)
    return (ret = transExpr((absyn::ArrayExpr*) expr));
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
  if (ptr->getThen()->getTyp() == NULL) {
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

  return ptr;
}

std::shared_ptr<ir::Branch> Semant::transBranch(absyn::DistrExpr* expr) {
  std::shared_ptr<ir::Branch> ptr(new ir::Branch());
  if (expr->size() != 2 || dynamic_cast<absyn::MapExpr*>(expr->get(0)) == NULL) {
    error(expr->line, expr->col, "Arguments Format Error for < TabularCPD >!");
    return ptr;
  }
  /*
   * Note that We cannot directly apply trans MapExpr here!
   *   since arguments of MapExpr are all Expr
   *   while for Branch, arguments could be clauses
   */
  absyn::MapExpr* mp = (absyn::MapExpr*) (expr->get(0));
  // Similar Type Checking Process to transExpr(MapExpr)
  const ir::Ty* fromTy = NULL;
  const ir::Ty* toTy = NULL;
  for (size_t i = 0; i < mp->mapSize(); i++) {
    std::shared_ptr<ir::Expr> symbol = transExpr(mp->getFrom(i));
    std::shared_ptr<ir::Clause> clause = transClause(mp->getTo(i));
    if (dynamic_cast<ir::ConstSymbol*>(symbol.get()) == NULL) {
      error(expr->line, expr->col,
          "From Terms of the MapExpr in < TabularCPD > must be constant symbols!");
      return ptr;
    }
    if (symbol->getTyp() != NULL) {
      if (fromTy == NULL)
        fromTy = symbol->getTyp();
      else {
        if (fromTy != symbol->getTyp()) {
          error(mp->line, mp->col,
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
          error(mp->line, mp->col,
              "To Terms of MapExpr must have the same type!");
          return ptr;
        }
      }
    }
    // Add a new Branch
    ptr->addBranch(std::dynamic_pointer_cast<ir::ConstSymbol>(symbol), clause);
  }
  if (fromTy == NULL) {
    error(expr->line, expr->col, "Type of From terms cannot be confirmed!");
    return ptr;
  }
  if (toTy == NULL) {
    error(expr->line, expr->col, "Type of To terms cannot be confirmed!");
    return ptr;
  }
  // Fill the type field of NullExpr
  for (auto c : ptr->getConds())
    if (c->getTyp() == NULL)
      c->setTyp(fromTy);
  for (auto b : ptr->getBranches())
    if (b->getTyp() == NULL)
      b->setTyp(toTy);
  ptr->setTyp(toTy);
  ptr->setVar(transExpr(expr->get(1)));
  if (ptr->getVar()->getTyp() != fromTy) {
    error(expr->line, expr->col, "Argument types do not match!");
    return ptr;
  }
  return ptr;
}

std::shared_ptr<ir::Clause> Semant::transClause(absyn::Expr* expr) {
  if (dynamic_cast<absyn::IfExpr*>(expr) != NULL)
    return transIfThen((absyn::IfExpr*) expr);
  if (dynamic_cast<absyn::DistrExpr*>(expr) != NULL
      && ((absyn::DistrExpr*) expr)->getDistrName().getValue() == "TabularCPD")
    return transBranch((absyn::DistrExpr*) expr);
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
          || t->getTyp() == ir::IRConstant::STRING);
}

bool OprExpr_isNumerical(const ir::Ty* t) {
  return (t != NULL)
      && (t->getTyp() == ir::IRConstant::INT
          || t->getTyp() == ir::IRConstant::DOUBLE);
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
    if (arg[0]->getTyp() != arg[1]->getTyp()
        || arg[0]->getTyp() != lookupTy(IRConstString::INT))
      return NULL;
    return arg[0]->getTyp();
  case IRConstant::PLUS:
    // Special Case for String Concatenation
    if (arg[0]->getTyp() == arg[1]->getTyp()
        && arg[0]->getTyp() == lookupTy(IRConstString::STRING))
      return arg[0]->getTyp();
  case IRConstant::MINUS:
  case IRConstant::MUL:
  case IRConstant::DIV:
  case IRConstant::POWER:
    if (arg[0]->getTyp() != arg[1]->getTyp()
        || !OprExpr_isNumerical(arg[0]->getTyp()))
      return NULL;
    if (op == IRConstant::POWER)
      return lookupTy(IRConstString::DOUBLE);
    return arg[0]->getTyp();

    // Address Operator
  case IRConstant::SUB: {
    if (arg[1]->getTyp() != tyFactory.getTy(ir::IRConstString::INT)
        || (dynamic_cast<const ir::ArrayTy*>(arg[0]->getTyp()) == NULL))
      return NULL;
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
  auto ret = std::make_shared<ir::OprExpr>(
      OprExpr_convertOpConst(expr->getOp()));
  if (ret->getOp() == ir::IRConstant::NA
      || (ret->getOp() == ir::IRConstant::NOT
          && (expr->getLeft() != NULL || expr->getRight() == NULL))
      || (ret->getOp() != ir::IRConstant::NOT
          && (expr->getLeft() == NULL || expr->getRight() == NULL))) {
    error(expr->line, expr->col, "Invalid/Incomplete Operator for OprExpr!");
    return ret;
  }

  // Special Case: 
  //         Replace OprExpr with a InstSymbolRef
  if (ret->getOp()
      == ir::IRConstant::SUB && (dynamic_cast<absyn::VarRef*>(expr->getLeft())) != NULL
      && (dynamic_cast<absyn::IntLiteral*>(expr->getRight())) != NULL) {
    std::string var = ((absyn::VarRef*) (expr->getLeft()))->getVar().getValue();
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
  } else {
    ret->addArg(transExpr(expr->getLeft()));
    ret->addArg(transExpr(expr->getRight()));
  }
  // Type Checking
  ret->setTyp(OprExpr_checkType(ret->getOp(), ret->getArgs()));
  if (ret->getTyp() == NULL) {
    error(expr->line, expr->col, "Error Type Matching for OprExpr!");
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

  // Special Case for Origin Function
  if (decl.size() == 1
      && (dynamic_cast<const ir::NameTy*>(decl[0]->getTyp()) != NULL)) {
    auto att = tyFactory.getOriginAttr((const ir::NameTy*) decl[0]->getTyp(),
        func);
    if (att != NULL) {
      auto ptr = std::make_shared<ir::OriginRefer>(att, args[0]);
      // type checking
      ptr->setTyp(att->getTyp());
      return ptr;
    }
  }

  auto ptr = std::make_shared<ir::FunctionCall>(functory.getFunc(func, decl));

  if (ptr->getRefer() == NULL) {
    error(expr->line, expr->col,
        "Error on Function Call! No Such Function < " + func + " >.");
    return ptr;
  }

  // Type Checking
  ptr->setTyp(ptr->getRefer()->getRetTyp());
  ptr->setArgs(args);
  return ptr;
}

std::shared_ptr<ir::CardExpr> Semant::transExpr(absyn::CardinalityExpr* expr) {
  std::shared_ptr<ir::CardExpr> cd(new ir::CardExpr());
  cd->setTyp(lookupTy(ir::IRConstString::INT));
  if (expr->size() != 1) {
    error(expr->line, expr->col, "Invalid Cardinality Expression!");
    return cd;
  }
  std::shared_ptr<ir::Expr> b = transExpr(expr->get(0));
  std::shared_ptr<ir::SetExpr> st = std::dynamic_pointer_cast<ir::SetExpr>(b);
  if (st == nullptr) {
    error(expr->line, expr->col,
        "Invalid Cardinality Expression! Body must be a SetExpr!");
    return cd;
  }
  cd->setBody(st);
  return cd;
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

  ptr->addArg(transExpr(expr->getCond()));
  if (ptr->get(0)->getTyp() != lookupTy(ir::IRConstString::BOOL)) {
    error(expr->line, expr->col,
        "Condition in Quant Form must return boolean value!");
  }

  // Remove Local Variable
  auto it = local_var.find(ptr->getVar()->getVarName());
  it->second.pop();
  if (it->second.empty())
    local_var.erase(it);
  return ptr;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::VarRef* expr) {
  // 3 cases: local variable, voidfunccall, const symbol
  std::string var = expr->getVar().getValue();
  if (local_var.count(var) != 0) {
    // Local Variable
    std::shared_ptr<ir::VarRefer> ret = std::make_shared<ir::VarRefer>(
        local_var[var].top());
    ret->setTyp(ret->getRefer()->getTyp());
    return ret;
  }
  auto func = functory.getFunc(var,
      std::vector<std::shared_ptr<ir::VarDecl> >());
  if (func != NULL) {
    // Void Function Call
    // TODO: To Change to Void Function Call
    //std::shared_ptr<ir::VoidFuncCall> ret(new ir::VoidFuncCall(func));
    auto ret = std::make_shared<ir::FunctionCall>(func);
    ret->setTyp(func->getRetTyp());
    return ret;
  }
  auto sym = tyFactory.getInstSymbol(var);
  if (sym != NULL) {
    // Const Symbol
    std::shared_ptr<ir::InstSymbolRef> ret(new ir::InstSymbolRef(sym));
    ret->setTyp(lookupNameTy(sym->getRefer()->getName()));
    return ret;
  }
  error(expr->line, expr->col, "Illegal Symbol Reference of < " + var + " >!");
  return std::make_shared<ir::Expr>();
}

std::shared_ptr<ir::SetExpr> Semant::transExpr(absyn::SetExpr* expr) {
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
  auto ptr = std::make_shared<ir::CondSet>(var, e);

  if (e != nullptr && e->getTyp() != tyFactory.getTy(ir::IRConstString::BOOL)) {
    error(expr->line, expr->col,
        "Condition of the set must return Boolean Value!");
  }

  ptr->setTyp(tyFactory.getUpdateTy(new ir::SetTy(var->getTyp())));
  return ptr;
}

std::shared_ptr<ir::Distribution> Semant::transExpr(absyn::DistrExpr* expr) {
  // TODO: add type checking for predecl distribution
  std::string name = expr->getDistrName().getValue();
  const predecl::PreDeclDistr* distr = predeclFactory.getDistr(name);

  if (distr == NULL) {
    // TODO: to allow costumized distribution
    //warning(expr->line, expr->col, "<" + name + "> costumized distribution assumed! No type checking will be performed!");
    error(expr->line, expr->col, "distribution < " + name + " > not defined");
    return std::make_shared<ir::Distribution>(name);
  }

  std::vector<std::shared_ptr<ir::Expr>> args;
  for (size_t i = 0; i < expr->size(); ++i) {
    auto ag = transExpr(expr->get(i));
    if (ag)
      args.push_back(ag);
  }

  std::shared_ptr<ir::Distribution> ret = distr->getNew(args, &tyFactory);
  if (ret == nullptr) {
    error(expr->line, expr->col,
        "Type Checking failed for <" + name + "> distribution!");
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
  error(expr->line, expr->col, "Illegal Literal!");
  return std::make_shared<ir::NullSymbol>();
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::ArrayExpr* expr) {
  std::shared_ptr<ir::ArrayExpr> ret = std::make_shared<ir::ArrayExpr>();
  for (size_t i = 0; i < expr->size(); ++i) {
    ret->addArg(transExpr(expr->get(i)));
  }
  const ir::Ty* base = NULL;
  for (size_t i = 0; i < ret->argSize(); ++i)
    if (ret->get(i)->getTyp() != NULL)
      base = ret->get(i)->getTyp();
  if (base == NULL
      || (base->getTyp() == ir::IRConstant::ARRAY
          && ((const ir::ArrayTy*) base)->getDim() != expr->getDim() - 1)
      || (base->getTyp() != ir::IRConstant::ARRAY && expr->getDim() != 1)) {
    error(expr->line, expr->col, "Illegal Array Expr");
  } else {
    for (size_t i = 0; i < ret->argSize(); ++i) {
      const ir::Ty* t = ret->get(i)->getTyp();
      if (t == NULL)
        ret->get(i)->setTyp(base);
      else if (t != base) {
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
  std::shared_ptr<ir::FuncDefn> fun = functory.getFunc(name, vds);
  if (fun != NULL) {
    // Add Local Variables
    for (auto v : fun->getArgs())
      local_var[v->getVarName()].push(v);

    fun->setBody(transClause(fd->getExpr()));
    if (fun->getBody()->getTyp() == NULL)
      fun->getBody()->setTyp(rettyp);

    // if it is random, then need to add the link from arg --> thisfunction
    if (fun->isRand()) {
      for (auto arg : fun->getArgs()) {
        auto nty = dynamic_cast<const ir::NameTy*>(arg->getTyp());
        if (nty)
          nty->getRefer()->addReferFun(std::shared_ptr<ir::FuncDefn>(fun));
      }
    }

    // Remove Local Variables
    for (auto v : fun->getArgs()) {
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
  for (auto v : numst->getAllVars())
    local_var[v->getVarName()].push(v);
  numst->setBody(transClause(nd->getExpr()));

  for (auto v : numst->getAllVars()) {
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
  // type checking for equality
  if (lhs->getTyp() == NULL && rhs->getTyp() != NULL)
    lhs->setTyp(rhs->getTyp());
  if (lhs->getTyp() != NULL && rhs->getTyp() == NULL)
    rhs->setTyp(lhs->getTyp());
  if (lhs->getTyp() == NULL) // Both are NULL! always hold!
    return;
  if (lhs->getTyp() != rhs->getTyp()) {
    error(ne->line, ne->col, "Types not match for equality in Evidence!");
    return;
  }
  // Format Checking
  //     we assume that :
  //         left side  : function call | #TypeName
  //         right side : const symbol
  if ((std::dynamic_pointer_cast<ir::ConstSymbol>(rhs)) == nullptr
      || ((std::dynamic_pointer_cast<ir::FunctionCall>(lhs) == nullptr)
          && !isCardAll(lhs))) {
    error(ne->line, ne->col,
        "Evidence format not correct! We assume < FunctionCall | #TypeName = ConstSymbol >!");
    return; // TODO: build internal function to avoid this
  }
  model->addEvidence(
      std::make_shared<ir::Evidence>(std::dynamic_pointer_cast<ir::Expr>(lhs),
          std::dynamic_pointer_cast<ir::ConstSymbol>(rhs)));
}

void Semant::transQuery(absyn::Query* nq) {
  auto ptr = transExpr(nq->getExpr());
  if (!isCardAll(ptr)
      && (std::dynamic_pointer_cast<ir::FunctionCall>(ptr) == nullptr)) {
    //TODO: build a internal Void Function Call to represent this expr
    error(nq->line, nq->col,
        "Currently we only accept [ Function Call | #TypeName ] in the query statement!");
    return;
  }
  model->addQuery(std::make_shared<ir::Query>(ptr));
}

const ir::Ty* Semant::transTy(const absyn::Ty& typ) {
  int dim = typ.getDim();
  const ir::Ty* ty = tyFactory.getTy(typ.getTyp().getValue());
  if (ty == NULL) {
    error(typ.line, typ.col,
        "Type < " + typ.getTyp().getValue() + " > not found");
    return NULL;
  }
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
  return st->getCond() == nullptr;
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

bool Semant::Okay() {
  return errorMsg.Okay();
}

}
} /* namespace swift */
