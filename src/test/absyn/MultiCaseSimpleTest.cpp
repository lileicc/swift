#include "MultiCaseSimpleTest.h"

namespace test_absyn { 

using namespace swift::absyn;

MultiCaseSimpleTest::MultiCaseSimpleTest() :root(NULL){}

MultiCaseSimpleTest::~MultiCaseSimpleTest() {
  if (root != NULL) delete root;
}

BlogProgram* MultiCaseSimpleTest::getRoot() {
  return root;
}

/*
random Boolean X ~ BooleanDistr(0.1);
random Boolean Y ~ BooleanDistr(0.9);
random Integer Z ~
  case [X,Y] in {
    [true, false] -> NULL,
    [false, true] -> 3,
    [true, true] -> 2,
    [false, false] -> 1
  };
query Z;
*/

void MultiCaseSimpleTest::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  random Boolean X ~ BooleanDistr(0.1);
  */
  {
    FuncApp *dis = new FuncApp(0, 0, Symbol("BooleanDistrib"));
    dis->add(new DoubleLiteral(0, 0, 0.1));
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("Boolean"), Symbol("X"), dis);
    blog->add(fd);
  }
  /*
  random Boolean Y ~ BooleanDistr(0.9);
  */
  {
    FuncApp *dis = new FuncApp(0, 0, Symbol("BooleanDistrib"));
    dis->add(new DoubleLiteral(0, 0, 0.9));
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("Boolean"), Symbol("Y"), dis);
    blog->add(fd);
  }
  /*
  random Integer Z ~
  case [X,Y] in {
    [true, false] -> NULL,
    [false, true] -> 3,
    [true, true] -> 2,
    [false, false] -> 1
  };
  */
  {
    MapExpr* mp = new MapExpr(0,0);
    int cnt = 4;
    for (int x = 1; x >= 0; --x) {
      for (int y = 1; y >= 0; --y) {
        ArrayExpr* arr = new ArrayExpr(0,0,1);
        arr->add(new BoolLiteral(0,0,x > 0));
        arr->add(new BoolLiteral(0, 0, y > 0));
        Expr* tar;
        if (x == 1 && y == 0) tar = new NullLiteral(0, 0) ;
        else tar = new IntLiteral(0,0,--cnt);
        mp->addMap(arr, tar);
      }
    }
    ArrayExpr* test = new ArrayExpr(0,0,1);
    test->add(new FuncApp(0, 0, Symbol("X")));
    test->add(new FuncApp(0, 0, Symbol("Y")));
    CaseExpr* cs = new CaseExpr(0,0,test,mp);
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("Integer"), Symbol("Z"), cs);
    blog->add(fd);
  }
  /*
  query Z;
  */
  {
    blog->add(new Query(0, 0, new FuncApp(0, 0, Symbol("Z"))));
  }
}

void MultiCaseSimpleTest::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
