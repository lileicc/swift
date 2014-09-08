#include "Birthday.h"

namespace test_absyn { 

using namespace swift::absyn;

Birthday::Birthday() :root(NULL){}

Birthday::~Birthday() {
  if (root != NULL) delete root;
}

BlogProgram* Birthday::getRoot() {
  return root;
}

void Birthday::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  type Person;
  type Date;
  */
  {
    blog->add(new TypDecl(0, 0, Symbol("Person")));
    blog->add(new TypDecl(0, 0, Symbol("Date")));
  }
  /*
  distinct Date Day[365];
  */
  {
    DistinctDecl*dis;
    dis = new DistinctDecl(0, 0, Symbol("Date"));
    dis->add(Symbol("Day"), 365);
    blog->add(dis);
  }
  /*
  #Person ~ Poisson(13);
  */
  {
    DistrExpr*dis;
    dis = new DistrExpr(0, 0, Symbol("Poisson"));
    dis->add(new IntLiteral(0, 0, 13));
    NumStDecl*num;
    num = new NumStDecl(0, 0, Symbol("Person"), dis);
    blog->add(num);
  }
  /*
  random Date Birthday(Person p) ~ UniformChoice({d for Date d});
  */
  {
    SetExpr*st;
    st = new TupleSetExpr(0, 0, 
      std::vector<Expr*>({new VarRef(0,0,Symbol("d"))}),
      std::vector<VarDecl>({ VarDecl(0, 0, Symbol("Date"), Symbol("d")) }), NULL);
    DistrExpr*uc;
    uc = new DistrExpr(0, 0, Symbol("UniformChoice"));
    uc->add(st);
    FuncDecl*fun;
    fun = new FuncDecl(0, 0, true, Symbol("Date"), Symbol("Birthday"), uc);
    fun->addArg(VarDecl(0, 0, Symbol("Person"), Symbol("p")));
    blog->add(fun);
  }
  /*
  obs size({p for Person p}) = 23;
  */
  {
    TupleSetExpr* tset = new TupleSetExpr(0, 0, 
      std::vector<Expr*>({new VarRef(0,0,Symbol("p"))}),
      std::vector<VarDecl>({VarDecl(0,0,Symbol("Person"),Symbol("p"))}),NULL);
    FuncApp* lft = new FuncApp(0,0,Symbol("size"));
    lft->add(tset);
    IntLiteral* rght = new IntLiteral(0, 0, 23);
    Evidence* evi = new Evidence(0, 0, lft, rght);
    blog->add(evi);
  }
  /*
  query exists Person x exists Person y
  ((x != y) & (Birthday(x) == Birthday(y)));
  */
  {
    // x != y
    OpExpr* lft = new OpExpr(0, 0, AbsynConstant::NEQ, new VarRef(0, 0, Symbol("x")), new VarRef(0, 0, Symbol("y")));
    // Birthday(x) == Birthday(y)
    FuncApp* bth_x = new FuncApp(0, 0, Symbol("Birthday"));
    bth_x->add(new VarRef(0, 0, Symbol("x")));
    FuncApp* bth_y = new FuncApp(0, 0, Symbol("Birthday"));
    bth_y->add(new VarRef(0, 0, Symbol("y")));
    OpExpr* rght = new OpExpr(0,0,AbsynConstant::EQ,bth_x,bth_y);

    OpExpr* cond = new OpExpr(0,0,AbsynConstant::AND,lft,rght);
    // exists Person y
    QuantExpr* ext_y = new QuantExpr(0, 0, AbsynConstant::EXISTS, VarDecl(0, 0, Symbol("Person"), Symbol("y")), cond);
    // exists Person x
    QuantExpr* ext_x = new QuantExpr(0, 0, AbsynConstant::EXISTS, VarDecl(0, 0, Symbol("Person"), Symbol("x")), ext_y);
    // query
    Query* qry = new Query(0, 0, ext_x);
    
    blog->add(qry);
  }
}

void Birthday::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
