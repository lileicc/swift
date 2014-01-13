#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include "absyn/BlogProgram.h"
using namespace swift::absyn;

int main(int argc, char **argv){
  FILE* output;
  
  /* distinct Ball a[10], b; */
  {
  BlogProgram *distincttest = new BlogProgram(0,0);
  DistinctDecl *dis = new DistinctDecl(0, 0, Symbol("Ball"));
  dis->add(Symbol("a"), 10);
  dis->add(Symbol("b"), 1);
  distincttest->add(dis);
  
  output = fopen("test/parse/distinct.out", "w");
  distincttest->print(output, 0); 
  }
  
  /* obs Color(b[0]) = Red; */
  {
  BlogProgram *obstest = new BlogProgram(0,0);
  FuncApp *left = new FuncApp(0, 0, Symbol("Color"));
  OpExpr *sub = new OpExpr(0, 0, AbsynConstant::SUB, new VarRef(0, 0, Symbol("b")), new IntLiteral(0, 0, 0));
  left->add(sub);
  VarRef *right = new VarRef(0, 0, Symbol("Red"));
  Evidence *evid = new Evidence(0, 0, left, right);
  obstest->add(evid);
  
  output = fopen("test/parse/evidence.out", "w");
  obstest->print(output, 0); 
  }
  
  /* random Ball x ~ UniformChoice({b[0], b[1]}); */
  {
  BlogProgram *fundectest = new BlogProgram(0, 0);
  DistrExpr* distexp = new DistrExpr(0, 0, Symbol("UniformChoice"));
  OpExpr *sub0 = new OpExpr(0, 0, AbsynConstant::SUB, new VarRef(0, 0, Symbol("b")), new IntLiteral(0, 0, 0));
  OpExpr *sub1 = new OpExpr(0, 0, AbsynConstant::SUB, new VarRef(0, 0, Symbol("b")), new IntLiteral(0, 0, 1));
  ListSet *set = new ListSet(0, 0);
  set->add(sub0);
  set->add(sub1);
  distexp->add(set);
  FuncDecl *fundec = new FuncDecl(0, 0, true, Ty(0, 0, Symbol("Ball")), Symbol("x"), distexp);
  fundectest->add(fundec);
  
  output = fopen("test/parse/fundec.out", "w");
  fundectest->print(output, 0); 
  }
  /* random Ball x ~ Categorical({b[0]->0.5, b[1]->0.5}); */
  {
  BlogProgram *maptest = new BlogProgram(0, 0);
  DistrExpr *distexp = new DistrExpr(0, 0, Symbol("Categorical"));
  OpExpr *sub0 = new OpExpr(0, 0, AbsynConstant::SUB, new VarRef(0, 0, Symbol("b")), new IntLiteral(0, 0, 0));
  OpExpr *sub1 = new OpExpr(0, 0, AbsynConstant::SUB, new VarRef(0, 0, Symbol("b")), new IntLiteral(0, 0, 1));
  MapExpr *map = new MapExpr(0, 0);
  map->addMap(sub0, new DoubleLiteral(0, 0, 0.5));
  map->addMap(sub1, new DoubleLiteral(0, 0, 0.5));
  distexp->add(map);
  FuncDecl *fundec = new FuncDecl(0, 0, true, Ty(0, 0, Symbol("Ball")), Symbol("x"), distexp);
  maptest->add(fundec);
  
  output = fopen("test/parse/map.out", "w");
  maptest->print(output, 0); 
  }
  /*
  random PrepLevel Prep(City c) {
    if (First == c) then ~ Categorical({High -> 0.5, Low -> 0.5})
    else ~ Categorical({High -> 0.8, Low -> 0.2})
  };
  */
  {
  BlogProgram *iftest = new BlogProgram(0, 0);
  OpExpr *condexp = new OpExpr(0, 0, AbsynConstant::EQ, new VarRef(0, 0, Symbol("First")), new VarRef(0, 0, Symbol("c")));
  MapExpr *map1 = new MapExpr(0, 0);
  map1->addMap(new VarRef(0, 0, Symbol("High")), new DoubleLiteral(0, 0, 0.5));
  map1->addMap(new VarRef(0, 0, Symbol("Low")), new DoubleLiteral(0, 0, 0.5));
  MapExpr *map2 = new MapExpr(0, 0);
  map2->addMap(new VarRef(0, 0, Symbol("High")), new DoubleLiteral(0, 0, 0.8));
  map2->addMap(new VarRef(0, 0, Symbol("Low")), new DoubleLiteral(0, 0, 0.2));
  DistrExpr *dist1 = new DistrExpr(0, 0, Symbol("Categorical"));
  dist1->add(map1);
  DistrExpr *dist2 = new DistrExpr(0, 0, Symbol("Categorical"));
  dist2->add(map2);
  IfExpr *ifexp = new IfExpr(0, 0, condexp, dist1, dist2);
  FuncDecl *fundec = new FuncDecl(0, 0, true, Ty(0, 0, Symbol("PrepLevel")), Symbol("Prep"), ifexp);
  fundec->addArg(VarDecl(0, 0, Ty(0, 0, Symbol("City")), Symbol("c")));
  iftest->add(fundec);
  
  output = fopen("test/parse/ifexp.out", "w");
  iftest->print(output, 0);
  }
  /*
  query exists Person x exists Person y (x==y);
  */
  {
  BlogProgram *quanttest = new BlogProgram(0, 0);
  QuantExpr *qexp2 = new QuantExpr(0, 0, AbsynConstant::EXISTS, VarDecl(0, 0, Ty(0, 0, Symbol("Person")), Symbol("y")), 
                                   new OpExpr(0, 0, AbsynConstant::EQ, new VarRef(0, 0, Symbol("x")), new VarRef(0, 0, Symbol("y")))); 
  QuantExpr *qexp = new QuantExpr(0, 0, AbsynConstant::EXISTS, VarDecl(0, 0, Ty(0, 0, Symbol("Person")), Symbol("x")), qexp2);
  Query *q = new Query(0, 0, qexp);
  quanttest->add(q);
  
  output = fopen("test/parse/quant.out", "w");
  quanttest->print(output, 0);
  }
  /*
  origin Aircraft Source(Blip);
  */
  {
  BlogProgram *origintest = new BlogProgram(0, 0);
  OriginDecl *orig = new OriginDecl(0, 0, Symbol("Aircraft"), Symbol("Source"), Symbol("Blip"));
  origintest->add(orig);
  
  output = fopen("test/parse/origin.out", "w");
  origintest->print(output, 0);
  }
  /*
  #Blip(Source = a) ~ Poisson(1.0);
  */
  {
  BlogProgram *numdectest = new BlogProgram(0, 0);
  DistrExpr *distexp = new DistrExpr(0, 0, Symbol("Poisson"));
  distexp->add(new DoubleLiteral(0, 0, 1.0));
  NumStDecl *numdec = new NumStDecl(0, 0, Symbol("Blip"), distexp);
  numdec->add(Symbol("Source"), Symbol("a"));
  numdectest->add(numdec);
  
  output = fopen("test/parse/numdec.out", "w");
  numdectest->print(output, 0);
  }
  /*
  query #{Aircraft a : a != b};
  */
  {
  BlogProgram *numreftest = new BlogProgram(0, 0);
  CondSet *cset = new CondSet(0, 0, VarDecl(0, 0, Ty(0, 0, Symbol("Aircraft")), Symbol("a")), 
                              new OpExpr(0, 0, AbsynConstant::NEQ, new VarRef(0, 0, Symbol("a")), new VarRef(0, 0, Symbol("b"))));
  NumStRef *numref = new NumStRef(0, 0, cset);
  Query *q = new Query(0, 0, numref);
  numreftest->add(q);
  
  output = fopen("test/parse/numref.out", "w");
  numreftest->print(output, 0);
  }
  return 0;
}
