#ifndef __MATRIX_HH__
#define __MATRIX_HH__

#include<vector>

#include<operators.hh>

class matrix : public gsw::multiplicative<matrix>,
                      gsw::multiplicative<matrix, double>,
                      gsw::additive<matrix>{
public:
  using dim_t = unsigned long;
  using data_t = double;

private:
  std::vector<std::vector<data_t> > mData;

public:
  /*!
   *
   * @param width
   *
   * @param height
   */
  matrix( dim_t width, dim_t height );

  /*!
   *
   * @param data
   */
  matrix( std::vector<std::vector<data_t> > data );

  /*!
   *
   * @param width
   *
   * @param height
   */
  const data_t&
  operator()( dim_t x, dim_t y ) const;

  /*!
   *
   * @param width
   *
   * @param height
   */
  data_t&
  operator()( dim_t x, dim_t y );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator*=( matrix& lhs, const matrix& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator/=( matrix& lhs, const matrix& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator*=( matrix& lhs, const data_t& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator/=( matrix& lhs, const data_t& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix
  operator*( data_t lhs, const matrix& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix
  operator/( data_t lhs, const matrix& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator+=( matrix& lhs, const matrix& rhs );

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend
  matrix&
  operator-=( matrix& lhs, const matrix& rhs );

  /*!
   */
  matrix
  operator-() const;

  /*!
   */
  matrix
  transpose() const;

  /*!
   */
  matrix
  inverse() const;

  /*!
   *
   * @param width
   *
   * @param height
   */
  void
  set_size( dim_t x, dim_t y );

  friend
  void
  validate_matrixes( const matrix& one, const matrix& two );
};

matrix&
operator*=( matrix& lhs, const matrix& rhs );

matrix&
operator/=( matrix& lhs, const matrix& rhs );

matrix&
operator*=( matrix& lhs, const matrix::data_t& rhs );

matrix&
operator/=( matrix& lhs, const matrix::data_t& rhs );

matrix
operator*( matrix::data_t lhs, const matrix& rhs );

matrix
operator/( matrix::data_t lhs, const matrix& rhs );

matrix&
operator+=( matrix& lhs, const matrix& rhs );

matrix&
operator-=( matrix& lhs, const matrix& rhs );

#endif

