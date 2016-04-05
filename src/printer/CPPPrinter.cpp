#include "CPPPrinter.h"

#include <cassert>
#include "../code/Code.h"

namespace swift {
namespace printer {

CPPPrinter::CPPPrinter(std::string str) :
    Printer(str), isforward(false), isheader(false) {
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
  case OpKind::UO_PLUS:
    return "+"; // unary plus
  case OpKind::UO_MINUS:
    return "-"; // unary minus
  case OpKind::UO_INC:
    return "++"; // increment
  case OpKind::UO_DEC:
    return "--"; // decrement
  case OpKind::UO_ADDR:
    return "&"; // address of
  case OpKind::UO_DEREF:
    return "*"; // deference of
  case OpKind::UO_NEW:
    return "new "; // new or malloc
  case OpKind::UO_DEL:
    return "delete "; // delete or dispose
  case OpKind::UO_ARRAY_DEL:
    return "delete[] "; // delete or dispose
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
  case OpKind::BO_AND:
    return "&&"; // and
  case OpKind::BO_OR:
    return "||"; // or
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
  case OpKind::BO_COMMA:
    return ",";
  default:
    assert(false);
    return "";
  }
}

std::pair<int, int> CPPPrinter::OpPrec(code::Expr* expr) {
  if (expr == NULL) return std::make_pair<int, int>(-1,0);
  auto b = dynamic_cast<code::BinaryOperator*>(expr);
  if (b == NULL) return std::make_pair<int,int>(0,0);
  using code::OpKind;
  auto op = b->getOp();
  switch (op) {
  case OpKind::BO_POW:
    return std::make_pair<int, int>(0,0);
  case OpKind::BO_FIELD:
  case OpKind::BO_POINTER:
  case OpKind::BO_SCOPE:
    return std::make_pair<int, int>(1,0);
  case OpKind::UO_INC:
  case OpKind::UO_DEC:
    if (b->getLeft() != NULL)
      return std::make_pair<int, int>(1,0);
  case OpKind::UO_CMPT:
  case OpKind::UO_NEG:
  case OpKind::UO_PLUS:
  case OpKind::UO_MINUS:
  case OpKind::UO_ADDR:
  case OpKind::UO_DEREF:
    return std::make_pair<int, int>(2,1);
  case OpKind::UO_NEW:
  case OpKind::UO_DEL:
  case OpKind::UO_ARRAY_DEL:
    return std::make_pair<int, int>(3,1);
  case OpKind::BO_MUL:
    if (b->getLeft() == NULL)
      return std::make_pair<int, int>(2,1);
  case OpKind::BO_DIV:
  case OpKind::BO_MOD:
    return std::make_pair<int, int>(4,0);
  case OpKind::BO_PLUS:
  case OpKind::BO_MINUS:
    if (b->getLeft() == NULL)
      return std::make_pair<int, int>(2,1);
    else
      return std::make_pair<int, int>(5,0);
  case OpKind::BO_LSHGT:
  case OpKind::BO_RSHGT:
    return std::make_pair<int, int>(6,0);
  case OpKind::BO_LT:
  case OpKind::BO_GT:
  case OpKind::BO_LEQ:
  case OpKind::BO_GEQ:
    return std::make_pair<int, int>(7,0);
  case OpKind::BO_EQU:
  case OpKind::BO_NEQ:
    return std::make_pair<int, int>(8,0);
  case OpKind::BO_BAND:
    if (b->getLeft() == NULL)
      return std::make_pair<int, int>(2,1);
    else
      return std::make_pair<int, int>(9,0);
  case OpKind::BO_XOR:
    return std::make_pair<int, int>(10,0);
  case OpKind::BO_BOR:
    return std::make_pair<int, int>(11,0);
  case OpKind::BO_AND:
    return std::make_pair<int, int>(12,0);
  case OpKind::BO_OR:
    return std::make_pair<int, int>(13,0);
  case OpKind::BO_ASSIGN:
  case OpKind::BO_SPLUS:
  case OpKind::BO_SMINUS:
  case OpKind::BO_SMUL:
  case OpKind::BO_SDIV:
  case OpKind::BO_SMOD:
    return std::make_pair<int, int>(15,1);
  case OpKind::BO_COMMA:
    return std::make_pair<int, int>(16,0);
  case OpKind::BO_RANGE:
    return std::make_pair<int, int>(17,0);
  default:
    assert(false);
    return std::make_pair<int,int>(18,0);
  }
}

void CPPPrinter::printPrefix() {
  for (auto p : prefix) {
    fprintf(file, "%s::", p.c_str());
  }
}

void CPPPrinter::addHeader(std::string h) {
  if(h.size() == 0) return;
  if(h[0]!='<' && h[0]!='\"') h="\""+h;
  if(h[h.size()-1]!='>' && h[h.size()-1]!='\"') h.push_back('\"');
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
  isheader = false;

  // output include
  fprintf(file, "#include <iostream>\n");
  fprintf(file, "#include <fstream>\n");
  fprintf(file, "#include <sstream>\n");
  fprintf(file, "#include <cstdio>\n");
  fprintf(file, "#include <cstdlib>\n");
  fprintf(file, "#include <cstring>\n");
  fprintf(file, "#include <cmath>\n");
  fprintf(file, "#include <cassert>\n");
  fprintf(file, "#include <algorithm>\n");
  fprintf(file, "#include <vector>\n");
  fprintf(file, "#include <set>\n");
  fprintf(file, "#include <map>\n");
  fprintf(file, "#include <unordered_map>\n");
  fprintf(file, "#include <chrono>\n");
  fprintf(file, "#include <random>\n");
  fprintf(file, "#include <numeric>\n");
  fprintf(file, "#include <string>\n");
  fprintf(file, "#include <memory>\n");
  fprintf(file, "#include <functional>\n");
  fprintf(file, "#include <utility>\n");
  fprintf(file, "#include \"random/Bernoulli.h\"\n");
  fprintf(file, "#include \"random/Beta.h\"\n");
  fprintf(file, "#include \"random/Binomial.h\"\n");
  fprintf(file, "#include \"random/BooleanDistrib.h\"\n");
  fprintf(file, "#include \"random/Categorical.h\"\n");
  fprintf(file, "#include \"random/Exponential.h\"\n");
  fprintf(file, "#include \"random/Gaussian.h\"\n");
  fprintf(file, "#include \"random/Gamma.h\"\n");
  fprintf(file, "#include \"random/Geometric.h\"\n");
  fprintf(file, "#include \"random/Poisson.h\"\n");
  fprintf(file, "#include \"random/InvGamma.h\"\n");
  fprintf(file, "#include \"random/UniformChoice.h\"\n");
  fprintf(file, "#include \"random/UniformInt.h\"\n");
  fprintf(file, "#include \"random/UniformReal.h\"\n");
  fprintf(file, "#include \"util/Hist.h\"\n");
  fprintf(file, "#include \"util/util.h\"\n");
  fprintf(file, "#include \"util/DynamicTable.h\"\n");

  // output costumized include
  for (auto h : header)
    fprintf(file, "#include %s\n", h.c_str());

  // print special include/statements
  for (auto s : prog->getAllMacros())
    s->print(this);
  printLine();

  // Check for Special Printing Option
  for (auto s : prog->getAllOptions()) {
    if (s == "matrix") {
      // Support Matrix
      fprintf(file, "\n// Matrix Library included\n");
      fprintf(file, "#include \"armadillo\"\n");
      fprintf(file, "#include \"random/Dirichlet.h\"\n");
      fprintf(file, "#include \"random/Discrete.h\"\n");
      fprintf(file, "#include \"random/MultivarGaussian.h\"\n");
      fprintf(file, "#include \"random/MultivarGaussianIndep.h\"\n");
      fprintf(file, "#include \"random/Multinomial.h\"\n");
      fprintf(file, "#include \"random/UniformVector.h\"\n");
      fprintf(file, "#include \"util/Hist_matrix.h\"\n");
      fprintf(file, "#include \"util/util_matrix.h\"\n");
      fprintf(file, "using namespace arma;\n\n");
    } else
    if (s == "MCMC" || s == "mcmc") {
      // Support MCMC algorithms (Parental-MH, Gibbs)
      fprintf(file, "\n// MCMC Library included\n");
      fprintf(file, "#include \"util/MCMC.h\"\n");
      fprintf(file, "#include \"util/util_MCMC.h\"\n");
    }
  }

  //fprintf(file, "#define bool char\n"); // currently a hack for bool type, since elements in vector<bool> cannot be referenced
  fprintf(file, "using namespace std;\n");
  fprintf(file, "using namespace swift::random;\n");

  printLine();
  // print forward declaration
  isforward = true; isheader = false;
  for (auto p : prog->getAllDecls())
    p->print(this);
  printLine();

  // print header declaration
  isforward = false; isheader = true;
  for (auto p : prog->getAllDecls())
    p->print(this);
  printLine();

  // print main body
  isforward = false; isheader = false;
  for (auto p : prog->getAllDecls())
    p->print(this);

}

void CPPPrinter::print(code::ArraySubscriptExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  // Note: [] operator
  if (term->getLeft() != NULL) {
    auto l_prec = OpPrec(term->getLeft());
    if (l_prec.first > 1)
      fprintf(file, "(");
    term->getLeft()->print(this);
    if (l_prec.first > 1)
      fprintf(file, ")");
  }
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

  auto l_prec = OpPrec(term->getLeft()).first;
  auto r_prec = OpPrec(term->getRight()).first;

  if (term->getOp() == code::OpKind::BO_POW) {
    fprintf(file, "std::pow(");
    term->getLeft()->print(this);
    fprintf(file, ",");
    term->getRight()->print(this);
    fprintf(file, ")");
  } else {
    std::string op = OpConvert(term->getOp());
    auto op_prec = OpPrec(term);

    if (term->getLeft() != NULL) {
      if (l_prec > op_prec.first || (l_prec == op_prec.first && op_prec.second == 1))
        fprintf(file, "(");
      term->getLeft()->print(this);
      if (l_prec > op_prec.first || (l_prec == op_prec.first && op_prec.second == 1))
        fprintf(file, ")");
    }
    fprintf(file, "%s", op.c_str());
    if (term->getRight() != NULL) {
      if (r_prec > op_prec.first || (r_prec == op_prec.first && op_prec.second == 0))
        fprintf(file, "(");
      term->getRight()->print(this);
      if (r_prec > op_prec.first || (r_prec == op_prec.first && op_prec.second == 0))
        fprintf(file, ")");
    }
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

  // Note: () operatorƒf
  auto f_prec = OpPrec(term->getFunc());
  if (f_prec.first > 1)
    fprintf(file, "(");
  term->getFunc()->print(this);
  if (f_prec.first > 1)
    fprintf(file, ")");

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

void CPPPrinter::print(code::NewExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  fprintf(file, "new ");
  term->getExpr()->print(this);

  newline = backup;
  if (backup)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::TemplateExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  // Note: () operatorƒf
  auto f_prec = OpPrec(term->getVar());
  if (f_prec.first > 1)
    fprintf(file, "(");
  term->getVar()->print(this);
  if (f_prec.first > 1)
    fprintf(file, ")");

  bool not_first = false;
  fprintf(file, "<");
  for (auto p : term->getArgs()) {
    if (not_first)
      fprintf(file, ",");
    else
      not_first = true;
    p->print(this);
  }
  fprintf(file, ">");

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
  if (isforward) { // print forward decl of the class
    printIndent();
    fprintf(file, "class %s;", term->getName().c_str());
    printLine();
  } else
  if (isheader) { // print everything except body of FunctionDecl
    printIndent();
    fprintf(file, "class %s", term->getName().c_str());
    // inheritance
    if (term->getInherit().size() > 0) {
      bool backup = newline;
      newline = false;

      auto& h = term->getInherit();
      for (size_t i = 0; i < h.size(); ++i) {
        if (i == 0)
          fprintf(file, ":");
        else
          fprintf(file, ",");
        fprintf(file, " public ");
        h[i].print(this);
      }

      newline = backup;
    }
    fprintf(file, " {");
    printLine();
    printIndent();
    fprintf(file, "public:");
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

  auto backup = newline;
  newline = true;
  if (term->getAll().size() > 0)
    printLine();

  incIndent();

  for (auto p : term->getAll())
    p->print(this);

  decIndent();

  if (term->getAll().size() > 0) // Otherwise it is just an empty block, no indent/newline needed
    printIndent();
  fprintf(file, "}");

  newline = backup;
  printLine();
}

void CPPPrinter::print(code::ContinueStmt* term) {
  printIndent();
  fprintf(file, "continue;");
  printLine();
}

void CPPPrinter::print(code::DeclStmt* term) {
  // We assume now isforward == false && isheader == false
  assert(isforward == false && isheader == false);

  isforward = true; isheader = false;
  term->getDecl()->print(this);
  isforward = false; isheader = true;
  term->getDecl()->print(this);
  isforward = false; isheader = false;
  term->getDecl()->print(this);
}

void CPPPrinter::print(code::FieldDecl* term) {
  print((code::VarDecl*) term);
}

void CPPPrinter::print(code::FloatingLiteral* term) {
  printIndent();
  // Special Case!
  //   Generally Here we keep 8 digits after decimal point
  if (term->getVal() < 1e-6)
    fprintf(file, "%s", std::to_string(term->getVal()).c_str());
  else {
    fprintf(file, "%.8lf", term->getVal());
  }
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

  if (term->getBody() != NULL) { // at least a pair of brackets will be printed
    printLine();
    term->getBody()->print(this);
  }
  else // Body is empty
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(code::FunctionDecl* term) {
  print(term, true);
}

void CPPPrinter::print(code::FunctionDecl* term, bool hasRetType) {
  if (isforward) return ;
  bool backup;
  if (isheader) {
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
    for (auto&d : term->getAllDecls()) {
      d->print(this);
    }
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
  fprintf(file, "nullptr");
  if (newline) {
    fprintf(file, ";");
    printLine();
  }
}

void CPPPrinter::print(code::NamespaceDecl* term) {
  if (isforward || isheader)
    return;

  printIndent();
  fprintf(file, "namespace %s {", term->getName().c_str());
  printLine();
  printLine();

  // print forward declaration
  isforward = true; isheader = false;
  for (auto p : term->getAllDecls())
    p->print(this);
  printLine();

  // print header declaration
  isforward = false; isheader = true;
  for (auto p : term->getAllDecls())
    p->print(this);
  printLine();

  // print body
  isforward = false; isheader = false;
  for (auto p : term->getAllDecls())
    p->print(this);
  printLine();

  printIndent();
  fprintf(file, "}");
  printLine();
}

void CPPPrinter::print(code::ParamVarDecl* term) {
  if (isforward) return ;
  // assume newline == false
  assert(newline == false);

  bool backup = newline;
  newline = false;
  if (isheader) {
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
  assert(newline == false);
  if (term->isConst())
    fprintf(file, "const ");
  if (term->hasScope()) {
    for (auto & nm : term->getScope()) {
      fprintf(file, "%s::", nm.c_str());
    }
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
  if (term->isPtr())
    fprintf(file, "*");
}

void CPPPrinter::print(code::VarDecl* term) {
  if (!isheader)
    return;

  printIndent();
  bool backup = newline;
  newline = false;

  term->getType().print(this);
  fprintf(file, " %s", term->getId().c_str());

  if (term->getArrArgs().size() > 0) {
    for (auto p : term->getArrArgs()) {
      fprintf(file, "[");
      p->print(this);
      fprintf(file, "]");
    }
  }

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

//void CPPPrinter::print(code::DeleteStmt* term) {
//  printIndent();
//  if (term->isArray()) {
//    fprintf(file, "delete[] ");
//  } else {
//    fprintf(file, "delete ");
//  }
//  bool backup = newline;
//  newline = false;
//  term->getVar()->print(this);
//  newline = backup;
//  fprintf(file, ";");
//  printLine();
//}

//void CPPPrinter::print(code::NewExpr* term) {
//  fprintf(file, "new ");
//  if (term->isArray()) {
//    term->getType().print(this);
//    fprintf(file, "[");
//    term->getExpr()->print(this);
//    fprintf(file, "]");
//  } else {
//    term->getExpr()->print(this);
//  }
//}

void CPPPrinter::print(code::DeclContext* term) {
  // note should not reach here!!
  term->print(this);
}

void CPPPrinter::print(code::ListInitExpr* term) {
  fprintf(file, "{");
  print(term->getArgs());
  fprintf(file, "}");
}

std::string CPPPrinter::getLambdaKindStr(code::LambdaKind kind) {
  using code::LambdaKind;
  switch (kind) {
  case LambdaKind::NA:
    return "";
  case LambdaKind::REF:
    return "&";
  case LambdaKind::COPY:
    return "=";
  case LambdaKind::THIS:
    return "this";
  default: return "";
  }
}

void CPPPrinter::print(code::LambdaExpr* term) {
  printIndent();
  bool backup = newline;
  newline = false;

  fprintf(file, "[%s]",getLambdaKindStr(term->getKind()).c_str());
  fprintf(file, "(");

  bool isFirst = true;
  for (auto p : term->getParams()) {
    if (!isFirst) fprintf(file, ", ");
    else isFirst = false;
    p->print(this);
  }

  fprintf(file, ")");

  term->getBody().print(this);

  newline = backup;
  if (backup)
    fprintf(file, ";");
  printLine();
}

void CPPPrinter::print(std::vector<code::Expr*>& exprs) {
  bool first = true;
  for (auto ex : exprs) {
    if (!first) {
      fprintf(file, ", ");
    } else {
      first = false;
    }
    ex->print(this);
  }
}

void CPPPrinter::print(code::ClassConstructor* term) {
  if (isforward) return;
  bool backup;
  if (isheader) {
    printIndent();
    backup = newline;
    newline = false;
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
  }
  else {
    printIndent();
    backup = newline;
    newline = false;
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

    // print initial expression
    if (term->getInitExpr() != NULL) {
      fprintf(file, ":");
      term->getInitExpr()->print(this);
    }

    newline = backup;
    printLine();

    term->getBody().print(this);
  }

}

void CPPPrinter::print(code::CallClassConstructor* term) {
  term->getType().print(this);
  fprintf(file, "(");
  print(term->getArgs());
  fprintf(file, ")");
}

}
}
