#pragma once

#include <string>

#include "IRForwardDecl.h"

namespace swift { namespace ir {

class OriginAttr {
public:
  OriginAttr(const std::string& name, Ty* ty, TypeDomain* src, int id);
  virtual ~OriginAttr();

  const std::string& getName();
  Ty* getTyp();
  void setID(int k);
  int getID();
  TypeDomain* getSrc();

private:
  std::string name;
  Ty* typ;
  TypeDomain* src;
  int id;
};

}
}
