#include "DirichletSimpleTest.h"

namespace test_absyn { 

using namespace swift::absyn;

DirichletSimpleTest::DirichletSimpleTest() :root(NULL){}

DirichletSimpleTest::~DirichletSimpleTest() {
  if (root != NULL) delete root;
}

BlogProgram* DirichletSimpleTest::getRoot() {
  return root;
}

/*
random Real[] w ~ Dirichlet(1.0, 2.0, 3.0);
random Integer x ~ Discrete(w);
query x;
*/

void DirichletSimpleTest::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  random Real[] w ~ Dirichlet(1.0, 2.0, 3.0);
  */
  {
    DistrExpr *dis = new DistrExpr(0, 0, Symbol("Dirichlet"));
    dis->add(new DoubleLiteral(0, 0, 1.0));
    dis->add(new DoubleLiteral(0, 0, 2.0));
    dis->add(new DoubleLiteral(0, 0, 3.0));
    FuncDecl *fd = new FuncDecl(0, 0, true, Ty(Symbol("Real"),1), Symbol("w"), dis);
    blog->add(fd);
  }
  /*
  random Integer x ~ Discrete(w);
  */
  {
    DistrExpr *dis = new DistrExpr(0, 0, Symbol("Discrete"));
    dis->add(new FuncApp(0, 0, Symbol("w")));
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("Integer"), Symbol("x"), dis);
    blog->add(fd);
  }
  /*
  query x;
  */
  {
    blog->add(new Query(0, 0, new FuncApp(0, 0, Symbol("x"))));
  }
}

void DirichletSimpleTest::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
