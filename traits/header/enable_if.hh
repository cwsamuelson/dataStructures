#ifndef __ENABLE_IF_HH__
#define __ENABLE_IF_HH__

/*!
 * @example test-traits.cc
 */

namespace gsw {

/*! SFINAE utility
 *
 * @tparam B Enabling condition
 *
 * @tparam T effective type when B is true
 *
 * This version of the template is used when B is false, as well as declares
 * enable_if template.
 */
template<bool B, typename T = void>
class enable_if {};

/*! SFINAE enabled utility
 *
 * @tparam T effective type
 *
 * enable_if takes a compile time condition in the B template parameter. If the
 * condition is true, this specialization is used, which provides type. If the
 * template version is used, type will not be provided, which creates a
 * substitution failure, eliminating that function from selection.
 */
template<typename T>
class enable_if<true, T> {
public:
  using type = T;
};

}

#endif
