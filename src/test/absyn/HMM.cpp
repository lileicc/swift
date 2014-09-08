#include "HMM.h"

namespace test_absyn { 

using namespace swift::absyn;

HMM::HMM() :root(NULL){}

HMM::~HMM() {
  if (root != NULL) delete root;
}

BlogProgram* HMM::getRoot() {
  return root;
}

void HMM::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  type State;
  type Output;
  distinct Output ResultA, ResultC, ResultG, ResultT;
  */
  {
    blog->add(new TypDecl(1, 0, Symbol("State")));
    blog->add(new TypDecl(2, 0, Symbol("Output")));
  }
  /*
  distinct State A, C, G, T;
  distinct Output ResultA, ResultC, ResultG, ResultT;
  */
  {
    DistinctDecl*dis;
    dis = new DistinctDecl(3, 0, Symbol("State"));
    dis->add(Symbol("A"), 1);
    dis->add(Symbol("C"), 1);
    dis->add(Symbol("G"), 1);
    dis->add(Symbol("T"), 1);
    blog->add(dis);
    dis = new DistinctDecl(4, 0, Symbol("Output"));
    dis->add(Symbol("ResultA"), 1);
    dis->add(Symbol("ResultC"), 1);
    dis->add(Symbol("ResultG"), 1);
    dis->add(Symbol("ResultT"), 1);
    blog->add(dis);
  }
  /*
  random State S(Timestep t) ~
    if t == @0 then Categorical({A -> 0.3,
                 C -> 0.2, 
                 G -> 0.1, 
                 T -> 0.4})
    else Case S(prev(t)) in 
      {A -> Categorical({A -> 0.1, C -> 0.3, G -> 0.3, T -> 0.3}),
       C -> Categorical({A -> 0.3, C -> 0.1, G -> 0.3, T -> 0.3}),
       G -> Categorical({A -> 0.3, C -> 0.3, G -> 0.1, T -> 0.3}),
       T -> Categorical({A -> 0.3, C -> 0.3, G -> 0.3, T -> 0.1})};
  */
  {
    Expr *cond, *thn, *els;
    { // Cond
      OpExpr *eq = new OpExpr(0, 0, AbsynConstant::EQ,
        new VarRef(0, 0, Symbol("t")), new TimeStampLiteral(0,0,0));

      cond = eq;
    }
    { // Then Clause
      MapExpr *map = new MapExpr(0, 0);
      map->addMap(new VarRef(0, 0, Symbol("A")), new DoubleLiteral(0, 0, 0.3));
      map->addMap(new VarRef(0, 0, Symbol("C")), new DoubleLiteral(0, 0, 0.2));
      map->addMap(new VarRef(0, 0, Symbol("G")), new DoubleLiteral(0, 0, 0.1));
      map->addMap(new VarRef(0, 0, Symbol("T")), new DoubleLiteral(0, 0, 0.4));
      DistrExpr *cat = new DistrExpr(0, 0, Symbol("Categorical"));
      cat->add(map);

      thn = cat;
    }
    { // Else Clause
      MapExpr *map_A = new MapExpr(0, 0);
      map_A->addMap(new VarRef(0, 0, Symbol("A")), new DoubleLiteral(0, 0, 0.1));
      map_A->addMap(new VarRef(0, 0, Symbol("C")), new DoubleLiteral(0, 0, 0.3));
      map_A->addMap(new VarRef(0, 0, Symbol("G")), new DoubleLiteral(0, 0, 0.3));
      map_A->addMap(new VarRef(0, 0, Symbol("T")), new DoubleLiteral(0, 0, 0.3));
      DistrExpr *cat_A = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_A->add(map_A);
      MapExpr *map_C = new MapExpr(0, 0);
      map_C->addMap(new VarRef(0, 0, Symbol("A")), new DoubleLiteral(0, 0, 0.3));
      map_C->addMap(new VarRef(0, 0, Symbol("C")), new DoubleLiteral(0, 0, 0.1));
      map_C->addMap(new VarRef(0, 0, Symbol("G")), new DoubleLiteral(0, 0, 0.3));
      map_C->addMap(new VarRef(0, 0, Symbol("T")), new DoubleLiteral(0, 0, 0.3));
      DistrExpr *cat_C = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_C->add(map_C);
      MapExpr *map_G = new MapExpr(0, 0);
      map_G->addMap(new VarRef(0, 0, Symbol("A")), new DoubleLiteral(0, 0, 0.3));
      map_G->addMap(new VarRef(0, 0, Symbol("C")), new DoubleLiteral(0, 0, 0.3));
      map_G->addMap(new VarRef(0, 0, Symbol("G")), new DoubleLiteral(0, 0, 0.1));
      map_G->addMap(new VarRef(0, 0, Symbol("T")), new DoubleLiteral(0, 0, 0.3));
      DistrExpr *cat_G = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_G->add(map_G);
      MapExpr *map_T = new MapExpr(0, 0);
      map_T->addMap(new VarRef(0, 0, Symbol("A")), new DoubleLiteral(0, 0, 0.3));
      map_T->addMap(new VarRef(0, 0, Symbol("C")), new DoubleLiteral(0, 0, 0.3));
      map_T->addMap(new VarRef(0, 0, Symbol("G")), new DoubleLiteral(0, 0, 0.3));
      map_T->addMap(new VarRef(0, 0, Symbol("T")), new DoubleLiteral(0, 0, 0.1));
      DistrExpr *cat_T = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_T->add(map_T);
      MapExpr *map_S = new MapExpr(0, 0);
      map_S->addMap(new VarRef(0, 0, Symbol("A")), cat_A);
      map_S->addMap(new VarRef(0, 0, Symbol("C")), cat_C);
      map_S->addMap(new VarRef(0, 0, Symbol("G")), cat_G);
      map_S->addMap(new VarRef(0, 0, Symbol("T")), cat_T);
      FuncApp *fun_prv = new FuncApp(0, 0, Symbol("prev"));
      fun_prv->add(new VarRef(0,0,Symbol("t")));
      FuncApp *fun_S = new FuncApp(0,0,Symbol("S"));
      fun_S->add(fun_prv);
      CaseExpr *cas_els = new CaseExpr(0,0,fun_S,map_S);

      els = cas_els;
    }
    IfExpr *ife = new IfExpr(0, 0, cond, thn, els);
    FuncDecl *func = new FuncDecl(0, 0, true, Symbol("State"), Symbol("S"), ife);
    func->addArg(VarDecl(0, 0, Symbol("Timestep"), Symbol("t")));

    blog->add(func);
  }
  /*
  random Output O(Timestep t)
   ~ case S(t) in 
     {A -> Categorical({ResultA -> 0.85, ResultC -> 0.05, ResultG -> 0.05, ResultT -> 0.05}),
      C -> Categorical({ResultA -> 0.05, ResultC -> 0.85, ResultG -> 0.05, ResultT -> 0.05}),
      G -> Categorical({ResultA -> 0.05, ResultC -> 0.05, ResultG -> 0.85, ResultT -> 0.05}),
      T -> Categorical({ResultA -> 0.05, ResultC -> 0.05, ResultG -> 0.05, ResultT -> 0.85})};
  */
  {
    MapExpr *map_A = new MapExpr(0, 0);
    map_A->addMap(new VarRef(0, 0, Symbol("ResultA")), new DoubleLiteral(0, 0, 0.85));
    map_A->addMap(new VarRef(0, 0, Symbol("ResultC")), new DoubleLiteral(0, 0, 0.05));
    map_A->addMap(new VarRef(0, 0, Symbol("ResultG")), new DoubleLiteral(0, 0, 0.05));
    map_A->addMap(new VarRef(0, 0, Symbol("ResultT")), new DoubleLiteral(0, 0, 0.05));
    DistrExpr *cat_A = new DistrExpr(0, 0, Symbol("Categorical"));
    cat_A->add(map_A);
    MapExpr *map_C = new MapExpr(0, 0);
    map_C->addMap(new VarRef(0, 0, Symbol("ResultA")), new DoubleLiteral(0, 0, 0.05));
    map_C->addMap(new VarRef(0, 0, Symbol("ResultC")), new DoubleLiteral(0, 0, 0.85));
    map_C->addMap(new VarRef(0, 0, Symbol("ResultG")), new DoubleLiteral(0, 0, 0.05));
    map_C->addMap(new VarRef(0, 0, Symbol("ResultT")), new DoubleLiteral(0, 0, 0.05));
    DistrExpr *cat_C = new DistrExpr(0, 0, Symbol("Categorical"));
    cat_C->add(map_C);
    MapExpr *map_G = new MapExpr(0, 0);
    map_G->addMap(new VarRef(0, 0, Symbol("ResultA")), new DoubleLiteral(0, 0, 0.05));
    map_G->addMap(new VarRef(0, 0, Symbol("ResultC")), new DoubleLiteral(0, 0, 0.05));
    map_G->addMap(new VarRef(0, 0, Symbol("ResultG")), new DoubleLiteral(0, 0, 0.85));
    map_G->addMap(new VarRef(0, 0, Symbol("ResultT")), new DoubleLiteral(0, 0, 0.05));
    DistrExpr *cat_G = new DistrExpr(0, 0, Symbol("Categorical"));
    cat_G->add(map_G);
    MapExpr *map_T = new MapExpr(0, 0);
    map_T->addMap(new VarRef(0, 0, Symbol("ResultA")), new DoubleLiteral(0, 0, 0.05));
    map_T->addMap(new VarRef(0, 0, Symbol("ResultC")), new DoubleLiteral(0, 0, 0.05));
    map_T->addMap(new VarRef(0, 0, Symbol("ResultG")), new DoubleLiteral(0, 0, 0.05));
    map_T->addMap(new VarRef(0, 0, Symbol("ResultT")), new DoubleLiteral(0, 0, 0.85));
    DistrExpr *cat_T = new DistrExpr(0, 0, Symbol("Categorical"));
    cat_T->add(map_T);
    MapExpr *map_S = new MapExpr(0, 0);
    map_S->addMap(new VarRef(0, 0, Symbol("A")), cat_A);
    map_S->addMap(new VarRef(0, 0, Symbol("C")), cat_C);
    map_S->addMap(new VarRef(0, 0, Symbol("G")), cat_G);
    map_S->addMap(new VarRef(0, 0, Symbol("T")), cat_T);
    FuncApp *fun_S = new FuncApp(0, 0, Symbol("S"));
    fun_S->add(new VarRef(0, 0, Symbol("t")));
    CaseExpr *cas = new CaseExpr(0,0,fun_S,map_S);

    FuncDecl* func = new FuncDecl(0, 0, true, Symbol("Output"), Symbol("O"), cas);
    func->addArg(VarDecl(0, 0, Symbol("Timestep"), Symbol("t")));
    blog->add(func);
  }
  /*
  obs O(@0) = ResultC;
  obs O(@1) = ResultA;
  obs O(@2) = ResultA;
  obs O(@3) = ResultA;
  obs O(@4) = ResultG;
  */
  {
    FuncApp *o;
    Evidence *obs;
    o = new FuncApp(0, 0, Symbol("O"));
    o->add(new TimeStampLiteral(0,0,0));
    obs = new Evidence(0, 0, o, new VarRef(0, 0, Symbol("ResultC")));
    blog->add(obs);
    o = new FuncApp(0, 0, Symbol("O"));
    o->add(new TimeStampLiteral(0, 0, 1));
    obs = new Evidence(0, 0, o, new VarRef(0, 0, Symbol("ResultA")));
    blog->add(obs);
    o = new FuncApp(0, 0, Symbol("O"));
    o->add(new TimeStampLiteral(0, 0, 2));
    obs = new Evidence(0, 0, o, new VarRef(0, 0, Symbol("ResultA")));
    blog->add(obs);
    o = new FuncApp(0, 0, Symbol("O"));
    o->add(new TimeStampLiteral(0, 0, 3));
    obs = new Evidence(0, 0, o, new VarRef(0, 0, Symbol("ResultA")));
    blog->add(obs);
    o = new FuncApp(0, 0, Symbol("O"));
    o->add(new TimeStampLiteral(0, 0, 4));
    obs = new Evidence(0, 0, o, new VarRef(0, 0, Symbol("ResultG")));
    blog->add(obs);
  }
  /*
  query S(@0);
  query S(@1);
  query S(@2);
  query S(@3);
  query S(@4);
  query S(@5);
  */
  {
    for (int i = 0; i <= 5; ++i) {
      FuncApp *fun_S = new FuncApp(0, 0, Symbol("S"));
      fun_S->add(new TimeStampLiteral(0,0,i));
      blog->add(new Query(0,0,fun_S));
    }
  }
}

void HMM::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
