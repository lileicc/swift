#include "Hurricane.h"

namespace test_absyn { 

using namespace swift::absyn;

Hurricane::Hurricane() :root(NULL){}

Hurricane::~Hurricane() {
  if (root != NULL) delete root;
}

BlogProgram* Hurricane::getRoot() {
  return root;
}

void Hurricane::build(){
  BlogProgram *blog = new BlogProgram(0, 0);
  root = blog;
  /*
  type City;
  type PrepLevel;
  type DamageLevel;
  */
  {
    blog->add(new TypDecl(0, 0, Symbol("City")));
    blog->add(new TypDecl(0, 0, Symbol("PrepLevel")));
    blog->add(new TypDecl(0, 0, Symbol("DamageLevel")));
  }
  /*
  distinct City A, B;
  distinct PrepLevel Low, High;
  distinct DamageLevel Severe, Mild;
  */
  {
    DistinctDecl*dis;
    dis = new DistinctDecl(0, 0, Symbol("City"));
    dis->add(Symbol("A"), 1);
    dis->add(Symbol("B"), 1);
    blog->add(dis);
    dis = new DistinctDecl(0, 0, Symbol("PrepLevel"));
    dis->add(Symbol("Low"), 1);
    dis->add(Symbol("High"), 1);
    blog->add(dis);
    dis = new DistinctDecl(0, 0, Symbol("DamageLevel"));
    dis->add(Symbol("Severe"), 1);
    dis->add(Symbol("Mild"), 1);
    blog->add(dis);
  }
  /*
  random City First  ~ UniformChoice({City c});
  */
  {
    SetExpr *se = new CondSet(0, 0, VarDecl(0, 0, Symbol("City"), Symbol("c")));
    DistrExpr *dis = new DistrExpr(0, 0, Symbol("UniformChoice"));
    dis->add(se);
    FuncDecl *fd = new FuncDecl(0, 0, true, Symbol("City"), Symbol("First"), dis);
    blog->add(fd);
  }
  /*
  random PrepLevel Prep(City c) {
  if (First == c) then  ~ Categorical({High -> 0.5, Low -> 0.5})
  else  ~ TabularCPD({Severe ->  ~ Categorical({High -> 0.9, Low -> 0.1}),
  Mild ->  ~ Categorical({High -> 0.1, Low -> 0.9})},
  Damage(First))
  };
  */
  {
    Expr *cond, *thn, *els;
    { // Cond
      OpExpr *eq = new OpExpr(0, 0, AbsynConstant::EQ,
        new VarRef(0, 0, Symbol("First")), new VarRef(0, 0, Symbol("c")));

      cond = eq;
    }
    { // Then Clause
      MapExpr *map = new MapExpr(0, 0);
      map->addMap(new VarRef(0, 0, Symbol("High")), new DoubleLiteral(0, 0, 0.5));
      map->addMap(new VarRef(0, 0, Symbol("Low")), new DoubleLiteral(0, 0, 0.5));
      DistrExpr *cat = new DistrExpr(0, 0, Symbol("Categorical"));
      cat->add(map);

      thn = cat;
    }
    { // Else Clause
      FuncApp *dam_f = new FuncApp(0, 0, Symbol("Damage"));
      dam_f->add(new VarRef(0, 0, Symbol("First")));
      MapExpr *map_s = new MapExpr(0, 0);
      map_s->addMap(new VarRef(0, 0, Symbol("High")), new DoubleLiteral(0, 0, 0.9));
      map_s->addMap(new VarRef(0, 0, Symbol("Low")), new DoubleLiteral(0, 0, 0.1));
      DistrExpr *cat_s = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_s->add(map_s);
      MapExpr *map_m = new MapExpr(0, 0);
      map_m->addMap(new VarRef(0, 0, Symbol("High")), new DoubleLiteral(0, 0, 0.1));
      map_m->addMap(new VarRef(0, 0, Symbol("Low")), new DoubleLiteral(0, 0, 0.9));
      DistrExpr *cat_m = new DistrExpr(0, 0, Symbol("Categorical"));
      cat_m->add(map_m);
      MapExpr *map_t = new MapExpr(0, 0);
      map_t->addMap(new VarRef(0, 0, Symbol("Severe")), cat_s);
      map_t->addMap(new VarRef(0, 0, Symbol("Mild")), cat_m);
      DistrExpr *tab_els = new DistrExpr(0, 0, Symbol("TabularCPD"));
      tab_els->add(map_t);
      tab_els->add(dam_f);

      els = tab_els;
    }
    IfExpr *ife = new IfExpr(0, 0, cond, thn, els);
    FuncDecl *func = new FuncDecl(0, 0, true, Symbol("PrepLevel"), Symbol("Prep"), ife);
    func->addArg(VarDecl(0, 0, Symbol("City"), Symbol("c")));

    blog->add(func);
  }
  /*
  random DamageLevel Damage(City c) {
  ~ TabularCPD({High ->  ~ Categorical({Severe -> 0.2, Mild -> 0.8}),
  Low ->  ~ Categorical({Severe -> 0.8, Mild -> 0.2})},
  Prep(c))
  };
  */
  {
    DistrExpr *cat_h = new DistrExpr(0, 0, Symbol("Categorical"));
    MapExpr *map_h = new MapExpr(0, 0);
    map_h->addMap(new VarRef(0, 0, Symbol("Severe")), new DoubleLiteral(0, 0, 0.2));
    map_h->addMap(new VarRef(0, 0, Symbol("Mild")), new DoubleLiteral(0, 0, 0.8));
    cat_h->add(map_h);
    DistrExpr *cat_l = new DistrExpr(0, 0, Symbol("Categorical"));
    MapExpr *map_l = new MapExpr(0, 0);
    map_l->addMap(new VarRef(0, 0, Symbol("Severe")), new DoubleLiteral(0, 0, 0.8));
    map_l->addMap(new VarRef(0, 0, Symbol("Mild")), new DoubleLiteral(0, 0, 0.2));
    cat_l->add(map_l);
    FuncApp *prep = new FuncApp(0, 0, Symbol("Prep"));
    prep->add(new VarRef(0, 0, Symbol("c")));
    MapExpr *map_t = new MapExpr(0, 0);
    map_t->addMap(new VarRef(0, 0, Symbol("High")), cat_h);
    map_t->addMap(new VarRef(0, 0, Symbol("Low")), cat_l);
    DistrExpr *tab = new DistrExpr(0, 0, Symbol("TabularCPD"));
    tab->add(map_t);
    tab->add(prep);

    FuncDecl* func = new FuncDecl(0, 0, true, Symbol("DamageLevel"), Symbol("Damage"), tab);
    func->addArg(VarDecl(0, 0, Symbol("City"), Symbol("c")));
    blog->add(func);
  }
  /*
  obs Damage(First) = Severe;
  */
  {
    FuncApp *dam = new FuncApp(0, 0, Symbol("Damage"));
    dam->add(new VarRef(0, 0, Symbol("First")));
    Evidence *obs = new Evidence(0, 0, dam, new VarRef(0, 0, Symbol("Severe")));
    blog->add(obs);
  }
  /*
  query First;
  query Damage(A);
  query Damage(B);
  */
  {
    blog->add(new Query(0, 0, new VarRef(0, 0, Symbol("First"))));
    FuncApp *dam_A = new FuncApp(0, 0, Symbol("Damage"));
    dam_A->add(new VarRef(0, 0, Symbol("A")));
    blog->add(new Query(0, 0, dam_A));
    FuncApp *dam_B = new FuncApp(0, 0, Symbol("Damage"));
    dam_B->add(new VarRef(0, 0, Symbol("B")));
    blog->add(new Query(0, 0, dam_B));
  }
}

void Hurricane::test(FILE *file)
{
  build();
  if(file != NULL) root->print(file, 0);
}

}
