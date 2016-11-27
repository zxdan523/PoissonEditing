#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <ostream>
#include "Vecnd.h"
class Matrix
{
	public:
	typedef Vecnd value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::unique_ptr<value_type[]>::pointer iterator;
	typedef const std::unique_ptr<value_type[]>::pointer const_iterator;

	Matrix(size_t m=0,size_t n=0,Vecnd::value_type val=0.0f);
	Matrix(const Matrix& mat);
	Matrix(Matrix&& mat);

	~Matrix(void)
	{
		_data.reset();
	}
	Matrix& operator=(const Matrix& mat);
	size_t column() const{return _n;}
	size_t row() const{return _m;}

	iterator begin(void);
	iterator end(void);
	const_iterator begin(void) const;
	const_iterator end(void) const;


	reference operator[](size_t idx);
	const_reference operator[](size_t idx) const;

	value_type operator*(const Vecnd& v) const;
	value_type Jacobian(const Vecnd& v) const;	
	friend std::ostream& operator<<(std::ostream& s,const Matrix& mat)
	{
		for(size_t i=0;i<mat._m;i++)
		{
			s<<mat[i]<<"\n";
		}
		return s;
	}
	friend void swap(Matrix& a,Matrix& b)
	{
		a._swap(b);
	}
	private:
	void _assign(const Matrix& mat);
	void _swap(Matrix& mat);

	size_t _m,_n;
	std::unique_ptr<value_type[]> _data;
};
#endif
