#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../ir/Distribution.h"
#include "../ir/Expr.h"
#include "../fabrica/TypeFactory.h"

namespace swift {
namespace predecl {

class PreDecl {
public:
  PreDecl(const std::string& name);
  virtual ~PreDecl();

  const std::string& getName() const;
  virtual std::shared_ptr<ir::Expr>
  getNew(std::vector<std::shared_ptr<ir::Expr>>& args,
      fabrica::TypeFactory* fact) const = 0;

private:
  std::string name;
};

}
}
