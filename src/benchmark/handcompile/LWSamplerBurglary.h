//
//  LWSamplerBurglary.h
//  swift
//
//  Created by Lei Li on 2/9/14.
//  Copyright (c) 2014 Lei Li. All rights reserved.
//

#pragma once

/*
 * LWSamplerUrnBall.h
 *
 *  Created on: Nov 21, 2013
 *      Author: leili
 */
#pragma once
#include <string>
#include <vector>
#include <map>

namespace lwsampler {
  
  class LWSamplerBurglary {
    
  public:
    LWSamplerBurglary();
    ~LWSamplerBurglary();
    void sample(int n); // take n samples
    void printResult();
    std::map<bool, double> getResult(); // the result is a mapping from int to probability
    
    
  private:
    double total_weight; // total weight
    std::vector<double> weights; // weights for each possible world
    std::vector<bool> ans; // answer for the query
    int loops = 1000000; // number of samples, by default 1million
    int cur_loop; // currently sampling which possible world?
    int mark_burglary; // mark for burglary
    bool value_burglary;
    int mark_earthquake;
    bool value_earthquake;
    int mark_alarm;
    bool value_alarm;
    int mark_johncalls;
    bool value_johncalls;
    int mark_marycalls;
    bool value_marycalls;
    bool get_burglary();
    bool get_earthquake();
    bool get_alarm();
    bool get_johncalls();
    bool get_marycalls();
    double likeli_johncalls();
    double likeli_marycalls();
    double observe_johncalls(bool v);
    double observe_marycalls(bool v);
    double set_evidence(); // initialize the observation
    void sample();
  };
  
  
  

} /* namespace lwsampler */


