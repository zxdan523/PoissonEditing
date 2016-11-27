/*************************************************************************************************************/
/*                             The Frame is based on Pieter Peers's framework                                */
/*Date:06/12/2016                                                                                            */
/*Change:None                                                                                                */
/*Changed By: Xiaodan Zhu                                                                                    */
/*************************************************************************************************************/
#ifndef COLOR_RGB_H
#define COLOR_RGB_H	

#include <ostream>
#include <cmath>

class ColorRGB
{
	public:
	typedef float value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;

	union
	{
		struct{value_type r,g,b;};
		value_type data[3];
	};

	ColorRGB(void);
	ColorRGB(const_reference r,const_reference g,const_reference b);
	ColorRGB(const_reference v);
	ColorRGB(const_iterator cp);
	ColorRGB(const ColorRGB& c);

	ColorRGB& operator=(const ColorRGB& c);
	ColorRGB& operator=(const_iterator cp);

	reference operator[](size_t item);
	const_reference operator[](size_t item) const;
	iterator begin(void);
	const_iterator begin(void) const;
	iterator end(void);
	const_iterator end(void) const;

	ColorRGB operator+(const ColorRGB& c) const;
	ColorRGB operator-(const ColorRGB& c) const;
	ColorRGB operator*(const ColorRGB& c) const;
	ColorRGB operator*(const_reference scale) const;
	ColorRGB operator/(const ColorRGB& c) const;
	ColorRGB operator/(const_reference scale) const;

	ColorRGB& operator+=(const ColorRGB& c);
	ColorRGB& operator-=(const ColorRGB& c);
	ColorRGB& operator*=(const ColorRGB& c);
	ColorRGB& operator*=(const_reference scale);
	ColorRGB& operator/=(const ColorRGB& c);
	ColorRGB& operator/=(const_reference scale);

	bool operator==(const ColorRGB& c) const;
	bool operator!=(const ColorRGB& c) const;

	value_type magnitude(void) const;
	value_type squared_magnitude(void) const;
	value_type difference(const ColorRGB& c) const;
	value_type squared_difference(const ColorRGB& c) const;

	ColorRGB& clamp(const_reference lower=0.0,const_reference upper=1.0);

	friend ColorRGB operator*(const_reference scale, const ColorRGB& c)
	{
		return c*scale;
	}

	friend void swap(ColorRGB& a,ColorRGB& b)
	{
		a._swap(b);
	}

	friend ColorRGB clamp(const ColorRGB& a,const_reference lower=0.0,const_reference upper=1.0)
	{
		return ColorRGB(a).clamp(lower,upper);
	}
        
	friend std::ostream& operator<<(std::ostream& s,const ColorRGB& c)
	{
		s<<"("<<c.r<<","<<c.g<<","<<c.b<<")";
		return s;
	}
	private:
	void _assign(const ColorRGB& c);
	void _swap(ColorRGB& c);
};

#endif

