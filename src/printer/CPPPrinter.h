#pragma once

#include <cstdio>
#include <string>
#include <vector>

#include "../code/CodeForwardDeclaration.h"

namespace swift { namespace code {
enum class OpKind;
}
}

namespace swift {
namespace printer {

class CPPPrinter {
public:
  CPPPrinter(std::string);
  virtual ~CPPPrinter();

  // main framework of the program
  void print(code::Code* prog);

  // Statements and Expressions
  void print(code::ArraySubscriptExpr* term);
  void print(code::BinaryOperator* term);
  void print(code::BooleanLiteral* term);
  void print(code::CallExpr* term);
  void print(code::CaseStmt* term);
  void print(code::ClassDecl* term);
  void print(code::CompoundStmt* term);
  void print(code::DeclStmt* term);
  void print(code::FieldDecl* term);
  void print(code::FloatingLiteral* term);
  void print(code::ForStmt* term);
  void print(code::FunctionDecl* term);
  void print(code::IfStmt* term);
  void print(code::IntegerLiteral* term);
  void print(code::NamespaceDecl* term);
  void print(code::ParamVarDecl* term);
  void print(code::ReturnStmt* term);
  void print(code::SpecialStmt* term);
  void print(code::StringLiteral* term);
  void print(code::SwitchStmt* term);
  void print(code::Type* term);
  void print(code::VarDecl* term);
  void print(code::VarRef* term);

private:
  FILE* file;
  int indent;
  bool newline; // whether need to print a newline after a statement
  bool isforward; // whether the current phase is to print forward declaration
  // Note: when process a print method of a Stmt, we assume isforward == false
  //    for every Decl, it should be processed twice!

  std::vector<std::string> prefix; // prefix of functions
  /*
  Note:
    eg.
    class A{
      int B();
    };

    when print the body of B outside A, 
    prefix = {"A"}; 
    we print 
    int A::B(){...}
  */

  void printIndent();
  void printLine();
  void printPrefix();

  // convert an OpKind to the corresponding string in C++
  std::string OpConvert(code::OpKind op);
};

}
}


