#pragma once

#include <cstdio>
#include <string>

#include "../code/CodeForwardDeclaration.h"

namespace swift {
namespace printer {

class Printer {
public:
  Printer(std::string);
  virtual ~Printer();

  // main framework of the program
  virtual void print(code::Code* prog)=0;

  // Statements and Expressions
  virtual void print(code::ArraySubscriptExpr* term)=0;
  virtual void print(code::BinaryOperator* term)=0;
  virtual void print(code::BooleanLiteral* term)=0;
  virtual void print(code::BreakStmt* term) = 0;
  virtual void print(code::CallExpr* term)=0;
  virtual void print(code::CaseStmt* term)=0;
  virtual void print(code::ClassDecl* term)=0;
  virtual void print(code::ClassConstructor* term)=0;
  virtual void print(code::CallClassConstructor* term)=0;
  virtual void print(code::CompoundStmt* term)=0;
  virtual void print(code::ContinueStmt* term) = 0;
  virtual void print(code::DeclContext* term)=0;
  virtual void print(code::DeclStmt* term)=0;
  virtual void print(code::FieldDecl* term)=0;
  virtual void print(code::FloatingLiteral* term)=0;
  virtual void print(code::ForStmt* term)=0;
  virtual void print(code::FunctionDecl* term)=0;
  virtual void print(code::IfStmt* term)=0;
  virtual void print(code::IntegerLiteral* term)=0;
  virtual void print(code::LambdaExpr* term)=0;
  virtual void print(code::ListInitExpr* term)=0;
  virtual void print(code::NamespaceDecl* term)=0;
  virtual void print(code::NullLiteral* term)=0;
  virtual void print(code::ParamVarDecl* term)=0;
  virtual void print(code::ReturnStmt* term)=0;
  virtual void print(code::SpecialMacro* term)=0;
  virtual void print(code::StringLiteral* term)=0;
  virtual void print(code::SwitchStmt* term)=0;
  virtual void print(code::Type* term)=0;
  virtual void print(code::VarDecl* term)=0;
  virtual void print(code::VarArrayDecl* term) = 0;
  virtual void print(code::Identifier* term)=0;

protected:
  FILE* file;
  int indent;
  bool newline; // whether need to print a newline after a statement
  /**
   * add one more indent defined by the TAB_SIZE
   */
  void incIndent() {
    indent += TAB_SIZE;
  }
  /**
   * reduce one indent defined by the TAB_SIZE
   */
  void decIndent() {
    indent -= TAB_SIZE;
  }
  static const int TAB_SIZE = 2;

  void printIndent();
  void printLine();
};

}
}

