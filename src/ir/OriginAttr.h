#pragma once

#include <string>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class OriginAttr {
public:
  OriginAttr(const std::string& name, const Ty* ty, TypeDomain* src, int id);
  virtual ~OriginAttr();

  const std::string& getName() const;
  const Ty* getTyp() const;
  void setID(int k);
  int getID() const;
  TypeDomain* getSrc() const;

private:
  std::string name;
  const Ty* typ;
  TypeDomain* src;
  int id;
};

}
}
