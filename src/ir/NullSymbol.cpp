#include "NullSymbol.h"

#include "IRConst.h"

namespace swift {
namespace ir {

NullSymbol::NullSymbol() :
    ConstSymbol(IRConstant::NULLSYMBOL) {
}

NullSymbol::~NullSymbol() {
}

void NullSymbol::print(FILE* file, int indent){
  fprintf(file, "%*sNullSymbol\n", indent, "");
}

}
}
