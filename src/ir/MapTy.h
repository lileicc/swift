#pragma once

#include "IRForwardDecl.h"
#include "Ty.h"

namespace swift {
namespace ir {

class MapTy :public swift::ir::Ty {
public:
  MapTy(const Ty* from, const Ty* to);
  virtual ~MapTy();

  const Ty* getFrom() const;
  const Ty* getTo() const;

  virtual std::string toString() const ;

private:
  const Ty* from;
  const Ty* to;
};

}
}