#include "CPPPrinter.h"

#include <cassert>
#include "../code/Code.h"

namespace swift {
namespace printer {

CPPPrinter::CPPPrinter(std::string str) :
    Printer(str), isforward(false) {
}

CPPPrinter::~CPPPrinter() {
}

std::string CPPPrinter::OpConvert(code::OpKind op) {
  using code::OpKind;
  switch (op) {
  case OpKind::UO_CMPT:
    return "~"; // complement
  case OpKind::UO_NEG:
    return "!"; // negate
  case OpKind::UO_INC:
    return "++"; // increment
  case OpKind::UO_DEC:
    return "--"; // decrement
  case OpKind::UO_NEW:
    return "new "; // new or malloc
  case OpKind::UO_DEL:
    return "delete "; // delete or dispose
  case OpKind::BO_ASSIGN:
    return "="; // Assignment
  case OpKind::BO_FIELD:
    return "."; // reference to a field
  case OpKind::BO_RANGE:
    return ": "; // range operator
  case OpKind::BO_LSHGT:
    return "<<"; // binary left shift
  case OpKind::BO_RSHGT:
    return ">>"; // binary right shift
  case OpKind::BO_BAND:
    return "&"; // binary and
  case OpKind::BO_BOR:
    return "|"; // binary or
  case OpKind::BO_XOR:
    return "^"; // binary xor
  case OpKind::BO_EQU:
    return "=="; // equal
  case OpKind::BO_NEQ:
    return "!="; // not equal
  case OpKind::BO_LT:
    return "<"; // less than
  case OpKind::BO_GT:
    return ">"; // greater than
  case OpKind::BO_LEQ:
    return "<="; // less then or equal
  case OpKind::BO_GEQ:
    return ">="; // greater then or equal
  case OpKind::BO_PLUS:
    return "+"; // plus
  case OpKind::BO_MINUS:
    return "-"; // minus
  case OpKind::BO_MUL:
    return "*"; // multiply
  case OpKind::BO_DIV:
    return "/"; // divide
  case OpKind::BO_MOD:
    return "%"; // module
  case OpKind::BO_SPLUS:
    return "+="; // self plus
  case OpKind::BO_SMINUS:
    return "-="; // self minus
  case OpKind::BO_SMUL:
    return "*="; // self multiply
  case OpKind::BO_SDIV:
    return "/="; // self divide
  case OpKind::BO_SMOD:
    return "%="; // self module
  case OpKind::BO_POINTER:
    return "->"; // pointer to a field
  case OpKind::BO_SCOPE:
    return "::";
  default:
    assert(false);
    return "";
  }
}

void CPPPrinter::printPrefix() {
  for (auto p : prefix) {
    fprintf(file, "%s::", p.c_str());
  }
}

void CPPPrinter::addHeader(std::string h) {
  header.push_back(h);
}

void CPPPrinter::print(code::Code* prog) {
  /*

   stmt contains all the includes, using and defines
   Note: standard includes will be printed automatically
   decl contains the body of the program

   */
  indent = 0;
  newline = true;
  prefix.clear();
  isforward = false;

  // output include
  fprintf(file, "#include<iostream>\n");
  fprintf(file, "#include<fstream>\n");
  fprintf(file, "#include<sstream>\n");
  fprintf(file, "#include<cstdio>\n");
  fprintf(file, "#include<cstdlib>\n");
  fprintf(file, "#include<cstring>\n");
  fprintf(file, "#include<cmath>\n");
  fprintf(file, "#include<cassert>\n");
  fprintf(file, "#include<algorithm>\n");
  fprintf(file, "#include<vector>\n");
  fprintf(file, "#include<set>\n");
  fprintf(file, "#include<map>\n");
  fprintf(file, "#include<unordered_map>\n");
  fprintf(file, "#include<chrono>\n");
  fprintf(file, "#include<random>\n");
  fprintf(file, "#include<numeric>\n");
  fprintf(file, "#include<string>\n");
  fprintf(file, "#include \"random/CategoricalDistribution.h\"\n");
  fprintf(file, "#include \"util/Hist.h\"\n");
  
  // output costumized include
  for (auto h : header)
    fprintf(file, "#include %s\n", h.c_str());

  // print special include/statements
  for (auto s : prog->getAllMacros())
    s->print(this);
  printLine();
  
  fprintf(file, "using namespace std;\n");
  fprintf(file, "using namespace swift::random;\n");

  printLine();
  // print forward declaration
  isforward = true;
  for (auto p : prog->getAllDecls())
    p->print(this);
  printLine();

  // print main body
  isforward = false;
  for (auto p : prog->getAllDecls())
    p->print(this);
  
}

void CPPPrinter::print(code::ArraySubscriptExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  if (term->getLeft() != NULL)
    term->getLeft()->print(this);
  fprintf(file, "[");
  if (term->getRight() != NULL)
    term->getRight()->print(this);
  fprintf(file, "]");

  newline = backup;
  if (backup)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::BinaryOperator* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  if (term->getOp() == code::OpKind::BO_POW) {
    fprintf(file, "std::pow(");
    term->getLeft()->print(this);
    fprintf(file, ",");
    term->getRight()->print(this);
    fprintf(file, ")");
  } else {
    if (!newline)
      fprintf(file, "(");
    std::string op = OpConvert(term->getOp());
    if (term->getLeft() != NULL)
      term->getLeft()->print(this);
    fprintf(file, "%s", op.c_str());
    if (term->getRight() != NULL)
      term->getRight()->print(this);
    if (!newline)
      fprintf(file, ")");
  }

  newline = backup;
  if (backup)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::BooleanLiteral* term) {
  printIndent();
  if (term->getVal())
    fprintf(file, "true");
  else
    fprintf(file, "false");
  if (newline)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::BreakStmt* term) {
  printIndent();
  fprintf(file, "break;");
  printLine();
}

void CPPPrinter::print(code::CallExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  term->getFunc()->print(this);
  fprintf(file, "(");
  bool not_first = false;
  for (auto p : term->getArgs()) {
    if (not_first)
      fprintf(file, ",");
    else
      not_first = true;
    p->print(this);
  }
  fprintf(file, ")");

  newline = backup;
  if (backup)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::CaseStmt* term) {
  decIndent();
  printIndent();
  fprintf(file, "case ");
  bool backup = newline;
  newline = false;
  term->getVal()->print(this);
  newline = backup;
  fprintf(file, ":");
  printLine();
  incIndent();

  if (term != NULL)
    term->getSub()->print(this);
}

void CPPPrinter::print(code::ClassDecl* term) {
  if (isforward) { // print everything except body of FunctionDecl
    printIndent();
    fprintf(file, "class %s { public:", term->getName().c_str());
    printLine();
    incIndent();
    for (auto p : term->getAllDecls())
      p->print(this);
    decIndent();
    printIndent();
    fprintf(file, "};");
    printLine();
  } else { // print body of FunctionDecl
    prefix.push_back(term->getName());
    for (auto p : term->getAllDecls())
      p->print(this);
    prefix.pop_back();
  }
}

void CPPPrinter::print(code::CompoundStmt* term) {
  printIndent();
  fprintf(file, "{");
  printLine();
  incIndent();

  for (auto p : term->getAll())
    p->print(this);

  decIndent();
  printIndent();
  fprintf(file, "}");
  printLine();
}

void CPPPrinter::print(code::ContinueStmt* term) {
  printIndent();
  fprintf(file, "continue;");
  printLine();
}

void CPPPrinter::print(code::DeclStmt* term) {
  // We assume now isforward == false
  assert(isforward == false);

  isforward = true;
  term->getDecl()->print(this);
  isforward = false;
  term->getDecl()->print(this);
}

void CPPPrinter::print(code::FieldDecl* term) {
  if (!isforward)
    return;
  printIndent();
  bool backup = newline;
  newline = false;
  term->getType().print(this);
  fprintf(file, " %s;", term->getId().c_str());
  newline = backup;
  printLine();
}

void CPPPrinter::print(code::FloatingLiteral* term) {
  printIndent();
  // Special Case!
  //   Here we keep 7 digits after decimal point
  fprintf(file, "%.7lf", term->getVal());
  if (newline)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::ForStmt* term) {
  printIndent();
  fprintf(file, "for (");

  bool backup = newline;
  newline = false;

  if (term->isRange()) {
    fprintf(file, "auto ");
    term->getInit()->print(this);
  } else {
    if (term->getInit() != NULL)
      term->getInit()->print(this);
    fprintf(file, ";");
    if (term->getCond() != NULL)
      term->getCond()->print(this);
    fprintf(file, ";");
    if (term->getStep() != NULL)
      term->getStep()->print(this);
  }

  fprintf(file, ")");
  newline = backup;

  if (term->getBody() != NULL) {
    printLine();
    term->getBody()->print(this);
  }
  fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::FunctionDecl* term) {
  print(term, true);
}

void CPPPrinter::print(code::FunctionDecl* term, bool hasRetType) {
  bool backup;
  if (isforward) {
    printIndent();
    backup = newline;
    newline = false;
    if (term->isInline())
      fprintf(file, "inline ");
    if (hasRetType) {
      term->getType().print(this);
      fprintf(file, " ");
    }
    fprintf(file, "%s(", term->getName().c_str());
    bool not_first = false;
    for (auto p : term->getParams()) {
      if (not_first)
        fprintf(file, ",");
      else
        not_first = true;
      p->print(this);
    }
    fprintf(file, ");");
    newline = backup;
    printLine();
  } else {
    printIndent();
    backup = newline;
    newline = false;
    if (term->isInline())
      fprintf(file, "inline ");
    if (hasRetType) {
      term->getType().print(this);
      fprintf(file, " ");
    }
    printPrefix();
    fprintf(file, "%s(", term->getName().c_str());
    bool not_first = false;
    for (auto p : term->getParams()) {
      if (not_first)
        fprintf(file, ", ");
      else
        not_first = true;
      p->print(this);
    }
    fprintf(file, ")");
    newline = backup;
    printLine();

    term->getBody().print(this);
  }
}

void CPPPrinter::print(code::IfStmt* term) {
  printIndent();
  fprintf(file, "if (");
  bool backup = newline;
  newline = false;
  term->getCond()->print(this);
  fprintf(file, ")");
  newline = backup;

  if (term->getThen() != NULL) {
    printLine();
    incIndent();
    term->getThen()->print(this);
    decIndent();
  }
  if (term->getElse() != NULL) {
    printIndent();
    fprintf(file, "else");
    printLine();
    incIndent();
    term->getElse()->print(this);
    decIndent();
  }
}

void CPPPrinter::print(code::IntegerLiteral* term) {
  printIndent();
  fprintf(file, "%d", term->getVal());
  if (newline)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::NullLiteral* term) {
  fprintf(file, "NULL");
  if (newline) {
    fprintf(file, ";");
    printLine();
  }
}

void CPPPrinter::print(code::NamespaceDecl* term) {
  if (isforward)
    return;

  printIndent();
  fprintf(file, "namespace %s {", term->getName().c_str());
  printLine();
  printLine();

  // print forward declaration
  isforward = true;
  for (auto p : term->getAllDecls())
    p->print(this);
  printLine();

  // print body
  isforward = false;
  for (auto p : term->getAllDecls())
    p->print(this);
  printLine();

  printIndent();
  fprintf(file, "}");
  printLine();
}

void CPPPrinter::print(code::ParamVarDecl* term) {
  // assume newline == false
  assert(newline == false);

  bool backup = newline;
  newline = false;
  if (isforward) {
    term->getType().print(this);
    if (term->getValue() != NULL) {
      fprintf(file, "=");
      term->getValue()->print(this);
    }
  } else {
    term->getType().print(this);
    fprintf(file, " %s", term->getId().c_str());
  }
  newline = backup;
}

void CPPPrinter::print(code::ReturnStmt* term) {
  printIndent();
  fprintf(file, "return ");

  if (term->getExpr() != NULL) {
    bool backup = newline;
    newline = false;
    term->getExpr()->print(this);
    newline = backup;
  }

  fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::SpecialMacro* term) {
  // Note: No need to print ';' here!
  printIndent();
  fprintf(file, "%s", term->getMacro().c_str());
  printLine();
}

void CPPPrinter::print(code::StringLiteral* term) {
  printIndent();
  fprintf(file, "\"%s\"", term->getVal().c_str());
  if (newline)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::SwitchStmt* term) {
  printIndent();
  fprintf(file, "switch (");
  bool backup = newline;
  newline = false;
  term->getCond()->print(this);
  newline = backup;
  fprintf(file, ")");
  printLine();

  term->getBody()->print(this);
}

void CPPPrinter::print(code::Type* term) {
  // assume newline == false;
  // assume newline == false;
  assert(newline == false);
  if (term->getScope() != nullptr) {
    term->getScope()->print(this);
    fprintf(file, "::");
  }
  fprintf(file, "%s", term->getName().c_str());
  if (term->getTypeArgs().size() > 0) {
    fprintf(file, "<");
    auto it = term->getTypeArgs().begin();
    it->print(this);
    for (it++; it != term->getTypeArgs().end(); it++) {
      fprintf(file, ",");
      it->print(this);
    }
    fprintf(file, ">");
  }
  if (term->isRef())
    fprintf(file, "&");
}

void CPPPrinter::print(code::VarDecl* term) {
  if (!isforward)
    return;

  bool backup = newline;
  newline = false;
  printIndent();

  term->getType().print(this);
  fprintf(file, " %s", term->getId().c_str());
  if (term->getValue() != NULL) {
    fprintf(file, " = ");
    term->getValue()->print(this);
  }

  newline = backup;
  if (backup)
    fprintf(file, ";"); // Note: VarDecl can be in a ForStmt
  printLine();
}

void CPPPrinter::print(code::Identifier* term) {
  printIndent();
  fprintf(file, "%s", term->getId().c_str());

  if (newline)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::DeleteStmt* term) {
  printIndent();
  if (term->isArray()) {
    fprintf(file, "delete[] ");
  } else {
    fprintf(file, "delete ");
  }
  bool backup = newline;
  newline = false;
  term->getVar()->print(this);
  newline = backup;
  fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::NewExpr* term) {
  fprintf(file, "new ");
  if (term->isArray()) {
    term->getType().print(this);
    fprintf(file, "[");
    term->getExpr()->print(this);
    fprintf(file, "]");
  } else {
    term->getExpr()->print(this);
  }
}

void CPPPrinter::print(code::DeclContext* term) {
  // note should not reach here!!
  term->print(this);
}

void CPPPrinter::print(code::ListInitExpr* term) {
  bool first = true;
  fprintf(file, "{");
  for (auto ex : term->getSubExprs()) {
    if (! first) {
      fprintf(file, ", ");
    } else {
      first = false;
    }
    ex->print(this);
  }
  fprintf(file, "}");
}

void CPPPrinter::print(code::ClassConstructor* term) {
  print(term, false);
}

}
}


