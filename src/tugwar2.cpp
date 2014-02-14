#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>
#include <numeric>
#include <string>
#include <memory>
#include <functional>
#include <utility>
#include "random/Bernoulli.h"
#include "random/Beta.h"
#include "random/BooleanDistrib.h"
#include "random/CategoricalDistribution.h"
#include "random/Dirichlet.h"
#include "random/Gaussian.h"
#include "random/Poisson.h"
#include "random/UniformChoice.h"
#include "random/UniformInt.h"
#include "util/Hist.h"

using namespace std;
using namespace swift::random;

int main();

namespace swift {

class BLOGProgram {
public:
  BLOGProgram();
  void init(int);
  void print();
  void debug();
  int _cur_loop;
  default_random_engine __random_device;
  int __num_Match;
  int __mark___num_Match;
  inline void __ensure___num_Match();
  inline int __get___num_Match();
  int __num_Person;
  int __mark___num_Person;
  inline void __ensure___num_Person();
  inline int __get___num_Person();
  vector<vector<bool>> __value_lazy;
  vector<vector<int>> __mark_lazy;
  bool __get_lazy(int,int);
  BooleanDistrib BooleanDistrib4299195328;
  double __likeli_lazy(int,int);
  double __set_lazy(int,int,bool);
  vector<vector<double>> __value_pulling_power;
  vector<vector<int>> __mark_pulling_power;
  double __get_pulling_power(int,int);
  double __likeli_pulling_power(int,int);
  double __set_pulling_power(int,int,double);
  vector<double> __value_strength;
  vector<int> __mark_strength;
  double __get_strength(int);
  Gaussian Gaussian4299190384;
  double __likeli_strength(int);
  double __set_strength(int,double);
  vector<int> __value_team1player1;
  vector<int> __mark_team1player1;
  int __get_team1player1(int);
  UniformInt UniformInt4299190784;
  double __likeli_team1player1(int);
  double __set_team1player1(int,int);
  vector<int> __value_team1player2;
  vector<int> __mark_team1player2;
  int __get_team1player2(int);
  UniformChoice UniformChoice4299190976;
  double __likeli_team1player2(int);
  double __set_team1player2(int,int);
  vector<bool> __value_team1win;
  vector<int> __mark_team1win;
  bool __get_team1win(int);
  double __likeli_team1win(int);
  double __set_team1win(int,bool);
  vector<int> __value_team2player1;
  vector<int> __mark_team2player1;
  int __get_team2player1(int);
  UniformChoice UniformChoice4299193184;
  double __likeli_team2player1(int);
  double __set_team2player1(int,int);
  vector<int> __value_team2player2;
  vector<int> __mark_team2player2;
  int __get_team2player2(int);
  UniformChoice UniformChoice4299195104;
  double __likeli_team2player2(int);
  double __set_team2player2(int,int);
  double _set_evidence();
  void sample(int);
  vector<double> _weight;
  inline void _evaluate_query(double);
  Hist<bool> _answer_0 = Hist<bool>(false);
  Hist<bool> _answer_1 = Hist<bool>(false);
  Hist<bool> _answer_2 = Hist<bool>(false);
  Hist<bool> _answer_3 = Hist<bool>(false);
};
class Match {
public:
  string _name;
};
class Person {
public:
  string _name;
};

BLOGProgram::BLOGProgram()
{}
void BLOGProgram::init(int n)
{
  __num_Person=8;
  __mark___num_Person=-1;
  __ensure___num_Person();
  __num_Match=4;
  __mark___num_Match=-1;
  __ensure___num_Match();
  BooleanDistrib4299195328.init(0.1000000);
  Gaussian4299190384.init(10,2);
  _weight.resize(n);
}
void BLOGProgram::print()
{
  _answer_0.print();
  _answer_1.print();
  _answer_2.print();
  _answer_3.print();
}
void BLOGProgram::debug()
{}
inline void BLOGProgram::__ensure___num_Match()
{
  resize(__value_lazy,1,__num_Match);
  resize(__mark_lazy,1,__num_Match);
  resize(__value_pulling_power,1,__num_Match);
  resize(__mark_pulling_power,1,__num_Match);
  resize(__value_team1player1,0,__num_Match);
  resize(__mark_team1player1,0,__num_Match);
  resize(__value_team1player2,0,__num_Match);
  resize(__mark_team1player2,0,__num_Match);
  resize(__value_team1win,0,__num_Match);
  resize(__mark_team1win,0,__num_Match);
  resize(__value_team2player1,0,__num_Match);
  resize(__mark_team2player1,0,__num_Match);
  resize(__value_team2player2,0,__num_Match);
  resize(__mark_team2player2,0,__num_Match);
}
inline int BLOGProgram::__get___num_Match()
{
  __mark___num_Match=_cur_loop;
  return __num_Match;
}
inline void BLOGProgram::__ensure___num_Person()
{
  resize(__value_lazy,0,__num_Person);
  resize(__mark_lazy,0,__num_Person);
  resize(__value_pulling_power,0,__num_Person);
  resize(__mark_pulling_power,0,__num_Person);
  resize(__value_strength,0,__num_Person);
  resize(__mark_strength,0,__num_Person);
}
inline int BLOGProgram::__get___num_Person()
{
  __mark___num_Person=_cur_loop;
  return __num_Person;
}
bool BLOGProgram::__get_lazy(int p, int m)
{
  bool __value = __value_lazy[p][m];
  int& __mark = __mark_lazy[p][m];
  if (__mark==_cur_loop)
    return __value;
  __value=BooleanDistrib4299195328.gen();
  __mark=_cur_loop;
  __value_lazy[p][m]=__value;
  return __value;
}
double BLOGProgram::__likeli_lazy(int p, int m)
{
  bool __value = __value_lazy[p][m];
  double __local_weight = 0.0000000;
  __local_weight=BooleanDistrib4299195328.likeli(__value);
  return __local_weight;
}
double BLOGProgram::__set_lazy(int p, int m, bool __value_arg)
{
  __value_lazy[p][m]=__value_arg;
  int& __mark = __mark_lazy[p][m];
  __mark=_cur_loop;
  return __likeli_lazy(p,m);
}
double BLOGProgram::__get_pulling_power(int p, int m)
{
  double& __value = __value_pulling_power[p][m];
  int& __mark = __mark_pulling_power[p][m];
  if (__mark==_cur_loop)
    return __value;
  if (__get_lazy(p,m))
    __value=__get_strength(p)/2.0000000;
  else
    __value=__get_strength(p);
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_pulling_power(int p, int m)
{
  double& __value = __value_pulling_power[p][m];
  double __local_weight = 0.0000000;
  if (__get_lazy(p,m))
    __local_weight=__value==__get_strength(p)/2.0000000;
  else
    __local_weight=__value==__get_strength(p);
  return __local_weight;
}
double BLOGProgram::__set_pulling_power(int p, int m, double __value_arg)
{
  __value_pulling_power[p][m]=__value_arg;
  int& __mark = __mark_pulling_power[p][m];
  __mark=_cur_loop;
  return __likeli_pulling_power(p,m);
}
double BLOGProgram::__get_strength(int p)
{
  double& __value = __value_strength[p];
  int& __mark = __mark_strength[p];
  if (__mark==_cur_loop)
    return __value;
  __value=Gaussian4299190384.gen();
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_strength(int p)
{
  double& __value = __value_strength[p];
  double __local_weight = 0.0000000;
  __local_weight=Gaussian4299190384.likeli(__value);
  return __local_weight;
}
double BLOGProgram::__set_strength(int p, double __value_arg)
{
  __value_strength[p]=__value_arg;
  int& __mark = __mark_strength[p];
  __mark=_cur_loop;
  return __likeli_strength(p);
}
int BLOGProgram::__get_team1player1(int m)
{
  int& __value = __value_team1player1[m];
  int& __mark = __mark_team1player1[m];
  if (__mark==_cur_loop)
    return __value;
  __value=(UniformInt4299190784.init(0,__get___num_Person()-1),UniformInt4299190784.gen());
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_team1player1(int m)
{
  int& __value = __value_team1player1[m];
  double __local_weight = 0.0000000;
  __local_weight=(UniformInt4299190784.init(0,__get___num_Person()-1),UniformInt4299190784.likeli(__value));
  return __local_weight;
}
double BLOGProgram::__set_team1player1(int m, int __value_arg)
{
  __value_team1player1[m]=__value_arg;
  int& __mark = __mark_team1player1[m];
  __mark=_cur_loop;
  return __likeli_team1player1(m);
}
int BLOGProgram::__get_team1player2(int m)
{
  int& __value = __value_team1player2[m];
  int& __mark = __mark_team1player2[m];
  if (__mark==_cur_loop)
    return __value;
  __value=(UniformChoice4299190976.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m);
})),UniformChoice4299190976.gen());
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_team1player2(int m)
{
  int& __value = __value_team1player2[m];
  double __local_weight = 0.0000000;
  __local_weight=(UniformChoice4299190976.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m);
})),UniformChoice4299190976.likeli(__value));
  return __local_weight;
}
double BLOGProgram::__set_team1player2(int m, int __value_arg)
{
  __value_team1player2[m]=__value_arg;
  int& __mark = __mark_team1player2[m];
  __mark=_cur_loop;
  return __likeli_team1player2(m);
}
bool BLOGProgram::__get_team1win(int m)
{
  bool __value = __value_team1win[m];
  int& __mark = __mark_team1win[m];
  if (__mark==_cur_loop)
    return __value;
  if (__get_pulling_power(__get_team1player1(m),m)+__get_pulling_power(__get_team1player2(m),m)>__get_pulling_power(__get_team2player1(m),m)+__get_pulling_power(__get_team2player2(m),m))
    __value=true;
  else
    __value=false;
  __mark=_cur_loop;
  __value_team1win[m]=__value;
  return __value;
}
double BLOGProgram::__likeli_team1win(int m)
{
  bool __value = __value_team1win[m];
  double __local_weight = 0.0000000;
  if (__get_pulling_power(__get_team1player1(m),m)+__get_pulling_power(__get_team1player2(m),m)>__get_pulling_power(__get_team2player1(m),m)+__get_pulling_power(__get_team2player2(m),m))
    __local_weight=__value==true;
  else
    __local_weight=__value==false;
  return __local_weight;
}
double BLOGProgram::__set_team1win(int m, bool __value_arg)
{
  __value_team1win[m]=__value_arg;
  int& __mark = __mark_team1win[m];
  __mark=_cur_loop;
  return __likeli_team1win(m);
}
int BLOGProgram::__get_team2player1(int m)
{
  int& __value = __value_team2player1[m];
  int& __mark = __mark_team2player1[m];
  if (__mark==_cur_loop)
    return __value;
  __value=(UniformChoice4299193184.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m)&&p!=__get_team1player2(m);
})),UniformChoice4299193184.gen());
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_team2player1(int m)
{
  int& __value = __value_team2player1[m];
  double __local_weight = 0.0000000;
  __local_weight=(UniformChoice4299193184.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m)&&p!=__get_team1player2(m);
})),UniformChoice4299193184.likeli(__value));
  return __local_weight;
}
double BLOGProgram::__set_team2player1(int m, int __value_arg)
{
  __value_team2player1[m]=__value_arg;
  int& __mark = __mark_team2player1[m];
  __mark=_cur_loop;
  return __likeli_team2player1(m);
}
int BLOGProgram::__get_team2player2(int m)
{
  int& __value = __value_team2player2[m];
  int& __mark = __mark_team2player2[m];
  if (__mark==_cur_loop)
    return __value;
  __value=(UniformChoice4299195104.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m)&&p!=__get_team1player2(m)&&p!=__get_team2player1(m);
})),UniformChoice4299195104.gen());
  __mark=_cur_loop;
  return __value;
}
double BLOGProgram::__likeli_team2player2(int m)
{
  int& __value = __value_team2player2[m];
  double __local_weight = 0.0000000;
  __local_weight=(UniformChoice4299195104.init(_filter(__get___num_Person(),[&](int p){
    return p!=__get_team1player1(m)&&p!=__get_team1player2(m)&&p!=__get_team2player1(m);
})),UniformChoice4299195104.likeli(__value));
  return __local_weight;
}
double BLOGProgram::__set_team2player2(int m, int __value_arg)
{
  __value_team2player2[m]=__value_arg;
  int& __mark = __mark_team2player2[m];
  __mark=_cur_loop;
  return __likeli_team2player2(m);
}
double BLOGProgram::_set_evidence()
{
  double __local_weight = 1.0000000;
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player1(0,0);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player2(0,1);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team2player1(0,3);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team2player2(0,2);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player1(1,0);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player2(1,1);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team2player1(1,4);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team2player2(1,5);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player1(2,0);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1player2(2,7);
  if (__local_weight>0.0000000)
    __local_weight*=__set_team1win(0,true);
  return __local_weight;
}
void BLOGProgram::sample(int n)
{
  double __local_weight;
  init(n);
  for (_cur_loop=1;_cur_loop<n;_cur_loop++)
  {
    __local_weight=_set_evidence();
    _evaluate_query(__local_weight);
    _weight[_cur_loop]=__local_weight;
  }

}
inline void BLOGProgram::_evaluate_query(double __local_weight)
{
  _answer_0.add(__get_strength(0)>__get_strength(3),__local_weight);
  _answer_1.add(__get_team1win(1),__local_weight);
  _answer_2.add(__get_team1win(2),__local_weight);
  _answer_3.add(!__get_team1win(3)&&__get_team2player1(3)==4&&__get_team2player2(3)==6,__local_weight);
}

}
int main()
{
  std::chrono::time_point<std::chrono::system_clock> __start_time = std::chrono::system_clock::now();
  swift::BLOGProgram sampler;
  sampler.sample(1000000);
  sampler.print();
  std::chrono::duration<double> __elapsed_seconds = std::chrono::system_clock::now()-__start_time;
  printf("\nrunning time: %fs\n",__elapsed_seconds.count());
}
