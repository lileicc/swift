/*
 * Expr.h
 *
 *  Created on: Oct 28, 2013
 *      Author: leili
 */

#pragma once

#include<vector>
#include "Absyn.h"

namespace swift {
  namespace absyn {

  class Expr : public Absyn {
  public:
    Expr(int l, int c);
    virtual ~Expr();

    void add(Expr* e);
    Expr* get(int id);
    size_t size();

  protected:
    std::vector<Expr*> args;
  };

}}