//
//  TestCategorical.cpp
//  swift-project
//
//  Created by Lei Li on 1/19/14.
//
//

#include <iostream>
#include <map>
#include "../../random/CategoricalDistribution.h"
using namespace std;

int main() {
  swift::random::Categorical cat;
  cat.init(std::map<int, double>({{0, 0.1}, {1, 0.9}}));
  int x[2] = {0, 0};
  for (int i=0; i < 1000; i++)
    x[cat.gen()]++;
  cout << "0:" << x[0] / 1000.0 << endl;
  cout << "1:" << x[1] / 1000.0 << endl;
}