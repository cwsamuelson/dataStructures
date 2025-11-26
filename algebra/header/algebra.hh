#pragma once

// https://www.geeksforgeeks.org/engineering-mathematics/group-rings-and-fields-in-group-theory/#
// https://github.com/warlock-labs/noether?tab=readme-ov-file
// Semigroup: composition (*)
// Monoid: composition (*), and identity
// Group: composition (*), inverse (/), and identity (id)
// Ring: multiply (*), add (+), negate(-), multiplicative identity (id),
//       additive identity (zero)
// Field: multiply (*), inverse (/), add (+), negate (-), multiplicative
//        identity (id), additive identity (zero)

namespace flp {

template<typename Type>
concept Ring = true;
template<typename Type>
concept Field = true;
template<typename Type>
concept Group = true;
template<typename Type>
concept VectorSpace = true;
template<typename Type>
concept Module = true;
template<typename Type>
concept Monoid = true;
template<typename Type>
concept SemiGroup = true;
template<typename Type>
concept Magma = true;
template<typename Type>
concept Groupoid = true;

// others ....

} // namespace flp
