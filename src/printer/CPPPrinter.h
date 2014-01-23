#pragma once

#include <vector>
#include "Printer.h"

namespace swift { namespace code {
enum class OpKind;
}
}

namespace swift {
namespace printer {

class CPPPrinter:public Printer {
public:
  CPPPrinter(std::string);
  virtual ~CPPPrinter();

  // add a single include
  void addHeader(std::string h);

  // main framework of the program
  void print(code::Code* prog);

  // Statements and Expressions
  void print(code::ArraySubscriptExpr* term);
  void print(code::BinaryOperator* term);
  void print(code::BooleanLiteral* term);
  void print(code::BreakStmt* term);
  void print(code::CallExpr* term);
  void print(code::CaseStmt* term);
  void print(code::ClassDecl* term);
  void print(code::ClassConstructor* term);
  void print(code::CallClassConstructor* term);
  void print(code::CompoundStmt* term);
  void print(code::ContinueStmt* term);
  void print(code::DeclContext* term);
  void print(code::DeclStmt* term);
  void print(code::FieldDecl* term);
  void print(code::FloatingLiteral* term);
  void print(code::ForStmt* term);
  void print(code::FunctionDecl* term);
  void print(code::FunctionDecl* term, bool hasRetType);
  void print(code::IfStmt* term);
  void print(code::IntegerLiteral* term);
  void print(code::ListInitExpr* term);
  void print(code::NamespaceDecl* term);
  void print(code::NullLiteral* term);
  void print(code::ParamVarDecl* term);
  void print(code::ReturnStmt* term);
  void print(code::SpecialMacro* term);
  void print(code::StringLiteral* term);
  void print(code::SwitchStmt* term);
  void print(code::Type* term);
  void print(code::VarDecl* term);
  void print(code::Identifier* term);

protected:
  void print(std::vector<code::Expr*>& exprs);
  
private:
  std::vector<std::string> header;

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
  
  void printPrefix();

  // convert an OpKind to the corresponding string in C++
  std::string OpConvert(code::OpKind op);
};

}
}


