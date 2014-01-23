#include "MapExpr.h"
#include "Ty.h"

namespace swift { namespace ir {

MapExpr::MapExpr() : fromTyp(NULL), toTyp(NULL) {
}

MapExpr::~MapExpr() {
}

size_t MapExpr::mapSize() const {
  return argSize() / 2;
}

void MapExpr::addMap(std::shared_ptr<Expr> a, std::shared_ptr<Expr> b) {
  addArg(a);
  addArg(b);
}

std::shared_ptr<Expr> MapExpr::getFrom(size_t k) const {
  return get(2 * k);
}

std::shared_ptr<Expr> MapExpr::getTo(size_t k) const {
  return get(2 * k + 1);
}

const Ty* MapExpr::getFromTyp() const {
  return fromTyp;
}

const Ty* MapExpr::getToTyp() const {
  return toTyp;
}

void MapExpr::setFromTyp(const Ty * t) {
  fromTyp = t;
}

void MapExpr::setToTyp(const Ty * t) {
  toTyp = t;
}

void MapExpr::print(FILE* file, int indent){
  fprintf(file, "%*s(MapExpr:\n", indent, "");
  fprintf(file, "%*s:fromTyp: %s", indent+2, "", getFromTyp()->toString().c_str());
  fprintf(file, "%*s:toTyp: %s", indent+2, "", getToTyp()->toString().c_str());
  for (size_t i = 0; i < mapSize(); i++) {
    fprintf(file, "%*s:from#%d\n", indent + 2, "", i);
    getFrom(i)->print(file, indent + 4);
    fprintf(file, "%*s:to#%d\n", indent + 2, "", i);
    getTo(i)->print(file, indent + 4);
  }
  fprintf(file, "%*s)\n", indent, "");
}

}
}