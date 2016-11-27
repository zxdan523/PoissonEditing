#include <algorithm>
#include <cassert>
#include "Matrix.h"

Matrix::Matrix(size_t m,size_t n,Vecnd::value_type val)
{
	_data.reset(new Vecnd[m]);
	for(size_t i=0;i<m;i++)
	{
		_data[i]=Vecnd(n,val);
	}
	_m=m;
	_n=n;
}
Matrix::Matrix(const Matrix& mat):Matrix(mat.row(),mat.column())
{
	std::copy(mat.begin(),mat.end(),begin());
}
Matrix::Matrix(Matrix&& mat)
{
	_swap(mat);
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	_assign(mat);
	return *this;
}

Matrix::reference Matrix::operator[](size_t idx)
{
	assert(idx<_m);
	return *(_data.get()+idx);
}
Matrix::const_reference Matrix::operator[](size_t idx) const
{
	assert(idx<_m);
	return *(_data.get()+idx);
}
Matrix::iterator Matrix::begin(void)
{
	return _data.get();
}
Matrix::iterator Matrix::end(void)
{
	return _data.get()+_m;
}
Matrix::const_iterator Matrix::begin(void) const
{
	return _data.get();
}
Matrix::const_iterator Matrix::end(void) const
{
	return _data.get()+_m;
}

Matrix::value_type Matrix::operator*(const Vecnd& v) const
{
	Vecnd result(_m);
	std::transform(begin(),end(),result.begin(),[&](const_reference a)
			{
				return a.dot(v);
			});
	return result;
}
Matrix::value_type Matrix::Jacobian(const Vecnd& v) const
{
	Vecnd x(_n,0.0f);
	Vecnd y=(*this)*x;
	while(y.squared_dist(v)>1e-3)
	{
		int k=0;
		std::for_each(x.begin(),x.end(),[&](Vecnd::reference a)
				{
					a*=(*this)[k][k];
					k++;
				});

		x=(v-y+x);
		int i=0;
		std::for_each(x.begin(),x.end(),[&](Vecnd::reference a)
				{
					a/=(*this)[i][i];
					i++;
				});
		y=(*this)*x;
		std::cout<<y.squared_dist(v)<<std::endl;
	}
	return x;
}
void Matrix::_assign(const Matrix& mat)
{
	Matrix temp(mat);
	_swap(temp);
}
void Matrix::_swap(Matrix& mat)
{
	std::swap(_data,mat._data);
	std::swap(_m,mat._m);
	std::swap(_n,mat._n);
}

