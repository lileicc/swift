#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../ir/Distribution.h"
#include "../fabrica/TypeFactory.h"

namespace swift { namespace predecl {

class PreDeclDistr {
public:
  PreDeclDistr(const std::string& name);
  virtual ~PreDeclDistr();

  const std::string& getName() const;
  virtual std::shared_ptr<ir::Distribution>
    getNew(std::vector<std::shared_ptr<ir::Expr>>& args,fabrica::TypeFactory* fact) const = 0;

private:
  std::string name;
};

}
}