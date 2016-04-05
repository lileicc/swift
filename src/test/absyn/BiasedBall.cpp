#include "BiasedBall.h"

namespace test_absyn { 

using namespace swift::absyn;

BiasedBall::BiasedBall() :root(NULL){}

BiasedBall::~BiasedBall() {
  if (root != NULL) delete root;
}

BlogProgram* BiasedBall::getRoot() {
  return root;
}

void BiasedBall::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  type Ball;
  type Draw;
  type Color;
  */
  {
    blog->add(new TypDecl(0, 0, Symbol("Ball")));
    blog->add(new TypDecl(0, 0, Symbol("Draw")));
    blog->add(new TypDecl(0, 0, Symbol("Color")));
  }
  /*
  distinct Color Blue, Green;
  distinct Draw Draw[10];
  */
  {
    DistinctDecl*dis;
    dis = new DistinctDecl(0, 0, Symbol("Color"));
    dis->add(Symbol("Blue"), 1);
    dis->add(Symbol("Green"), 1);
    blog->add(dis);
    dis = new DistinctDecl(0, 0, Symbol("Draw"));
    dis->add(Symbol("Draw"), 10);
    blog->add(dis);
  }
  /*
  #Ball ~ UniformInt(1,20);
  */
  {
    FuncApp*dis;
    dis = new FuncApp(0, 0, Symbol("UniformInt"));
    dis->add(new IntLiteral(0, 0, 1));
    dis->add(new IntLiteral(0, 0, 20));
    NumStDecl*num;
    num = new NumStDecl(0, 0, Symbol("Ball"), dis);
    blog->add(num);
  }
  /*
  random Color TrueColor(Ball b) ~ Categorical({Blue -> 0.9, Green -> 0.1});
  */
  {
    FuncApp*cate;
    {
      MapExpr* mp;
      mp = new MapExpr(0, 0);
      mp->addMap(new FuncApp(0, 0, Symbol("Blue")), new DoubleLiteral(0, 0, 0.9));
      mp->addMap(new FuncApp(0, 0, Symbol("Green")), new DoubleLiteral(0, 0, 0.1));
      cate = new FuncApp(0, 0, Symbol("Categorical"));
      cate->add(mp);
    }
    FuncDecl*fun;
    fun = new FuncDecl(0, 0, true, Symbol("Color"), Symbol("TrueColor"), cate);
    fun->addArg(VarDecl(0, 0, Symbol("Ball"), Symbol("b")));
    blog->add(fun);
  }
  /*
  random Ball BallDrawn(Draw d) ~UniformChoice({ b for Ball b });
  */
  {
    SetExpr*st;
    st = new TupleSetExpr(0, 0, 
      std::vector<Expr*>({ new FuncApp(0, 0, Symbol("b")) }),
      std::vector<VarDecl>({ VarDecl(0, 0, Symbol("Ball"), Symbol("b")) }), NULL);
    FuncApp*uc;
    uc = new FuncApp(0, 0, Symbol("UniformChoice"));
    uc->add(st);
    FuncDecl*fun;
    fun = new FuncDecl(0, 0, true, Symbol("Ball"), Symbol("BallDrawn"), uc);
    fun->addArg(VarDecl(0, 0, Symbol("Draw"), Symbol("d")));
    blog->add(fun);
  }
  /*
  random Color ObsColor(Draw d) ~
    case TrueColor(BallDrawn(d)) in 
    {Blue -> ~ Categorical({Blue -> 0.9, Green -> 0.1}),
    Green -> ~ Categorical({Blue -> 0.1, Green -> 0.9})};
  */
  {
    FuncApp* ball_draw;
    ball_draw = new FuncApp(0, 0, Symbol("BallDrawn"));
    ball_draw->add(new FuncApp(0, 0, Symbol("d")));
    CaseExpr*cas = NULL;
    {
      MapExpr* mp = new MapExpr(0,0);
      {
        MapExpr*sub1 = new MapExpr(0,0);
        sub1->addMap(new FuncApp(0, 0, Symbol("Blue")), new DoubleLiteral(0, 0, 0.9));
        sub1->addMap(new FuncApp(0, 0, Symbol("Green")), new DoubleLiteral(0, 0, 0.1));
        FuncApp*cate1 = new FuncApp(0,0,Symbol("Categorical"));
        cate1->add(sub1);

        MapExpr*sub2 = new MapExpr(0, 0);
        sub2->addMap(new FuncApp(0, 0, Symbol("Blue")), new DoubleLiteral(0, 0, 0.1));
        sub2->addMap(new FuncApp(0, 0, Symbol("Green")), new DoubleLiteral(0, 0, 0.9));
        FuncApp*cate2 = new FuncApp(0, 0, Symbol("Categorical"));
        cate2->add(sub2);

        mp->addMap(new FuncApp(0, 0, Symbol("Blue")), cate1);
        mp->addMap(new FuncApp(0, 0, Symbol("Green")), cate2);
      }
      FuncApp* ball_draw;
      ball_draw = new FuncApp(0, 0, Symbol("BallDrawn"));
      ball_draw->add(new FuncApp(0, 0, Symbol("d")));
      FuncApp* true_color;
      true_color = new FuncApp(0, 0, Symbol("TrueColor"));
      true_color->add(ball_draw);
      
      cas = new CaseExpr(0,0,true_color,mp);
    }
    FuncDecl*fun;
    fun = new FuncDecl(0, 0, true, Symbol("Color"), Symbol("ObsColor"), cas);
    fun->addArg(VarDecl(0, 0, Symbol("Draw"), Symbol("d")));

    blog->add(fun);
  }
  /*
  obs ObsColor(Draw[0]) = Blue;
  obs ObsColor(Draw[1]) = Green;
  obs ObsColor(Draw[2]) = Green;
  obs ObsColor(Draw[3]) = Green;
  obs ObsColor(Draw[4]) = Green;
  obs ObsColor(Draw[5]) = Green;
  obs ObsColor(Draw[6]) = Green;
  obs ObsColor(Draw[7]) = Green;
  obs ObsColor(Draw[8]) = Green;
  obs ObsColor(Draw[9]) = Green;
  */
  for (int k = 0; k < 10; ++k) {
    OpExpr* ball = new OpExpr(0, 0, AbsynConstant::SUB, new FuncApp(0, 0, Symbol("Draw")), new IntLiteral(0, 0, k));
    FuncApp* fun = new FuncApp(0, 0, Symbol("ObsColor"));
    fun->add(ball);
    Evidence* e = new Evidence(0, 0, fun, new FuncApp(0, 0, Symbol(k >= 1 ? "Green" : "Blue")));

    blog->add(e);
  }

  /*
  query size({b for Ball b});
  */
  {
    TupleSetExpr* st = new TupleSetExpr(0, 0, 
      std::vector<Expr*>({ new FuncApp(0, 0, Symbol("b")) }),
      std::vector<VarDecl>({ VarDecl(0, 0, Symbol("Ball"), Symbol("b")) }), NULL);
    FuncApp* num = new FuncApp(0,0,Symbol("size"));
    num->add(st);
    Query* query = new Query(0,0,num);
    blog->add(query);
  }
}

void BiasedBall::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
