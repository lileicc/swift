#pragma once

#include <string>

#include "IRForwardDecl.h"

#include "Ty.h"

namespace swift { namespace ir {

class OriginAttr {
public:
  OriginAttr(const std::string& name, Ty* ty, TypeDomain* src);
  virtual ~OriginAttr();

  const std::string& getName();
  Ty* getTyp();
  void setID(int k);
  int getID();
  TypeDomain* getSrc();

private:
  std::string name;
  int id;
  Ty* typ;
  TypeDomain* src;
};

}
}