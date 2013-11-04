#pragma once

#include <string>

#include "Ty.h"
//#include "TypeDomain.h"

namespace swift { namespace ir {
class TypeDomain;

class OriginAttr {
  std::string name;
  int id;
  Ty* typ;
  TypeDomain* src;
public:
  OriginAttr(std::string name, Ty* ty, TypeDomain* src);
  virtual ~OriginAttr();

  const std::string& getName();
  Ty* getTyp();
  void setID(int k);
  int getID();
  TypeDomain* getSrc();
};

}
}