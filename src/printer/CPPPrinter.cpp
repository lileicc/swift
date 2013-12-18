#include "CPPPrinter.h"

namespace swift { namespace printer {

CPPPrinter::CPPPrinter(std::string str) {
  file = fopen(str.c_str(), "w");
  if (file == NULL) {
    fprintf(stderr, "Warning: the output file is not modifiable! set defualt to stdout.\n");
    file = stdout;
  }
}

CPPPrinter::~CPPPrinter() {
  if (file != stdout) fclose(file);
}

void CPPPrinter::print(code::Code* prog) {

}

void CPPPrinter::print(code::ArraySubscriptExpr* term) {

}

void CPPPrinter::print(code::BinaryOperator* term) {

}

void CPPPrinter::print(code::CallExpr* term) {

}

void CPPPrinter::print(code::CaseStmt* term) {

}

void CPPPrinter::print(code::ClassDecl* term) {

}

void CPPPrinter::print(code::CompoundStmt* term) {

}

void CPPPrinter::print(code::DeclStmt* term) {

}

void CPPPrinter::print(code::FieldDecl* term) {

}

void CPPPrinter::print(code::FloatingLiteral* term) {

}

void CPPPrinter::print(code::ForStmt* term) {

}

void CPPPrinter::print(code::FunctionDecl* term) {

}

void CPPPrinter::print(code::IfStmt* term) {

}

void CPPPrinter::print(code::IntegerLiteral* term) {

}

void CPPPrinter::print(code::NamespaceDecl* term) {

}

void CPPPrinter::print(code::ParamVarDecl* term) {

}

void CPPPrinter::print(code::ReturnStmt* term) {

}

void CPPPrinter::print(code::SpecialStmt* term) {

}

void CPPPrinter::print(code::SwitchStmt* term) {

}

void CPPPrinter::print(code::Type* term) {

}

void CPPPrinter::print(code::VarDecl* term) {

}

void CPPPrinter::print(code::VarRef* term) {

}

}
}