#include "MatrixTest.h"

#include <string>
using namespace std;

namespace test_absyn { 

using namespace swift::absyn;

MatrixTest::MatrixTest() :root(NULL){}

MatrixTest::~MatrixTest() {
  if (root != NULL) delete root;
}

BlogProgram* MatrixTest::getRoot() {
  return root;
}

/*
fixed Real x = 1;
fixed Real y = 0;
fixed Real z = -1;
fixed RealMatrix A = [x,y,z];
fixed RealMatrix B = [x;y;z];
fixed RealMatrix W = [1,0.0,0;0.0,1,0;0.0,0,1];

fixed Real scale(Real k) = A * transpose(A) * k;

random RealMatrix C ~ MultivarGaussian(B,W);
random RealMatrix D ~ MultivarGaussian([3.0;3.0;3.0],W);

obs D = vstack(2,2,2);

query scale(1.5);
query C[0];
query D[0] + (B * A)[0][0];
*/

void MatrixTest::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  fixed Real x = 1;
  fixed Real y = 0;
  fixed Real z = -1;
  */
  {
    int val = 1;
    for (char c = 'x'; c <= 'z'; ++c, --val) {
      std::string var;
      var.push_back(c);
      FuncDecl *fd = new FuncDecl(0, 0, false, Symbol("Real"), Symbol(var),
                new IntLiteral(0,0,val));
      blog->add(fd);
    }
  }
  /*
  fixed RealMatrix A = [x,y,z];
  */
  {
    ArrayExpr* mat = new ArrayExpr(0,0,1);
    mat->add(new FuncApp(0, 0, Symbol("x")));
    mat->add(new FuncApp(0, 0, Symbol("y")));
    mat->add(new FuncApp(0, 0, Symbol("z")));
    FuncDecl *fd = new FuncDecl(0, 0, false, Symbol("RealMatrix"), Symbol("A"), mat);
    blog->add(fd);
  }
  /*
  fixed RealMatrix B = [x;y;z];
  */
  {
    ArrayExpr* mat = new ArrayExpr(0, 0, 2);
    for (char c = 'x'; c <= 'z'; ++c) {
      ArrayExpr* row = new ArrayExpr(0,0,1);
      string v; v.push_back(c);
      row->add(new FuncApp(0,0,Symbol(v)));
      mat->add(row);
    }
    FuncDecl *fd = new FuncDecl(0, 0, false, Symbol("RealMatrix"), Symbol("B"), mat);
    blog->add(fd);
  }
  /*
  fixed RealMatrix W = [1,0.0,0;0.0,1,0;0.0,0,1];
  */
  {
    ArrayExpr* mat = new ArrayExpr(0, 0, 2);
    for (int i = 0; i < 3; ++i) {
      ArrayExpr* row = new ArrayExpr(0,0,1);
      for (int j = 0; j < 3; ++j) {
        if (j == i)
          row->add(new DoubleLiteral(0,0,1.0));
        else
          row->add(new IntLiteral(0,0,0));
      }
      mat->add(row);
    }
    FuncDecl *fd = new FuncDecl(0, 0, false, Symbol("RealMatrix"), Symbol("W"), mat);
    blog->add(fd);
  }
  /*
  fixed Real scale(Real k) = A * transpose(A) * k;
  */
  {
    FuncApp* trs = new FuncApp(0, 0, Symbol("transpose"));
    trs->add(new FuncApp(0, 0, Symbol("A")));
    OpExpr* sub = new OpExpr(0, 0, AbsynConstant::MUL, new FuncApp(0, 0, Symbol("A")), trs);
    OpExpr* expr = new OpExpr(0, 0, AbsynConstant::MUL, sub, new FuncApp(0, 0, Symbol("k")));
    FuncDecl *fd = new FuncDecl(0, 0, false, Symbol("Real"), Symbol("scale"), expr);
    fd->addArg(VarDecl(0, 0, Symbol("Real"), Symbol("k")));
    blog->add(fd);
  }
  /*
  random RealMatrix C ~ MultivarGaussian(B,W);
  */
  {
    FuncApp* distr = new FuncApp(0, 0, Symbol("MultivarGaussian"));
    distr->add(new FuncApp(0,0,Symbol("B")));
    distr->add(new FuncApp(0, 0, Symbol("W")));
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("RealMatrix"), Symbol("C"), distr);
    blog->add(fd);
  }
  /*
  random RealMatrix D ~ MultivarGaussian([3.0;3.0;3.0],W);
  */
  {
    FuncApp* distr = new FuncApp(0, 0, Symbol("MultivarGaussian"));
    ArrayExpr* mat = new ArrayExpr(0, 0, 2);
    for (int i = 0; i < 3; ++i) {
      ArrayExpr* row = new ArrayExpr(0, 0, 1);
      row->add(new DoubleLiteral(0, 0, 3));
      mat->add(row);
    }
    distr->add(mat);
    distr->add(new FuncApp(0, 0, Symbol("W")));
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("RealMatrix"), Symbol("D"), distr);
    blog->add(fd);
  }
  /*
  obs D = vstack(2,2,2);
  */
  {
    FuncApp* vs = new FuncApp(0, 0, Symbol("vstack"));
    for (int i = 0; i < 3; ++i) {
      vs->add(new IntLiteral(0,0,2));
    }
    Evidence* obs = new Evidence(0, 0, new FuncApp(0, 0, Symbol("D")), vs);
    blog->add(obs);
  }
  /*
  query scale(1.5);
  */
  {
    FuncApp* func = new FuncApp(0, 0, Symbol("scale"));
    func->add(new DoubleLiteral(0, 0, 1.5));
    Query* query = new Query(0, 0, func);
    blog->add(query);
  }
  /*
  query C[0];
  */
  {
    OpExpr* expr = new OpExpr(0,0,AbsynConstant::SUB,
      new FuncApp(0, 0, Symbol("C")), new IntLiteral(0,0,0));
    Query* query = new Query(0, 0, expr);
    blog->add(query);
  }
  /*
  query D[0] + (B * A)[0][0];
  */
  {
    OpExpr* mul = new OpExpr(0, 0, AbsynConstant::MUL,
      new FuncApp(0,0,Symbol("B")), new FuncApp(0,0,Symbol("A")));
    OpExpr* sub = new OpExpr(0, 0, AbsynConstant::SUB,
      mul, new IntLiteral(0, 0, 0));
    OpExpr* rt = new OpExpr(0,0,AbsynConstant::SUB,
      sub, new IntLiteral(0,0,0));
    OpExpr* lt = new OpExpr(0,0,AbsynConstant::SUB,
      new FuncApp(0,0,Symbol("D")), new IntLiteral(0,0,0));
    OpExpr* expr = new OpExpr(0, 0, AbsynConstant::PLUS, lt, rt);
    Query* query = new Query(0, 0, expr);
    blog->add(query);
  }
}

void MatrixTest::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
