#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cassert>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<random>
#include<numeric>
#include<string>
#include "random/CategoricalDistribution.h"

using namespace std;
using namespace swift::random;

int main();

namespace swift {

class BLOGProgram { public:
  void init(int);
  int _cur_loop;
  std::default_random_engine __random_device;
  int __num_City;
  int __mark___num_City;
  inline int __get___num_City();
  int __num_DamageLevel;
  int __mark___num_DamageLevel;
  inline int __get___num_DamageLevel();
  int __num_PrepLevel;
  int __mark___num_PrepLevel;
  inline int __get___num_PrepLevel();
  int* __value_Damage;
  int* __mark_Damage;
  int __get_Damage(int);
  Categorical Categorical4297096984;
  Categorical Categorical4297097848;
  double __likeli_Damage(int);
  double __set_Damage(int,int);
  int* __value_Prep;
  int* __mark_Prep;
  int __get_Prep(int);
  Categorical Categorical4297093784;
  Categorical Categorical4297094872;
  Categorical Categorical4297095720;
  double __likeli_Prep(int);
  double __set_Prep(int,int);
  double _set_evidence();
  void sample(int);
  double* _weight;
  inline void _evaluate_query(double);
};
class City { public:
  std::string _name;
};
class DamageLevel { public:
  std::string _name;
};
class PrepLevel { public:
  std::string _name;
};

void BLOGProgram::init(int n)
{
  (__num_City=2);
  (__mark___num_City=1);
  (__num_DamageLevel=2);
  (__mark___num_DamageLevel=1);
  (__num_PrepLevel=2);
  (__mark___num_PrepLevel=1);
  delete[] __value_Damage;
  (__value_Damage=new int[n]);
  delete[] __mark_Damage;
  (__mark_Damage=new int[n]);
  (Categorical4297096984.init)(unordered_map<int, int>({{0, 0.2000000}, {1, 0.8000000}}));
  (Categorical4297097848.init)(unordered_map<int, int>({{0, 0.8000000}, {1, 0.2000000}}));
  delete[] __value_Prep;
  (__value_Prep=new int[n]);
  delete[] __mark_Prep;
  (__mark_Prep=new int[n]);
  (Categorical4297093784.init)(unordered_map<int, int>({{1, 0.5000000}, {0, 0.5000000}}));
  (Categorical4297094872.init)(unordered_map<int, int>({{1, 0.9000000}, {0, 0.1000000}}));
  (Categorical4297095720.init)(unordered_map<int, int>({{1, 0.1000000}, {0, 0.9000000}}));
  delete[] _weight;
  (_weight=new double[n]);
}
inline int BLOGProgram::__get___num_City()
{
  return __num_City;
}
inline int BLOGProgram::__get___num_DamageLevel()
{
  return __num_DamageLevel;
}
inline int BLOGProgram::__get___num_PrepLevel()
{
  return __num_PrepLevel;
}
int BLOGProgram::__get_Damage(int c)
{
int& __value = __value_Damage[c];
int& __mark = __mark_Damage[c];
  if ((__mark==_cur_loop))
    return __value;
  (__mark=_cur_loop);
  switch (__get_Prep(n ))
  {
  case 1:
    (__value=(Categorical4297096984.gen)(__random_engine));
    break;
  case 0:
    (__value=(Categorical4297097848.gen)(__random_engine));
    break;
  }
  return __value;
}
double BLOGProgram::__likeli_Damage(int c)
{
int& __value = __value_Damage[c];
double __local_weight = 0.0000000;
  switch (__get_Prep(n ))
  {
  case 1:
    (__local_weight=(Categorical4297096984.loglikeli)(__value));
    break;
  case 0:
    (__local_weight=(Categorical4297097848.loglikeli)(__value));
    break;
  }
  return __local_weight;
}
double BLOGProgram::__set_Damage(int c, int __value_arg)
{
int __value = __value_Damage[c];
int& __mark = __mark_Damage[c];
  (__mark=_cur_loop);
  (__value=__value_arg);
  return __likeli_Damage(c);
}
int BLOGProgram::__get_Prep(int c)
{
int& __value = __value_Prep[c];
int& __mark = __mark_Prep[c];
  if ((__mark==_cur_loop))
    return __value;
  (__mark=_cur_loop);
  if ((__get_First()>n ))
    (__value=(Categorical4297093784.gen)(__random_engine));
  return __value;
}
double BLOGProgram::__likeli_Prep(int c)
{
int& __value = __value_Prep[c];
double __local_weight = 0.0000000;
  if ((__get_First()>n ))
    (__local_weight=(Categorical4297093784.loglikeli)(__value));
  return __local_weight;
}
double BLOGProgram::__set_Prep(int c, int __value_arg)
{
int __value = __value_Prep[c];
int& __mark = __mark_Prep[c];
  (__mark=_cur_loop);
  (__value=__value_arg);
  return __likeli_Prep(c);
}
double BLOGProgram::_set_evidence()
{
double __local_weight = 0.0000000;
  (__local_weight+=__set_Damage(__get_First(),0));
  return __local_weight;
}
void BLOGProgram::sample(int n)
{
double __local_weight;
  init(n);
  for ((_cur_loop=1);(_cur_loop<=n);(n++))
  {
    (__local_weight=_set_evidence());
    _evaluate_query(__local_weight);
    (_weight[_cur_loop]=__local_weight);
  }
;
}
inline void BLOGProgram::_evaluate_query(double __local_weight)
{
  (_answer_0.add)(__get_First(),__local_weight);
  (_answer_1.add)(__get_Damage(0),__local_weight);
  (_answer_2.add)(__get_Damage(1),__local_weight);
}

}
int main()
{
swift::BLOGProgram sampler;
  (sampler.sample)(10000);
}
