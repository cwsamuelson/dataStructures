#include<cmath>
#include<algorithm>

#include<logic.hh>
#include <utility>

using namespace std;
using namespace gsw;

/**************
 * operations *
 **************/
/***********
 * helpers *
 ***********/
set<string> invert(const set<string>& operand, set<string> variables) {
  for(const auto& op : operand) {
    if(variables.count(op)) {
      variables.erase(variables.find(op));
    }
  }

  return variables;
}

/************
 * variable *
 ************/
bool proposition::variable::evaluate(const set<string>& facts) const {
  return facts.count(name) > 0;
}

set<set<string>> proposition::variable::solve(const set<string>& data) const {
  // this throws in some confusion.  what to do if this variable doesn't exist in
  //  the variables to be solved on?
  set<set<string>> assignments;
  size_t max = pow(2, data.size());

  // mask used to describe which elements from data should be tested
  // and is then incremented to retrieve the next 'permutation'
  for(size_t mask = 0; mask < max; ++mask) {
    set<string> test;

    // each element of data is mapped to a bit in mask
    // each bit is tested, and each respective variable is added appropriately
    size_t j = 1;
    for(const auto& var : data) {
      if(j & mask) {
        test.insert(var);
      }
      j <<= 1;
    }

    // once a set of values from variables is generated, add this var, and save it
    test.insert(name);
    assignments.insert(test);
  }

  return assignments;
}

/***************
 * conjunction *
 ***************/
bool proposition::conjunction::evaluate(const set<string>& facts) const {
  return lhs->evaluate(facts) && rhs->evaluate(facts);
}

set<set<string>> proposition::conjunction::solve(const set<string>& data) const {
  auto lhs_data = lhs->solve(data);
  auto rhs_data = rhs->solve(data);
  set<set<string>> result;

  set_intersection(lhs_data.begin(),
                   lhs_data.end(),
                   rhs_data.begin(),
                   rhs_data.end(),
                   inserter(result, result.begin()));

  return result;
}

/***************
 * disjunction *
 ***************/
bool proposition::disjunction::evaluate(const set<string>& facts) const {
  return lhs->evaluate(facts) || rhs->evaluate(facts);
}

set<set<string>> proposition::disjunction::solve(const set<string>& data) const {
  auto lhs_data = lhs->solve(data);
  auto rhs_data = rhs->solve(data);
  set<set<string>> result;

  set_union(lhs_data.begin(), lhs_data.end(), rhs_data.begin(), rhs_data.end(), inserter(result, result.begin()));

  return result;
}

/*************************
 * exclusive disjunction *
 *************************/
bool proposition::exDisjunction::evaluate(const set<string>& facts) const {
  return lhs->evaluate(facts) ^ rhs->evaluate(facts);
}

set<set<string>> proposition::exDisjunction::solve(const set<string>& data) const {
  auto lhs_data = lhs->solve(data);
  auto rhs_data = rhs->solve(data);
  set<set<string>> result;

  // set_symmetric_difference is insufficient.  by way of example:
  // truth table for A^(A||B):
  // | A | B || A^(A||B)|
  // |---|---||---------|
  // | 0 | 0 ||    0    |
  // | 0 | 1 ||    1    |
  // | 1 | 0 ||    0    |
  // | 1 | 1 ||    0    |
  // using set_symmetric_difference this is solved as:
  // solve( lhs ) == A
  // solve( rhs ) == A, B, AB
  // set_symmetric_difference( lhs, rhs ) == B, AB
  // this leaves AB as a solution, but this is an invalid solution, as A cannot
  //  be part of a solution, and is in fact ignored in this equation
  set_symmetric_difference(lhs_data.begin(),
                           lhs_data.end(),
                           rhs_data.begin(),
                           rhs_data.end(),
                           inserter(result, result.begin()));

  return result;
}

/************
 * negation *
 ************/
bool proposition::negation::evaluate(const set<string>& facts) const {
  return !operand->evaluate(facts);
}

set<set<string>> proposition::negation::solve(const set<string>& data) const {
  auto solutions = operand->solve(data);
  set<set<string>> result;

  for(const auto& solution : solutions) {
    result.insert(invert(solution, data));
  }

  return result;
}

/***************
 * proposition *
 ***************/
proposition::proposition(op_ptr value)
        : mValue(std::move(value)) {
}

proposition proposition::operator&&(const proposition& conjunct) const {
  auto var = make_shared<proposition::conjunction>();

  var->lhs = mValue;
  var->rhs = conjunct.mValue;

  return proposition{ var };
}

proposition proposition::operator||(const proposition& disjunct) const {
  auto var = make_shared<proposition::disjunction>();

  var->lhs = mValue;
  var->rhs = disjunct.mValue;

  return proposition{ var };
}

proposition proposition::operator^(const proposition& operand) const {
  auto var = make_shared<proposition::exDisjunction>();

  var->lhs = mValue;
  var->rhs = operand.mValue;

  return proposition{ var };
}

proposition proposition::operator!() const {
  auto var = make_shared<proposition::negation>();

  var->operand = mValue;

  return proposition{ var };
}

proposition proposition::implies(const proposition& consequent) const {
  return !(*this) || consequent;
}

proposition proposition::iff(const proposition& equivalent) const {
  return this->implies(equivalent) && equivalent.implies(*this);
}

bool proposition::evaluate(const set<string>& facts) const {
  return mValue->evaluate(facts);
}

set<set<string>> proposition::solve(const set<string>& variables) const {
  set<set<string>> solutions;
  size_t max = pow(2, variables.size());

  // mask used to describe which elements from variables should be tested
  // and is then incremented to retrieve the next 'permutation'
  for(size_t mask = 0; mask < max; ++mask) {
    set<string> test;

    // each element of variables is mapped to a bit in mask
    // each bit is tested, and each element of variables is added appropriately
    size_t j = 1;
    for(auto var : variables) {
      if(j & mask) {
        test.insert(std::move(var));
      }
      j <<= 1;
    }

    // once a set of values from variables is generated, test it
    if(evaluate(test)) {
      solutions.insert(std::move(test));
    }
  }

  return solutions;
}

set<set<string>> proposition::solve2(const set<string>& variables) const {
  return mValue->solve(variables);
}

proposition gsw::operator ""_lvar(const char* name, size_t sz) {
  auto var = make_shared<proposition::variable>();

  var->name = string(name, sz);

  return proposition{ var };
}
