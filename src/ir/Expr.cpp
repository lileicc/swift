/*
 * Expr.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: leili
 */
namespace swift{
namespace ir{
Expr::Expr() {
  args = new vector<Expr*>;
}
void Expr::addArg(Expr * expr) {
  args.push_back(expr);
}
vector<Expr*> Expr::getArgs() {
  return args;
}
}
}