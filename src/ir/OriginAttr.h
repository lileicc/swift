#pragma once

#include <string>
#include <memory>
#include "IRForwardDecl.h"

namespace swift { namespace ir {

class OriginAttr {
public:
  OriginAttr(const std::string& name, const Ty* ty, std::shared_ptr<TypeDomain> src, size_t id);
  virtual ~OriginAttr();

  const std::string& getName() const;
  const Ty* getTyp() const;
  void setID(size_t k);
  size_t getID() const;
  std::shared_ptr<TypeDomain> getSrc() const;

private:
  std::string name;
  const Ty* typ;
  std::shared_ptr<TypeDomain> src;
  size_t id;
};

}
}
