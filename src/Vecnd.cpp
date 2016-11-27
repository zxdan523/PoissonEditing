#include <algorithm>
#include <cassert>
#include <cmath>
#include "Vecnd.h"


Vecnd::Vecnd(size_t n,value_type val)
{
	_data.reset(new value_type[n]);
	_size=n;
	std::fill(begin(),end(),val);
}
Vecnd::Vecnd(const Vecnd& v):Vecnd(v.size())
{
	std::copy(v.begin(),v.end(),begin());
}
Vecnd::Vecnd(Vecnd&& v)
{
	_swap(v);
}
Vecnd& Vecnd::operator=(const Vecnd& v)
{
	_assign(v);
	return *this;
}

Vecnd::reference Vecnd::operator[](size_t idx)
{
	assert(idx<_size);
	return *(_data.get()+idx);
}
Vecnd::const_reference Vecnd::operator[](size_t idx) const
{
	assert(idx<_size);
	return *(_data.get()+idx);
}
Vecnd::iterator Vecnd::begin(void)
{
	return _data.get();
}
Vecnd::iterator Vecnd::end(void)
{
	return _data.get()+_size;
}
Vecnd::const_iterator Vecnd::begin(void) const
{
	return _data.get();
}
Vecnd::const_iterator Vecnd::end(void) const
{
	return _data.get()+_size;
}
Vecnd Vecnd::operator+(const Vecnd& v) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),v.begin(),result.begin(),[](const_reference a,const_reference b)
			{
				return a+b;
			});
	return result;
}
Vecnd Vecnd::operator-(const Vecnd& v) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),v.begin(),result.begin(),[](const_reference a,const_reference b)
			{
				return a-b;
			});
	return result;
}
Vecnd Vecnd::operator*(const Vecnd& v) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),v.begin(),result.begin(),[](const_reference a,const_reference b)
			{
				return a*b;
			});
	return result;
}
Vecnd Vecnd::operator*(Vecnd::const_reference scale) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),result.begin(),[&](const_reference a)
			{
				return a*scale;
			});
	return result;
}
Vecnd Vecnd::operator/(const Vecnd& v) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),v.begin(),result.begin(),[](const_reference a,const_reference b)
			{
				return a/b;
			});
	return result;
}
Vecnd Vecnd::operator/(Vecnd::const_reference scale) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),result.begin(),[&](const_reference a)
			{
				return a/scale;
			});
	return result;
}
Vecnd& Vecnd::operator+=(const Vecnd& v)
{
	std::transform(begin(),end(),v.begin(),begin(),[](const_reference a,const_reference b)
			{
				return a+b;
			});
	return *this;
}
Vecnd& Vecnd::operator-=(const Vecnd& v)
{
	std::transform(begin(),end(),v.begin(),begin(),[](const_reference a,const_reference b)
			{
				return a-b;
			});
	return *this;
}
Vecnd& Vecnd::operator*=(const Vecnd& v)
{
	std::transform(begin(),end(),v.begin(),begin(),[](const_reference a,const_reference b)
			{
				return a*b;
			});
	return *this;
}
Vecnd& Vecnd::operator*=(Vecnd::const_reference scale)
{
	std::for_each(begin(),end(),[&](reference a)
			{
				a*=scale;
			});
	return *this;
}
Vecnd& Vecnd::operator/=(const Vecnd& v)
{
	std::transform(begin(),end(),v.begin(),begin(),[](const_reference a,const_reference b)
			{
				return a/b;
			});
	return *this;
}
Vecnd& Vecnd::operator/=(Vecnd::const_reference scale)
{
	std::for_each(begin(),end(),[&](reference a)
			{
				a/=scale;
			});
	return *this;
}
Vecnd Vecnd::operator-(void) const
{
	Vecnd result(_size);
	std::transform(begin(),end(),result.begin(),[](const_reference a)
			{
				return -1*a;
			});
	return result;

}
Vecnd::value_type Vecnd::dot(const Vecnd& v) const
{
	value_type result=0.0f;
	for(size_t i=0;i<_size;i++)
	{
		result+=v[i]*(*this)[i];
	}
	return result;
}

Vecnd::value_type Vecnd::dist(const Vecnd& v) const
{
	value_type result=0.0;
	Vecnd d=(*this)-v;
	std::for_each(d.begin(),d.end(),[&](const_reference a)
			{
				result+=a*a;
			});
	return sqrt(result);
}
Vecnd::value_type Vecnd::squared_dist(const Vecnd& v) const
{
	value_type result=0.0;
	Vecnd d=(*this)-v;
	std::for_each(d.begin(),d.end(),[&](const_reference a)
			{
				result+=a*a;
			});
	return result;
}
void Vecnd::_assign(const Vecnd& v)
{
	if(this==&v)
	{
		return;
	}
	Vecnd temp(v);
	_swap(temp);
}
void Vecnd::_swap(Vecnd& v)
{
	std::swap(_data,v._data);
	std::swap(_size,v._size);
}

