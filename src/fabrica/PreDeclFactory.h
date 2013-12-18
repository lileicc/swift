#pragma once

#include <string>
#include <map>

#include "../predecl/PreDeclDistr.h"

namespace swift { namespace fabrica {

class PreDeclFactory {
public:
  PreDeclFactory();
  ~PreDeclFactory();

private:
  std::map<std::string,std::map<std::string,const predecl::PreDeclDistr*>> distr;
};

}
}