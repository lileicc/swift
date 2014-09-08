#pragma once

#include <vector>
#include "Printer.h"

namespace swift {
namespace code {
enum class OpKind;
enum class LambdaKind;
}
}

namespace swift {
namespace printer {

class CPPPrinter: public Printer {
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
  void print(code::CallTemplateExpr* term);
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
  void print(code::LambdaExpr* term);
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
  bool isheader; // whether the current phase is to print the header file declarations
  // Note: when process a print method of a Stmt, we assume isforward == false
  //    for every Decl, it should be processed THREE Times!
  //    i.e. ForwardDecl (for classes), HeaderFile Decl (for methods), Function Body Decl
  //     Attention: isforward only works for class decl!!! isheader works for functiondecl, vardecl, methoddecl, memberdecl

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

  // return the Precedence and Associativity(0: left to right, 1: right to left) of an Expr
  std::pair<int, int> OpPrec(code::Expr* expr);

  // return the string flag corresponding to the kind of lambda expression
  //  e.g. LambdaKind::REF  ==>  [&](){...}
  //       LambdaKind::NONE ==>  [] (){...}
  std::string getLambdaKindStr(code::LambdaKind kind);
};

}
}

