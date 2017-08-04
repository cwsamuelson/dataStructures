#ifndef __REMOVE_CV_HH__
#define __REMOVE_CV_HH__

namespace gsw{

/*! Removes const qualifier
 *
 * @tparam
 *
 * This class is used when remove_const is used with a class that doesn't have
 * a const qualifier, so the provided class is presented through type as is.
 */
template<typename T>
class remove_const{
public:
  using type = T;
};

/*! Removes const qualifier
 *
 * @tparam
 *
 * This class is  a template specialization and is used when remove_const is
 * used with a class that does have a const qualifier, so the provided class is
 * presented through type with the const qualifier stripped. 
 */
template<typename T>
class remove_const<const T>{
public:
  using type = T;
};

/*! Removes volatile qualifier
 *
 * @tparam
 *
 * This class is used when remove_volatile is used with a class that doesn't
 * have a volatile qualifier, so the provided class is presented through type
 * as is.
 */
template<typename T>
class remove_volatile{
public:
  using type = T;
};

/*! Removes volatile qualifier
 *
 * @tparam
 *
 * This class is a template specialization and is used when remove_volatile is
 * used with a class that does have a volatile qualifier, so the provided class
 * is presented through type with the volatile qualifier stripped. 
 */
template<typename T>
class remove_volatile<volatile T>{
public:
  using type = T;
};

/*! Removes const and volatile qualifiers
 *
 * @tparam
 *
 * Utilizes remove_const and remove_volatile to remove const and volatile
 * qualifiers.
 */
template<typename T>
class remove_cv{
public:
  using type = typename remove_const<typename remove_volatile<T>::type>::type;
};

}

#endif

