#ifndef __MATRIX_HH__
#define __MATRIX_HH__

#include<vector>
#include<tuple>

#include<operators.hh>
#include<normal_iterator.hh>

namespace gsw {

class matrix
        : public gsw::multiplicative<matrix>
          , gsw::multiplicative<matrix, double>
          , gsw::multiplicative<double, matrix>
          , gsw::additive<matrix> {
public:
  using dim_t = unsigned long;
  using data_t = double;
  using iterator = normal_iterator<data_t, matrix>;

private:
  std::vector<std::vector<data_t>> mData;

  void validate_matrixes(const gsw::matrix& two) const;

public:
  /*!
   *
   * @param width
   *
   * @param height
   */
  matrix(dim_t width, dim_t height);

  /*!
   *
   * @param data
   */
  matrix(std::vector<std::vector<data_t>> data);

  /*!
   *
   * @param width
   *
   * @param height
   */
  const data_t& operator()(dim_t x, dim_t y) const;

  /*!
   *
   * @param width
   *
   * @param height
   */
  data_t& operator()(dim_t x, dim_t y);

  /*!
   */
  matrix operator-() const;

  /*!
   */
  matrix transpose() const;

  /*!
   */
  matrix inverse() const;

  /*!
   *
   * @param width
   *
   * @param height
   */
  void set_size(dim_t x, dim_t y);

  /*!
   *
   * @param width
   *
   * @param height
   */
  std::tuple<dim_t, dim_t> size() const;

  /*!
   */
  matrix splice(dim_t x, dim_t y) {
  }

  /*!
   */
  iterator begin() {
  }

  /*!
   */
  iterator end() {
  }

  /*!
   */
  iterator xbegin() {
  }

  /*!
   */
  iterator xend() {
  }

  /*!
   */
  iterator ybegin() {
  }

  /*!
   */
  iterator yend() {
  }

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator*=(matrix& lhs, const matrix& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator/=(matrix& lhs, const matrix& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator*=(matrix& lhs, const data_t& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator/=(matrix& lhs, const data_t& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator*=(data_t lhs, const matrix& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator/=(data_t lhs, const matrix& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator+=(matrix& lhs, const matrix& rhs);

  /*!
   *
   * @param lhs
   *
   * @param rhs
   */
  friend matrix& operator-=(matrix& lhs, const matrix& rhs);
};

matrix& operator*=(matrix& lhs, const matrix& rhs);

matrix& operator/=(matrix& lhs, const matrix& rhs);

matrix& operator*=(matrix& lhs, const matrix::data_t& rhs);

matrix& operator/=(matrix& lhs, const matrix::data_t& rhs);

matrix& operator*=(matrix::data_t lhs, const matrix& rhs);

matrix& operator/=(matrix::data_t lhs, const matrix& rhs);

matrix& operator+=(matrix& lhs, const matrix& rhs);

matrix& operator-=(matrix& lhs, const matrix& rhs);

}

#endif

