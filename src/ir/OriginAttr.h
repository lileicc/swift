#pragma once

#include <string>

#include "Ty.h"
#include "TypeDomain.h"

namespace swift { namespace ir {

class OriginAttr {
  std::string name;
  int id;
  Ty* typ;
  TypeDomain* src;
public:
  OriginAttr(std::string name, Ty* ty, TypeDomain* src, int id);
  virtual ~OriginAttr();

  std::string& getName();
  Ty* getTyp();
  int getID();
  TypeDomain* getSrc();
};

}
}