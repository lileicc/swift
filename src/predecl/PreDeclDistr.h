#pragma once

#include <string>
#include <vector>

namespace swift { namespace predecl {

class PreDeclDistr {
public:
  PreDeclDistr(const std::string& name);
  virtual ~PreDeclDistr();

  const std::string& getName() const;

private:
  std::string name;
  std::vector<std::string> argTyp;
};

}
}