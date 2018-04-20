#include<stdexcept>

#include<matrix.hh>

using namespace std;

void
validate_matrixes( const matrix& one, const matrix& two ){
  if( one.mData.size()    != two.mData.size()
   || one.mData[0].size() != two.mData[0].size() ){
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
operator*=( matrix& lhs, const matrix& rhs ){
  validate_matrixes( lhs, rhs.transpose() );

}

matrix&
operator/=( matrix& lhs, const matrix& rhs ){
  validate_matrixes( lhs, rhs.transpose() );

}

matrix&
operator*=( matrix& lhs, const matrix::data_t& rhs ){
  for( auto& row : lhs.mData ){
    for( auto& val : row ){
      val *= rhs;
    }
  }
}

matrix&
operator/=( matrix& lhs, const matrix::data_t& rhs ){
  for( auto& row : lhs.mData ){
    for( auto& val : row ){
      val /= rhs;
    }
  }
}

matrix
operator*( matrix::data_t lhs, const matrix& rhs ){
  return rhs * lhs;
}

matrix
operator/( matrix::data_t lhs, const matrix& rhs ){
  return lhs * rhs.transpose();
}

matrix&
operator+=( matrix& lhs, const matrix& rhs ){
  validate_matrixes( lhs, rhs );

  for( unsigned long i = 0; i < lhs.mData.size(); ++i ){
    for( unsigned long j = 0; i < lhs.mData[i].size(); ++j ){
      lhs.mData[i][j] += rhs.mData[i][j];
    }
  }
}

matrix&
operator-=( matrix& lhs, const matrix& rhs ){
  validate_matrixes( lhs, rhs );

  for( unsigned long i = 0; i < lhs.mData.size(); ++i ){
    for( unsigned long j = 0; j < lhs.mData[i].size(); ++j ){
      lhs.mData[i][j] -= rhs.mData[i][j];
    }
  }
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
}

void
matrix::set_size( dim_t x, dim_t y ){
  matrix m( x, y );

  (*this) = m;
}

