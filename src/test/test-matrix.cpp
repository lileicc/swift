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
#include "random/Binomial.h"
#include "random/BooleanDistrib.h"
#include "random/Categorical.h"
#include "random/Exponential.h"
#include "random/Gaussian.h"
#include "random/Gamma.h"
#include "random/Geometric.h"
#include "random/Poisson.h"
#include "random/InvGamma.h"
#include "random/UniformChoice.h"
#include "random/UniformInt.h"
#include "random/UniformReal.h"
#include "util/Hist.h"
#include "util/util.h"
#include "util/DynamicTable.h"


// Matrix Library included
#include "armadillo"
#include "random/DiagGaussian.h"
#include "random/Dirichlet.h"
#include "random/Discrete.h"
#include "random/MultivarGaussian.h"
#include "random/MultivarGaussianIndep.h"
#include "random/Multinomial.h"
#include "random/UniformVector.h"
#include "util/Hist_matrix.h"
#include "util/util_matrix.h"
using namespace arma;

using namespace std;
using namespace swift::random;


int main();

namespace swift {

class BLOGProgram;

class BLOGProgram {
public:
  BLOGProgram();
  void init(int);
  void print();
  void debug();
  int _cur_loop;
  default_random_engine __random_device;
  double __fixed_x = 1;
  double __fixed_y = 0;
  double __fixed_z = -1;
  mat __fixed_A = rowvec(vector<double>({__fixed_x, __fixed_y, __fixed_z}));
  mat __fixed_B = vec(vector<double>({__fixed_x, __fixed_y, __fixed_z}));
  mat __fixed_W = _to_matrix(vector<double>({1, 0.000000, 0, 0.000000, 1, 0, 0.000000, 0, 1}),3,3);
  double __fixed_scale(double);
  mat __value_C;
  int __mark_C;
  mat& __get_C();
  MultivarGaussian MultivarGaussian140692428970192;
  double __likeli_C();
  double __set_C(mat);
  mat __value_D;
  int __mark_D;
  mat& __get_D();
  MultivarGaussian MultivarGaussian140692428970832;
  double __likeli_D();
  double __set_D(mat);
  bool _set_evidence(double&);
  void sample(int);
  vector<double> _weight;
  inline void _evaluate_query(double);
  Hist<double> _answer_0 = Hist<double>(true);
  Hist<double> _answer_1 = Hist<double>(true);
  Hist<double> _answer_2 = Hist<double>(true);
  Hist<mat> _answer_3 = Hist<mat>(true);
};

BLOGProgram::BLOGProgram()
{}
void BLOGProgram::init(int n)
{
  MultivarGaussian140692428970192.init(__fixed_B,__fixed_W);
  MultivarGaussian140692428970832.init(vec(vector<double>({3.00000000, 3.00000000, 3.00000000})),__fixed_W);
  _weight.resize(n);
}
void BLOGProgram::print()
{
  _answer_0.print("scale(1.500000)");
  _answer_1.print("C[0]");
  _answer_2.print("D[0]+B*A[0][0]");
  _answer_3.print("C");
}
void BLOGProgram::debug()
{}
double BLOGProgram::__fixed_scale(double k)
{
  return as_scalar(__fixed_A*trans(__fixed_A)*k);
}
mat& BLOGProgram::__get_C()
{
  mat& __retvalue = __value_C;
  int& __mark = __mark_C;
  if (__mark==_cur_loop)
    return __retvalue;
  __retvalue=MultivarGaussian140692428970192.gen();
  __mark=_cur_loop;
  return __retvalue;
}
double BLOGProgram::__likeli_C()
{
  mat& __retvalue = __value_C;
  double __local_weight = 0.000000;
  __local_weight=MultivarGaussian140692428970192.loglikeli(__retvalue);
  return __local_weight;
}
double BLOGProgram::__set_C(mat __retvalue_arg)
{
  __value_C=__retvalue_arg;
  int& __mark = __mark_C;
  __mark=_cur_loop;
  return __likeli_C();
}
mat& BLOGProgram::__get_D()
{
  mat& __retvalue = __value_D;
  int& __mark = __mark_D;
  if (__mark==_cur_loop)
    return __retvalue;
  __retvalue=MultivarGaussian140692428970832.gen();
  __mark=_cur_loop;
  return __retvalue;
}
double BLOGProgram::__likeli_D()
{
  mat& __retvalue = __value_D;
  double __local_weight = 0.000000;
  __local_weight=MultivarGaussian140692428970832.loglikeli(__retvalue);
  return __local_weight;
}
double BLOGProgram::__set_D(mat __retvalue_arg)
{
  __value_D=__retvalue_arg;
  int& __mark = __mark_D;
  __mark=_cur_loop;
  return __likeli_D();
}
bool BLOGProgram::_set_evidence(double& __local_weight)
{
  __local_weight=0.000000;
  __local_weight+=__set_D(vstack({2, 2, 2}));
  return true;
}
void BLOGProgram::sample(int n)
{
  double __local_weight;
  init(n);
  for (_cur_loop=1;_cur_loop<n;_cur_loop++)
  {
    if (_set_evidence(__local_weight))
      _evaluate_query(__local_weight);
    _weight[_cur_loop]=__local_weight;
  }

}
inline void BLOGProgram::_evaluate_query(double __local_weight)
{
  _answer_0.add(__fixed_scale(1.50000000),__local_weight);
  _answer_1.add(__get_C()[0],__local_weight);
  _answer_2.add(__get_D()[0]+mat(__fixed_B*__fixed_A)(0,0),__local_weight);
  _answer_3.add(__get_C(),__local_weight);
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
