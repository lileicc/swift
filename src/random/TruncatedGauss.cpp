/*
 * TruncatedGauss.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: yiwu
 */
 
#include <cmath>
#include <cassert>
#include "TruncatedGauss.h"

namespace swift {
namespace random {

/////////////////////////////////////////////////////
// util function for computing cdf of N(0,1)
// >> ref: http://math60082.blogspot.com/2013/02/question-write-function-to-calculate-nx.html
double get_cdf01(double x)
{ // calculate \sqrt{2\pi} upfront once
  static const double RT2PI = sqrt(4.0*acos(0.0));
  // calculate 10/\sqrt{2} upfront once
  static const double SPLIT = 10./sqrt(2);
  static const double a[] = {220.206867912376,221.213596169931,112.079291497871,33.912866078383,6.37396220353165,0.700383064443688,3.52624965998911e-02};
  static const double b[] = {440.413735824752,793.826512519948,637.333633378831,296.564248779674,86.7807322029461,16.064177579207,1.75566716318264,8.83883476483184e-02};
  
  const double z = fabs(x);
  // Now N(x) = 1 - N(-x) = 1-\sqrt{2\pi}N'(x)\frac{P(x)}{Q(x)}
  //  so N(-x) = \sqrt{2\pi}N'(x)\frac{P(x)}{Q(x)}
  // now let \sqrt{2\pi}N'(z)\frac{P(x)}{Q(z)} = Nz
  // Therefore we have
  //     Nxm = N(x) = \sqrt{2\pi}N'(z)\frac{P(x)}{Q(z)} = Nz if x<0
  //     Nxp = N(x) = 1 - \sqrt{2\pi}N'(z)\frac{P(x)}{Q(z)} = 1-Nz if x>=0
  double Nz = 0.0;
  
  // if z outside these limits then value effectively 0 or 1 for machine precision
  if(z<=37.0)
  {
    // NDash = N'(z) * sqrt{2\pi}
    const double NDash = exp(-z*z/2.0)/RT2PI;
    if(z<SPLIT)
    {
      // here Pz = P(z) is a polynomial
      const double Pz = (((((a[6]*z + a[5])*z + a[4])*z + a[3])*z + a[2])*z + a[1])*z + a[0];
      // and Qz = Q(z) is a polynomial
      const double Qz = ((((((b[7]*z + b[6])*z + b[5])*z + b[4])*z + b[3])*z + b[2])*z + b[1])*z + b[0];
      // use polynomials to calculate N(z)  = \sqrt{2\pi}N'(x)\frac{P(x)}{Q(x)}
      Nz = RT2PI*NDash*Pz/Qz;
    }
    else
    {
      // implement recurrence relation on F_4(z) 
      const double F4z = z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))));
      // use polynomials to calculate N(z), note here that Nz = N' / F
      Nz = NDash/F4z;
    }
  }
  
  // 
  return x>=0.0 ? 1-Nz : Nz;
}
///////////////////////////
// util function for inverse cdf for N(0,1)
// >> ref: https://people.sc.fsu.edu/~jburkardt/cpp_src/asa241/asa241.html
inline double r8poly_value ( int n, double a[], double x ) {
  double value = 0;
  for (int i = n-1; 0 <= i; i-- ) value = value * x + a[i];
  return value;
}
double get_inv_cdf01 ( double p ) {
  static double a[8] = { 
    3.3871328727963666080,     1.3314166789178437745e+2,
    1.9715909503065514427e+3,  1.3731693765509461125e+4,
    4.5921953931549871457e+4,  6.7265770927008700853e+4,
    3.3430575583588128105e+4,  2.5090809287301226727e+3 };
  static double b[8] = {
    1.0,                       4.2313330701600911252e+1,
    6.8718700749205790830e+2,  5.3941960214247511077e+3,
    2.1213794301586595867e+4,  3.9307895800092710610e+4,
    2.8729085735721942674e+4,  5.2264952788528545610e+3 };
  static double c[8] = {
    1.42343711074968357734,     4.63033784615654529590,
    5.76949722146069140550,     3.64784832476320460504,
    1.27045825245236838258,     2.41780725177450611770e-1,
    2.27238449892691845833e-2,  7.74545014278341407640e-4 };
  static double const1 = 0.180625;
  static double const2 = 1.6;
  static double d[8] = {
    1.0,                        2.05319162663775882187,
    1.67638483018380384940,     6.89767334985100004550e-1,
    1.48103976427480074590e-1,  1.51986665636164571966e-2,
    5.47593808499534494600e-4,  1.05075007164441684324e-9 };
  static double e[8] = {
    6.65790464350110377720,     5.46378491116411436990,
    1.78482653991729133580,     2.96560571828504891230e-1,
    2.65321895265761230930e-2,  1.24266094738807843860e-3,
    2.71155556874348757815e-5,  2.01033439929228813265e-7 };
  static double f[8] = {
    1.0,                        5.99832206555887937690e-1,
    1.36929880922735805310e-1,  1.48753612908506148525e-2,
    7.86869131145613259100e-4,  1.84631831751005468180e-5,
    1.42151175831644588870e-7,  2.04426310338993978564e-15 };
  double q, r;
  static double split1 = 0.425;
  static double split2 = 5.0;
  double value;
  
  assert(p>0&&p<1);
  
  q = p - 0.5;
  if ( fabs ( q ) <= split1 ) {
    r = const1 - q * q;
    value = q * r8poly_value ( 8, a, r ) / r8poly_value ( 8, b, r );
  } 
  else {
    if ( q < 0.0 ) r = p;
    else r = 1.0 - p;
    if ( r <= 0.0 ) {
      value = -1.0;
      exit ( 1 );
    }
    r = sqrt ( -log ( r ) );
    if ( r <= split2 ) {
      r = r - const2;
      value = r8poly_value ( 8, c, r ) / r8poly_value ( 8, d, r ); 
     }
     else {
       r = r - split2;
       value = r8poly_value ( 8, e, r ) / r8poly_value ( 8, f, r );
     }
    if ( q < 0.0 )
      value = -value;
  }
  return value;
}

/////////////////////////////////////////////////////

TruncatedGauss::TruncatedGauss() :
  dist(0.0, 1.0), dist_unif(0, 1), mean(0.0), stddev(1.0), var(1.0),
  is_like_ok(true), is_loglike_ok(true),
  sqrt_2PI(std::sqrt(2.0 * PI)),
  lt(-1), rt(1) {
  coef = 1.0 / (stddev * sqrt_2PI);
  log_coef = -std::log(stddev * sqrt_2PI);
  scale = -0.5;
}

TruncatedGauss::~TruncatedGauss() {
}

void TruncatedGauss::init(double mean, double var, double _l, double _r) {
  this->mean = mean;
  if (var != this->var) {
    this->var = var;
    this->stddev = std::sqrt(var);
    is_like_ok = is_loglike_ok = false;
    scale = -0.5 / (var);
  }
  assert(_l < _r);
  if (_l != this->lt || _r != this->rt) {
    this->lt = _l; this->rt = _r;
    shft_lt = ( _l - mean ) / this->stddev;
    shft_rt = ( _r - mean ) / this->stddev;
    l_cdf = get_cdf01(shft_lt);
    r_cdf = get_cdf01(shft_rt);
    mid_cdf = r_cdf - l_cdf;
    inv_mid_cdf = 1.0 / mid_cdf;
    coef *= inv_mid_cdf;
    log_coef -= log(mid_cdf);
  }
}

double TruncatedGauss::gen_trunc01(double l, double r) {
  // rejection sampling
  double x;
  if (l == 0) {
    if (r >= 2) {
      while(x = fabs(dist(engine)), x > r);
      return x;
    }
  } else 
  if (r == 0){
    if (l <= -2) {
      while(x = -fabs(dist(engine)), x < l);
      return x;
    }
  } else
  if (l <= -2 && r >= 2) {
    while(x = dist(engine), (x < l || x > r));
    return x;
  }
  // using inverse cdf function
  double y = dist_unif(engine) * mid_cdf + l_cdf;
  return get_inv_cdf01(y);
}

double TruncatedGauss::gen() {
  return gen_trunc01(shft_lt, shft_rt) * stddev + mean;
}

double TruncatedGauss::likeli(const double& x) {
  if(!is_like_ok) {
    coef = 1.0 / (stddev * sqrt_2PI) * inv_mid_cdf;
    is_like_ok = true;
  }
  return coef * std::exp(scale * (x - mean) * (x - mean));
}

double TruncatedGauss::loglikeli(const double& x) {
  if(!is_loglike_ok) {
    log_coef = - std::log(stddev * sqrt_2PI) - log(mid_cdf);
    is_loglike_ok = true;
  }
  return scale * (x - mean) * (x - mean) + log_coef;
}

} /* namespace random */
} /* namespace swift */
