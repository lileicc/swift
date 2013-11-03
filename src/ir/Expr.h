/*
 * Expr.h
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */

#include <vector>
namespace swift{
namespace ir{
class Expr : public Clause {
public:
  Expr();
  virtual ~Expr();
  void addArg(Expr * expr);
  vector<Expr*> getArgs();
private:
  vector<Expr*> args;
};
}
}