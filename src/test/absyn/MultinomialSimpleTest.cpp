#include "MultinomialSimpleTest.h"

namespace test_absyn { 

using namespace swift::absyn;

MultinomialSimpleTest::MultinomialSimpleTest() :root(NULL){}

MultinomialSimpleTest::~MultinomialSimpleTest() {
  if (root != NULL) delete root;
}

BlogProgram* MultinomialSimpleTest::getRoot() {
  return root;
}

/*
fixed Integer[] A = [0,1,2,3,4];
random Integer[] B ~ Multinomial([0.1,0.1,0.2,0.3,0.3]);
query A[0] == B[0];
query B;
*/

void MultinomialSimpleTest::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  fixed Integer[] A = [0,1,2,3,4];
  */
  {
    ArrayExpr* arr = new ArrayExpr(0,0,1);
    for (int i = 0; i < 5; ++ i)
      arr->add(new IntLiteral(0,0,i));
    FuncDecl *fd = new FuncDecl(0, 0, false, Ty(0,0,Symbol("Integer"),1), Symbol("A"), arr);
    blog->add(fd);
  }
  /*
  random Integer[] B ~ Multinomial([0.1,0.1,0.2,0.3,0.3]);
  */
  {
    ArrayExpr*arr = new ArrayExpr(0, 0, 1);
    double val[5] = { 0.1, 0.1, 0.2, 0.3, 0.3 };
    for (int i = 0; i < 5; ++i)
      arr->add(new DoubleLiteral(0, 0, val[i]));
    FuncApp *dis = new FuncApp(0, 0, Symbol("Multinomial"));
    dis->add(arr);
    FuncDecl *fd = new FuncDecl(0, 0, true, Ty(0, 0, Symbol("Integer"), 1), Symbol("B"), dis);
    blog->add(fd);
  }
  /*
  query A[0] == B[0];
  */
  {
    OpExpr* subA = new OpExpr(0, 0, AbsynConstant::SUB, new FuncApp(0, 0, Symbol("A")), new IntLiteral(0,0,0));
    OpExpr* subB = new OpExpr(0, 0, AbsynConstant::SUB, new FuncApp(0, 0, Symbol("B")), new IntLiteral(0, 0, 0));
    OpExpr* opr = new OpExpr(0,0,AbsynConstant::EQ,subA, subB);
    blog->add(new Query(0,0,opr));
  }
  /*
  query B;
  */
  {
    blog->add(new Query(0, 0, new FuncApp(0, 0, Symbol("B"))));
  }
}

void MultinomialSimpleTest::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
