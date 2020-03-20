#ifndef __OPERATORS_HH__
#define __OPERATORS_HH__

/*!
 * @example test-operators.cc
 */

/*!
 * @class additive
 * @class multiplicative
 *
 * These operators should not handle commutativity
 * This is because the second operator template parameter defaults to the first
 * this causes the second set of functions that handle commutativity to error as
 * redefinitions.
 * This means that the sub-classes inheriting from these classes should handle
 * specifying commutativity.
 */
#include<additive.hh>
#include<multiplicative.hh>
#include<comparitive.hh>

#endif

