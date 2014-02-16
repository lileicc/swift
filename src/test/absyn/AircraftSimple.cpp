#include "AircraftSimple.h"

namespace test_absyn { 

using namespace swift::absyn;

AircraftSimple::AircraftSimple() :root(NULL){}

AircraftSimple::~AircraftSimple() {
  if (root != NULL) delete root;
}

BlogProgram* AircraftSimple::getRoot() {
  return root;
}

void AircraftSimple::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  type Aircraft;
  type Blip;
  */
  {
    blog->add(new TypDecl(0, 0, Symbol("Aircraft")));
    blog->add(new TypDecl(0, 0, Symbol("Blip")));
  }
  /*
  origin Aircraft Source(Blip);
  */
  {
    OriginDecl* origin = new OriginDecl(0,0,Symbol("Aircraft"),Symbol("Source"),Symbol("Blip"));
    blog->add(origin);
  }
  /*
  #Aircraft ~ Poisson(5);
  */
  {
    DistrExpr*dis;
    dis = new DistrExpr(0, 0, Symbol("Poisson"));
    dis->add(new IntLiteral(0, 0, 5));
    NumStDecl*num;
    num = new NumStDecl(0, 0, Symbol("Aircraft"), dis);
    blog->add(num);
  }
  /*
  #Blip(Source=a) ~ Poisson(4);
  */
  {
    DistrExpr*dis;
    dis = new DistrExpr(0, 0, Symbol("Poisson"));
    dis->add(new IntLiteral(0, 0, 4));
    NumStDecl*num;
    num = new NumStDecl(0, 0, Symbol("Blip"), dis);
    num->add(Symbol("Source"), Symbol("a"));
    blog->add(num);
  }
  /*
  obs {Blip b} = {b1, b2, b3};
  */
  {
    CondSet* st = new CondSet(0, 0, VarDecl(0,0,Symbol("Blip"),Symbol("b")));
    ListSet* lst = new ListSet(0,0);
    lst->add(new VarRef(0, 0, Symbol("b1")));
    lst->add(new VarRef(0, 0, Symbol("b2")));
    lst->add(new VarRef(0, 0, Symbol("b3")));
//    CardinalityExpr* num = new CardinalityExpr(0, 0, new CondSet(0, 0, VarDecl(0, 0, Symbol("Blip"))));
//    Evidence* e = new Evidence(0, 0, num, new IntLiteral(0,0,3));
    Evidence* e = new Evidence(0,0,st,lst); // Set Evidence Here!
    blog->add(e);
  }

  /*
  query #{Aircraft a};
  */
  {
    CardinalityExpr* num = new CardinalityExpr(0, 0, new CondSet(0, 0, VarDecl(0, 0, Symbol("Blip"),Symbol("a"))));
    Query* query = new Query(0,0,num);
    blog->add(query);
  }
}

void AircraftSimple::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
