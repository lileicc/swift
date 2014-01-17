#pragma once

#include <string>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class OriginAttr {
public:
  OriginAttr(const std::string& name, const Ty* ty, TypeDomain* src, size_t id);
  virtual ~OriginAttr();

  const std::string& getName() const;
  const Ty* getTyp() const;
  void setID(size_t k);
  size_t getID() const;
  TypeDomain* getSrc() const;

private:
  std::string name;
  const Ty* typ;
  TypeDomain* src;
  size_t id;
};

}
}
