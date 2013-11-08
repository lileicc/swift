/*
 * Semant.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#include "Semant.h"

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
  return model;
}

void Semant::process(absyn::BlogProgram* prog) {
  processDeclarations(prog);
  processBodies(prog);
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

    dd = dynamic_cast<absyn::DistinctDecl*>(st);
    if (dd != NULL) { // it is distinct declaration
      transDistinctDecl(dd);
      continue;
    }

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
}

void Semant::processBodies(absyn::BlogProgram* prog) {
  absyn::FuncDecl* fd;
  absyn::NumStDecl* nd;
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
    //TODO evidence
    //TODO query

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
      if (k == 1) {
        if (!tyFactory.addInstSymbol(nt, name)) {
          error(dd->line, dd->col, "Symbol " + name + " already defined");
        }
      } else {
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
  const std::string& name = fd->getFuncName().getValue();
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
  std::shared_ptr<ir::Expr> ret;
  if (dynamic_cast<absyn::OpExpr*>(expr) != NULL)
    return (ret=transExpr((absyn::OpExpr*) expr));
  return ret;
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
  // TODO:
  case IRConstant::SUB:
    return NULL;
    break;
  default: return NULL;
  }
}

std::shared_ptr<ir::OprExpr> Semant::transExpr(absyn::OpExpr* expr) {
  std::shared_ptr<ir::OprExpr> ret(new ir::OprExpr(OprExpr_convertOpConst(expr->getOp())));
  if (ret->getOp() == ir::IRConstant::NA) {
    error(expr->line, expr->col, "Invalid Operator!");
    return nullptr;
  }
  // Unary Operator
  if (ret->getOp() == ir::IRConstant::NOT)  {
    if (expr->getLeft() != NULL || expr->getRight() == NULL) {
      error(expr->line, expr->col, "Invalid Unaray Operator Expression!");
      return nullptr;
    }
    ret->addArg(transExpr(expr->getRight()));
    if (ret->get(0) == nullptr) return nullptr;
  } 
  else {
    if (expr->getLeft() == NULL || expr->getRight() == NULL) {
      error(expr->line, expr->col, "Invalid Binary Operator Expression!");
      return nullptr;
    }
    ret->addArg(transExpr(expr->getLeft()));
    ret->addArg(transExpr(expr->getRight()));
    if (ret->get(0) == nullptr || ret->get(1) == nullptr) return nullptr;
  }
  // Type Check
  ret->setTyp(OprExpr_checkType(ret->getOp(), ret->getArgs()));
  if (ret->getTyp() == NULL) {
    error(expr->line, expr->col, "Error Type Matching for OprExpr!");
    return nullptr;
  }
  return ret;
}

std::shared_ptr<ir::Expr> Semant::transExpr(absyn::FuncApp* expr) {
  //TODO
  return NULL;
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
    fun->setBody( transExpr(fd->getExpr()) );
  }
}

void Semant::transNumSt(absyn::NumStDecl* nd) {
  //TODO
}

const ir::Ty* Semant::transTy(const absyn::Ty& typ) {
  int dim = typ.getDim();
  const ir::Ty* ty = tyFactory.getTy(typ.getTyp().getValue());
  if (ty == NULL) {
    error(typ.line, typ.col, "Type " + typ.getTyp().getValue() + " not found");
  }
  if (dim == 0) {
    return ty;
  } else {
    //TODO array type
    return NULL;
  }
}

const std::shared_ptr<ir::VarDecl> Semant::transVarDecl(const absyn::VarDecl & vd) {
  const ir::Ty* ty = transTy(vd.getTyp());
  return std::make_shared<ir::VarDecl>(ty, vd.getVar().getValue());
}

void Semant::error(int line, int col, const std::string& info) {
  errorMsg.error(line, col, info);
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
