#ifndef VECND_H
#define VECND_H

#include <memory>
#include <iostream>

class Vecnd
{
	public:
	typedef float value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
        typedef std::unique_ptr<value_type[]>::pointer iterator;
	typedef std::unique_ptr<const value_type[]>::pointer const_iterator;

	Vecnd(size_t n=0,value_type val=0.0f);
	Vecnd(const Vecnd& v);
	Vecnd(Vecnd&& v);

	~Vecnd(void)
	{
		_data.reset();
	}
	Vecnd& operator=(const Vecnd& v);

	reference operator[](size_t idx);
	const_reference operator[](size_t idx) const;

	size_t size() const{return _size;}

	iterator begin(void);
	iterator end(void);
	const_iterator begin(void) const;
	const_iterator end(void) const;

	Vecnd operator+(const Vecnd& v) const;
	Vecnd operator-(const Vecnd& v) const;
	Vecnd operator*(const Vecnd& v) const;
	Vecnd operator*(const_reference scale) const;
	Vecnd operator/(const Vecnd& v) const;
	Vecnd operator/(const_reference scale) const;

	Vecnd& operator+=(const Vecnd& v);
	Vecnd& operator-=(const Vecnd& v);
	Vecnd& operator*=(const Vecnd& v);
	Vecnd& operator*=(const_reference scale);
	Vecnd& operator/=(const Vecnd& v);
	Vecnd& operator/=(const_reference scale);
	Vecnd operator-(void) const;

	value_type dot(const Vecnd& v) const;
	value_type dist(const Vecnd& v) const;
	value_type squared_dist(const Vecnd& v) const;

	friend Vecnd operator*(const_reference scale, const Vecnd& v)
	{
		return Vecnd(v)*scale;
	}

	friend std::ostream& operator<<(std::ostream& s,const Vecnd& v)
	{
		for(size_t i=0;i<v._size;i++)
		{
			s<<v[i]<<" ";
		}
		return s;
	}
	friend void swap(Vecnd& a,Vecnd& b)
	{
		a._swap(b);
	}
	private:
	
	void _assign(const Vecnd& v);
	void _swap(Vecnd& v);

	size_t _size;
	std::unique_ptr<value_type[]> _data;	
};
#endif
