#include "ListSet.h"

namespace swift { namespace ir {

ListSet::ListSet()
  :SetExpr(IRConstant::LISTSET) {
}

ListSet::~ListSet() {
}

}
}