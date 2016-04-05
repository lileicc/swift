//
//  MCMC.h
//  swift-project
//  general framework for MCMC algorithms (Parental MH, Gibbs)
//
//  Created by Yi Wu on 4/14/15.
//
//

#pragma once

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <random>
#include <array>

namespace swift {

int _cur_loop = 0;

class MCMCObject {
protected:
  static std::default_random_engine engine;
  static std::uniform_real_distribution<double> uni_r_dist;
public:
  MCMCObject() { list_pos = -1; }
  int list_pos;
  virtual void mcmc_resample() = 0;
  virtual double getlikeli() = 0;
  virtual double getcachelikeli() = 0;
  // degenerate all edges from its parent when we erase this var OR 
  //   one of its contingent vars changes val
  virtual void remove_edge() {};
  // generate all edges from its parent when this node is instantiated
  //   TODO: only need to do this during initialization and modification of contingent vars
  virtual void active_edge() {};
  virtual std::string getname() = 0;
};

// Initialization
std::default_random_engine MCMCObject::engine = std::default_random_engine();
std::uniform_real_distribution<double> MCMCObject::uni_r_dist = std::uniform_real_distribution<double>(0.0,1.0);

// Table that contains all the vars active in the current world and are not observed
std::vector<MCMCObject*> _active_list;

inline void mcmc_sample_single_iter() {
  // TODO: to use some other random number generator??
  int pos = rand() % _active_list.size();
  auto node = _active_list[pos];
  node->mcmc_resample();
}

// Methods for adding/removing var to active_list
inline void add_var_to_list(MCMCObject* node) { // assert(node not in active_list)
  // assert(node->list_pos == -1);
  node->list_pos = (int)_active_list.size();
  _active_list.push_back(node);
}
inline void remove_var_from_list(MCMCObject* node) { // assert(node is in active_list)
  // assert(node->list_pos > -1);
  // assert(node->list_pos > -1 && node->list_pos<_active_list.size() && _active_list[node->list_pos] == node);

  int p = node->list_pos;
  _active_list[p] = _active_list.back();
  _active_list[p]->list_pos = p;
  node->list_pos = -1;
  _active_list.pop_back();
}

template<class Tp>
class BayesVar : public MCMCObject {
public:
  std::vector<double> all_weis; // TODO: do we need to get rid of it?

  std::set<MCMCObject*> child;  // variables that depend on this var
  std::set<MCMCObject*> contig; // variables that are contingent on this var
  std::set<MCMCObject*> backup; // temporary storage

  inline void add_contig(MCMCObject* var) {
    contig.insert(var);
  }

  inline void erase_contig(MCMCObject* var) {
    contig.insert(var);
  }

  inline void add_child(MCMCObject* var) {
    child.insert(var);
  }

  inline void erase_child(MCMCObject* var) {
    child.insert(var);
  }

  Tp val;
  bool is_obs;
  bool is_active; // if a var is active and not observed, it is in active_list

  BayesVar() { is_obs = is_active = false; is_cached = -1; }

  // for Caching values
  //   Gibbs sampling may generate temporal samples for weight computation
  Tp cache_val;
  int is_cached;
  virtual Tp& getcache_arg(BayesVar* cur_node);
  virtual Tp& getcache() = 0;
  virtual void cache_cur_val() { cache_val = val; is_cached = (is_active ? _cur_loop : -1); } // when not active, we DO NOT cache val
  virtual void clear_cache() { is_cached = -1; }

  // Uninstantiate Active Node
  virtual void clear_arg(BayesVar* cur_node);
  virtual void clear() = 0;

  virtual bool check_obs() { return true; }
  virtual void update_obs(bool flag) {}; // for contingent var associated with obs

  // this method only does the sampling process, NO graph maintainance.
  // For graph maintainance, we need to invoke getval()
  // BUT will ensure the initialization of variables
  virtual void sample() = 0;
  virtual void sample_cache() = 0;
  virtual inline void ensure_cache() {
    sample_cache();
    is_cached = _cur_loop;
  }

  std::vector<Tp> all_vals; // containing all possible values
  // TODO: add method so that it can return a range of integer/real
  //       possibly <support analysis> ?
  virtual std::vector<Tp>& get_all_vals() { return all_vals; };

  // ensure support
  Tp& getval_arg(BayesVar* cur_node);
  virtual inline Tp& getval() = 0;
  virtual void clear_reference() {}; // optional for var returning an object with num-st
  virtual void update_reference() {}; // optional for var returning an object with num-st
  virtual int get_reference_diff(Tp from, Tp to) { return 0; }; // get the number of variables to activate of val varies

  // main resample process
  /*
    w_i <- w_i * P( Y_new_value | Y_new_parents  ) / P( Y_old_value | Y_old_parent  )
  */
  virtual void gibbs_resample_arg(BayesVar* cur_node);
  virtual void mh_parent_resample_arg(BayesVar* curnode);
  virtual void conjugacy_analysis(Tp& nxt_val) {}; // to be filled later for conjugacy analysis
  virtual void conjugate_gibbs_resample_arg(BayesVar* curnode);

  virtual std::string getname() { return ""; }
};

template<class Tp>
Tp& BayesVar<Tp>::getcache_arg(BayesVar* cur_node) {
  if (cur_node->is_active)
    return cur_node->val;

  if (cur_node->is_cached != _cur_loop) {
    cur_node->sample_cache();

    cur_node->is_cached = _cur_loop;
  }
  return cur_node->cache_val;
}

template<class Tp>
Tp& BayesVar<Tp>::getval_arg(BayesVar* cur_node) {
  if (!cur_node->is_active) {

    if (cur_node->is_cached == _cur_loop) {
      cur_node->val = cur_node->cache_val;
      cur_node->is_cached = -1; // fetch cache and clear it
    }
    else
      cur_node->sample();

    cur_node->is_active = true;

    add_var_to_list(cur_node); // add to active_list

    // add dependency edges
    cur_node->update_reference(); // only has content when returning an object!
    cur_node->active_edge(); // generate graph
  }
  return cur_node->val;
}

template<class Tp>
void BayesVar<Tp>::clear_arg(BayesVar* cur_node) {
  if (!cur_node->is_active) return;

  // remove from active_list
  if (!cur_node->is_obs)
    remove_var_from_list(cur_node);
  cur_node->is_active = false;

  // We DO NOT clear cache here

  // clear graph: NO RECURSION
  //  TODO: possibly recurssive???? how to temporarily remove all properties of an object in OUPMs?????
  cur_node->child.clear(); // out-edges
  cur_node->contig.clear();
  cur_node->clear_reference(); // only has content when returning an object

  // remove all edges
  cur_node->remove_edge(); // in-edges
}

template<class Tp>
void BayesVar<Tp>::gibbs_resample_arg(BayesVar* cur_node) {
  auto& child = cur_node->child;
  std::vector<Tp>&values = cur_node->get_all_vals();
  Tp old_val = cur_node->val, nxt_val;
  all_weis.resize(values.size());
  int active_n = _active_list.size();
  double basic = 0;
  for (size_t i = 0; i < all_weis.size(); ++i) {
    double &w = all_weis[i];
    nxt_val = values[i];
    cur_node->val = nxt_val;
    // First is associated with observations
    // check observations
    if (nxt_val != old_val) {
      if (!cur_node->check_obs()) {
        w = 10000;
        continue;
      }
    }

    // TODO: *IMPORTANT* [ assume close-world here ]
    w = cur_node->getcachelikeli(); // equivalent to getlikeli() in close-world case
    for (auto &c : child) {
      //if (c->is_parent(cur_node)) // always parent
      w += c->getcachelikeli(); // make sure it is supported: equivalent to getlikeli() in close-world case
      // TODO: for open-universe, here we need to maintain the total number of active variables
      // *IMPORTANT* *TODO* :
      //   when this is a contigent var, some new var might be cached!!!!
    }
    if (nxt_val == old_val) {
      w -= std::log(active_n);
      basic = w;
    }
    else
      w -= std::log(active_n + cur_node->get_reference_diff(old_val, nxt_val));
  }

  for (auto&w : all_weis) {
    if (w > 1000) w = 0;
    else w = std::exp(w - basic);
  }

  // resample part
  for (size_t i = 1; i < all_weis.size(); ++i)
    all_weis[i] += all_weis[i - 1];

  double loc = uni_r_dist(engine) * all_weis.back(); // TODO: *IMPORTANT* simplified for close-world case here
  nxt_val = values[std::lower_bound(all_weis.begin(), all_weis.end(), loc) - all_weis.begin()];

  cur_node->val = old_val;
  if (nxt_val == old_val) return ;

  cur_node->update_obs(false);
  if (contig.size() > 0) {
    backup = contig;
    
    for (auto&c : backup) {
      c->remove_edge();
    }

    cur_node->clear_reference();  // only has content when this returns an object

    cur_node->val = nxt_val;

    cur_node->update_reference(); // only has content when this returns an object

    for (auto&c : backup) {
      c->active_edge();
    }
  } else
    cur_node->val = nxt_val;
  cur_node->update_obs(true); // TODO: in open-world, if there are some new var instantiated, we need to ensure support!

  // in normal cases, there is no cache val
  cur_node->clear_cache();

}

template<class Tp>
void BayesVar<Tp>::mh_parent_resample_arg(BayesVar* cur_node) {
  auto& child = cur_node->child;
  Tp old_val = cur_node->val;

  double old_w = 0;
  for (auto&c : child)
    old_w += c->getlikeli();
  old_w -= std::log(_active_list.size());

  double nxt_w = 0;
  cur_node->is_active = false;
  cur_node->sample_cache();
  cur_node->is_cached = _cur_loop; // mark cache_flag
  Tp nxt_val = cur_node->cache_val;
  cur_node->is_active = true;
  if (nxt_val == old_val) return ;

  cur_node->val = nxt_val;

  if (!cur_node->check_obs()) {
    return;
  }

  for (auto&c : child)
    nxt_w += c->getcachelikeli();
  nxt_w -= std::log(_active_list.size() + cur_node->get_reference_diff(old_val, nxt_val));
  cur_node->is_active = true;

  cur_node->clear_cache();
  

  double alpha = std::min(1.0, std::exp(nxt_w - old_w));
  double loc = uni_r_dist(engine);
  bool acceptance = (loc <= alpha);

  if (acceptance) { // accept
    cur_node->val = old_val;
    cur_node->update_obs(false);

    if (contig.size() > 0) {
      backup = contig;
      for (auto&c : backup) {
        c->remove_edge();
      }

      cur_node->clear_reference();  // only has content when this returns an object

      cur_node->val = nxt_val;

      cur_node->update_reference(); // only has content when this returns an object

      for (auto&c : backup) {
        c->active_edge();
      }
    } else 
       cur_node->val = nxt_val;

    cur_node->update_obs(true); // TODO: in open-world, if there are some new var instantiated, we need to ensure support!
  }
  else cur_node->val = old_val; // reject

}

template<class Tp>
void BayesVar<Tp>::conjugate_gibbs_resample_arg(BayesVar* cur_node) {
  Tp nxt_val;
  cur_node->conjugacy_analysis(nxt_val); // sample from true posterior with conjugacy

  cur_node->update_obs(false);
  if (contig.size() > 0) {
    backup = contig;
    for (auto&c : backup) {
      c->remove_edge();
    }

    cur_node->clear_reference();  // only has content when this returns an object

    cur_node->val = nxt_val;

    cur_node->update_reference(); // only has content when this returns an object

    for (auto&c : backup) {
      c->active_edge();
    }
  }
  else
    cur_node->val = nxt_val;

  cur_node->update_obs(true); // TODO: in open-world, if there are some new var instantiated, we need to ensure support!
}

/////////////////////////////////////
// Number Variable
/////////////////////////////////////

class NumberVar : public BayesVar<int> {
public:

  int capacity; // maximum value in history
  NumberVar() : capacity(0) {};

  std::vector<int> refer_cnt; // reference number for each objects
  std::vector<int> active_obj; // all objects with at least one reference
  std::vector<int> obj_pos; // possition of objects in active_obj

  std::set<BayesVar<int>*> dep_var; // all the variables that return an object of this type

  // gibbs usage
  std::vector<int> tar; // storage for a mapping
  std::vector<int> pick; // reverse map: TODO: probably change to map<int,int> for memory efficiency??

  // cache all the properties of current prop, and then uninstatiate them
  //    when is_full_clear == true, we invoke clear(), otherwise, we only mark the flag: is_active <- true
  virtual void clear_prop_arg(int k) = 0; // Note: some property might NOT be instantiated!
  virtual void clear_prop() {
    for (auto& k : active_obj) {
      clear_prop_arg(k);
    }
  };

  virtual void ensure_support_prop_arg(int i) = 0; // instantiate property of object_i (sample / init from cached val)
  virtual void ensure_cache_prop_arg(int i) = 0; // sample cache value of property of object_i and mark its flag true

  // special getval()/getcache() for number variable (need to invoke ensure_size())
  virtual int& getval_numvar_arg(NumberVar* cur_node);
  virtual int& getcache_numvar_arg(NumberVar* cur_node);

  // ensure all the storage vectors for properties have sufficient size
  virtual void ensure_size(int n) = 0; // need to specify!

  // Number of properties (random functions) related this this type
  virtual inline int get_property_size() { return 0; }

  // main resample process for number variable
  virtual void mcmc_resample_numvar_arg(NumberVar* cur_node);

  virtual void mh_parent_resample_numvar_arg(NumberVar* cur_node);
};

int& NumberVar::getval_numvar_arg(NumberVar* cur_node) {
  if (!cur_node->is_active) {
    // clear reference
    dep_var.clear(); // in normal case, it should be already cleared
    active_obj.clear();

    if (cur_node->is_cached == _cur_loop) {
      cur_node->val = cur_node->cache_val;
      cur_node->is_cached = -1; // clear cache
    }
    else
      cur_node->sample();

    cur_node->ensure_size(cur_node->val); // ensure vector size of properties
    refer_cnt.resize(cur_node->val);
    obj_pos.resize(cur_node->val); // NOTE: for convenience, we do not mark them -1
    std::fill(refer_cnt.begin(), refer_cnt.end(), 0); // do not shrink?? possibly yes

    cur_node->is_active = true;
    add_var_to_list(cur_node); // add to active_list

    // add dependency edges
    cur_node->active_edge();
  }
  return cur_node->val;
}

int& NumberVar::getcache_numvar_arg(NumberVar* cur_node) {
  if (cur_node->is_active)
    return cur_node->val;

  if (cur_node->is_cached != _cur_loop) {
    cur_node->sample_cache();
    cur_node->is_cached = _cur_loop;

    if (cur_node->cache_val > refer_cnt.size()) { // only increase here!
      refer_cnt.resize(cur_node->cache_val);
      obj_pos.resize(cur_node->cache_val);
      cur_node->ensure_size(cur_node->cache_val); // ensure vector size of properties
    }
  }
  return cur_node->cache_val;
}

void NumberVar::mcmc_resample_numvar_arg(NumberVar* cur_node) {
  // DO NOTHING..... to be filled later
}

void NumberVar::mh_parent_resample_numvar_arg(NumberVar* cur_node) {

  //resample number_var, dep_var
  // instantiate and uninstantiate some properties
  //compute likelihood of vars depending on dep_var and numbervar
  std::set<MCMCObject*> cond;
  for (auto&c : cur_node->child) {
    if (dep_var.find(dynamic_cast<BayesVar<int>*>(c)) == dep_var.end())
      cond.insert(c);
  }
  int old_val = cur_node->val;
  double old_w = 0, nxt_w = 0; // log likelihood
  int prop_size = cur_node->get_property_size();
  int old_active_n = _active_list.size();

  // compute old probability
  old_w = cur_node->getlikeli();
  for (auto &u : dep_var) {
    for (auto&c : u->child) {
      if (cond.find(c) == cond.end()) {
        cond.insert(c);
        old_w += c->getlikeli();
      }
    }
  }

  // compute probability of the proposed world
  //    mark all the related vars not active
  cur_node->is_active = false;
  for (auto& u : dep_var)
    u->is_active = false;

  // sample new values
  cur_node->sample_cache();
  cur_node->is_cached = _cur_loop;
  int nxt_val = cur_node->cache_val; // proposed number var

  int m = active_obj.size();
  int nxt_active_n = _active_list.size() - m * prop_size;

  cur_node->ensure_size(nxt_val);
  int sz = std::max(old_val, nxt_val);
  pick.resize(sz); std::fill(pick.begin(), pick.end(), 0);
  for (auto &j : active_obj)
    pick[j] = 1; // already exists in the old world
  tar.clear(); // all the objects that needs to be instantiated

  for (auto& u : dep_var) {
    u->sample_cache();
    u->is_cached = _cur_loop;

    int t = u->cache_val;
    if (!pick[t]) {
      tar.push_back(t);
      cur_node->ensure_cache_prop_arg(t); // sample_cache and mark is_cache flag true for each property var
    }
    if (pick[t] != 2) {
      nxt_active_n += prop_size;
      pick[t] = 2;
    }
  }

  // compute probablity
  nxt_w = cur_node->getcachelikeli();
  for (auto&c : cond) {
    nxt_w += c->getcachelikeli();
  }

  // recover flag of is_active
  cur_node->is_active = true;
  for (auto&u : dep_var) u->is_active = true;

  // compute acceptance ratio
  old_w -= std::log(old_active_n);
  nxt_w -= std::log(nxt_active_n);

  bool acceptance;
  double alpha = std::min(std::exp(nxt_w - old_w), 1.0);
  double rd = uni_r_dist(engine);
  acceptance = (rd <= alpha);

  if (acceptance) { // accept
    // ensure vector length
    refer_cnt.resize(nxt_val);
    std::fill(refer_cnt.begin(), refer_cnt.end(), 0);
    if (nxt_val > obj_pos.size())
      obj_pos.resize(nxt_val);
    // ensure support and instantiate all the required vars
    for (auto &j : tar)
      cur_node->ensure_support_prop_arg(j);
    // find out all the vars to uninstatiate
    tar.clear(); // all the objects to uninstantiate
    for (auto &j : active_obj) {
      if (pick[j] == 1) tar.push_back(j);
    }
    // update references, active_obj, obj_pos
    // update values of all the resampled vars
    active_obj.clear();
    for (auto& u : dep_var) {
      int t = u->cache_val;
      if (++refer_cnt[t] == 1) { // update references
        obj_pos[t] = active_obj.size();
        active_obj.push_back(t);
      }

      u->update_obs(false); // TODO: to support general evidence contigency!
      if (u->contig.size() > 0) {
        backup = u->contig;
        
        for (auto&c : backup) {
          c->remove_edge();
        }
        u->val = t;
        for (auto&c : backup) {
          c->active_edge();
        }
      }
      else
        u->val = t;

      u->update_obs(true); // need to make sure support!
      u->clear_cache();
    }

    cur_node->update_obs(false);
    if (contig.size() > 0) {
      backup = contig;
      
      for (auto&c : backup) {
        c->remove_edge();
      }
      cur_node->val = nxt_val;
      for (auto&c : backup) {
        c->active_edge();
      }
    }
    else {
      // set value
      cur_node->val = nxt_val;
    }
    cur_node->update_obs(true); // need to make sure support!
    cur_node->clear_cache();

    // uninstantiate redundant properties
    for (auto& j : tar) {
      cur_node->clear_prop_arg(j);
    }
  }
  else { // reject
    // DO NOTHING!
  }

}

}

