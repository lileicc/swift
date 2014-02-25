#pragma once

#include <string>
#include <map>

#include "../predecl/PreDecl.h"

namespace swift {
namespace fabrica {

class PreDeclFactory {
public:
  PreDeclFactory();
  ~PreDeclFactory();

  const predecl::PreDecl* getDecl(std::string name);

private:
  std::map<std::string, const predecl::PreDecl*> decls;
};

}
}
