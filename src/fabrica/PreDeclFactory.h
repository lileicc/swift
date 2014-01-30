#pragma once

#include <string>
#include <map>

#include "../predecl/PreDeclDistr.h"

namespace swift {
namespace fabrica {

class PreDeclFactory {
public:
  PreDeclFactory();
  ~PreDeclFactory();

  const predecl::PreDeclDistr* getDistr(std::string name);

private:
  std::map<std::string, const predecl::PreDeclDistr*> distr;
};

}
}
