#include<stdexcept>

#include<matrix.hh>

using namespace std;
using namespace gsw;

void
matrix::validate_matrixes( const matrix& other ) const{
  if( mData.size()    != other.mData.size()
   || mData[0].size() != other.mData[0].size() ){
    throw std::invalid_argument( "mismatched dimensions" );
  }
}

matrix::matrix( dim_t width, dim_t height ):
  mData( width, vector<data_t>( height ) ){
}

matrix::matrix( vector<vector<data_t> > data ):
  mData( data ){
}

const matrix::data_t&
matrix::operator()( dim_t x, dim_t y ) const{
  return mData[x][y];
}

matrix::data_t&
matrix::operator()( dim_t x, dim_t y ){
  return mData[x][y];
}

matrix&
gsw::operator*=( matrix& lhs, const matrix& rhs ){
  lhs.validate_matrixes( rhs.transpose() );

  return lhs;
}

matrix&
gsw::operator/=( matrix& lhs, const matrix& rhs ){
  lhs.validate_matrixes( rhs.transpose() );

  return lhs;
}

matrix&
gsw::operator*=( matrix& lhs, const matrix::data_t& rhs ){
  for( auto& row : lhs.mData ){
    for( auto& val : row ){
      val *= rhs;
    }
  }

  return lhs;
}

matrix&
gsw::operator/=( matrix& lhs, const matrix::data_t& rhs ){
  for( auto& row : lhs.mData ){
    for( auto& val : row ){
      val /= rhs;
    }
  }

  return lhs;
}

matrix
gsw::operator*( matrix::data_t lhs, const matrix& rhs ){
  return rhs * lhs;
}

matrix
gsw::operator/( matrix::data_t lhs, const matrix& rhs ){
  return lhs * rhs.transpose();
}

matrix&
gsw::operator+=( matrix& lhs, const matrix& rhs ){
  lhs.validate_matrixes( rhs );

  for( unsigned long i = 0; i < lhs.mData.size(); ++i ){
    for( unsigned long j = 0; i < lhs.mData[i].size(); ++j ){
      lhs.mData[i][j] += rhs.mData[i][j];
    }
  }

  return lhs;
}

matrix&
gsw::operator-=( matrix& lhs, const matrix& rhs ){
  lhs.validate_matrixes( rhs );

  for( unsigned long i = 0; i < lhs.mData.size(); ++i ){
    for( unsigned long j = 0; j < lhs.mData[i].size(); ++j ){
      lhs.mData[i][j] -= rhs.mData[i][j];
    }
  }

  return lhs;
}

matrix
matrix::operator-() const{
  matrix m = *this;

  for( auto& row : m.mData ){
    for( auto& val : row ){
      val = -val;
    }
  }

  return m;
}

matrix
matrix::transpose() const{
  matrix m( mData[0].size(), mData.size() );

  for( unsigned long i = 0; i < mData.size(); ++i ){
    for( unsigned long j = 0; j < mData.size(); ++j ){
      m( j, i ) = (*this)( i, j );
    }
  }

  return m;
}

matrix
matrix::inverse() const{
  return *this;
}

void
matrix::set_size( dim_t x, dim_t y ){
  matrix m( x, y );

  (*this) = m;
}

