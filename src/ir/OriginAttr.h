#pragma once

#include <string>
#include <memory>
#include "IRForwardDecl.h"

namespace swift {
namespace ir {

/**
 * Declare an origin function
 */
class OriginAttr {
public:
  /**
   * construct an origin function
   * name: string, the name of the function
   * ty: an ir Type, the return type of the origin function
   * src: TypeDomain for the argument type of origin function
   * id: indicating the index of the origin function
   */
  OriginAttr(const std::string& name, const Ty* ty,
      std::shared_ptr<TypeDomain> src, size_t id);
  virtual ~OriginAttr();

  /**
   * get the name of this origin function
   */
  const std::string& getName() const;

  /**
   * get the return type of this origin function
   */
  const Ty* getTyp() const;

  /**
   * set id of this origin function in its TypeDomain
   */
  void setID(size_t k);

  /**
   * get id of this origin function in its TypeDomain
   */
  size_t getID() const;

  /**
   * get the type domain of the argument type for this origin function
   */
  std::shared_ptr<TypeDomain> getSrc() const;

  /**
   * print the origin function
   */
  void print(FILE* file, int indent);

private:
  std::string name;
  const Ty* typ;
  std::shared_ptr<TypeDomain> src;
  size_t id;
};

}
}
