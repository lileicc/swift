/*
 * ConjugatePrior.h
 *
 *  Created on: Apr 30, 2015
 *      Author: yiwu
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <set>
#include "../Analyzer.h"

namespace swift {
namespace analyzer {
namespace conjugate {

class ConjugatePrior{
public:
  ConjugatePrior(std::string _distrib = std::string(""));
  
  std::string getDistr();
  
  virtual std::shared_ptr<ir::Expr> process(
    std::shared_ptr<ir::FuncDefn> fun,
    std::set<std::shared_ptr<ir::FuncDefn>> child) = 0;

private:
  std::string distrb;
};

}
}
} /* namespace swift */
