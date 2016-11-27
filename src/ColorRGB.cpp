/*************************************************************************************************************/
/*                             The Frame is based on Pieter Peers's framework                                */
/*Date:06/13/2016                                                                                            */
/*Change:None                                                                                                */
/*Changed By: Xiaodan Zhu                                                                                    */
/*************************************************************************************************************/
#include <cassert>
#include <algorithm>
#include "ColorRGB.h"

ColorRGB::ColorRGB(void)
{
	r=g=b=0.0;
}

ColorRGB::ColorRGB(ColorRGB::const_reference r,ColorRGB::const_reference g,ColorRGB::const_reference b)
{
	this->r=r;
	this->g=g;
	this->b=b;
}
ColorRGB::ColorRGB(ColorRGB::const_reference v)
{
	this->r=v;
	this->g=v;
	this->b=v;
}
ColorRGB::ColorRGB(ColorRGB::const_iterator cp)
{
	this->r=cp[0];
	this->g=cp[1];
	this->b=cp[2];
}

ColorRGB::ColorRGB(const ColorRGB& c)
{
	_assign(c);
}

ColorRGB& ColorRGB::operator=(const ColorRGB& c)
{
	_assign(c);
	return *this;
}

ColorRGB& ColorRGB::operator=(ColorRGB::const_iterator cp)
{
	this->r=cp[0];
	this->g=cp[1];
	this->b=cp[2];
	return *this;
}

ColorRGB::reference ColorRGB::operator[](size_t item)
{
	assert(item>=0&&item<3);
	return data[item];
}

ColorRGB::const_reference ColorRGB::operator[](size_t item) const
{
	assert(item>=0&&item<3);
	return data[item];
}

ColorRGB::iterator ColorRGB::begin(void)
{
	return data;
}

ColorRGB::const_iterator ColorRGB::begin(void) const
{
	return data;
}

ColorRGB::iterator ColorRGB::end(void)
{
	return data+3;
}

ColorRGB::const_iterator ColorRGB::end(void) const
{
	return data+3;
}

ColorRGB ColorRGB::operator+(const ColorRGB& c) const
{
	return ColorRGB(r+c.r,g+c.g,b+c.b);
}

ColorRGB ColorRGB::operator-(const ColorRGB& c) const
{
	return ColorRGB(r-c.r,g-c.g,b-c.b);
}

ColorRGB ColorRGB::operator*(const ColorRGB& c) const
{
	return ColorRGB(r*c.r,g*c.g,b*c.b);
}

ColorRGB ColorRGB::operator*(ColorRGB::const_reference scale) const
{
	return ColorRGB(scale*r,scale*g,scale*b);
}

ColorRGB ColorRGB::operator/(const ColorRGB& c) const
{
	return ColorRGB(r/c.r,g/c.g,b/c.b);
}

ColorRGB ColorRGB::operator/(ColorRGB::const_reference scale) const
{
	return ColorRGB(r/scale,g/scale,b/scale);
}

ColorRGB& ColorRGB::operator+=(const ColorRGB& c)
{
	r+=c.r;g+=c.g;b+=c.b;
	return *this;
}

ColorRGB& ColorRGB::operator-=(const ColorRGB& c)
{
	r-=c.r;g-=c.g;b-=c.b;
	return *this;
}

ColorRGB& ColorRGB::operator*=(const ColorRGB& c)
{
	r*=c.r;g*=c.g;b*=c.b;
	return *this;
}

ColorRGB& ColorRGB::operator*=(ColorRGB::const_reference scale)
{
	r*=scale; g*=scale; b*=scale;
	return *this;
}

ColorRGB& ColorRGB::operator/=(const ColorRGB& c)
{
	r/=c.r;g/=c.g;b/=c.b;
	return *this;
}

ColorRGB& ColorRGB::operator/=(ColorRGB::const_reference scale)
{
	r/=scale; g/=scale; b/=scale;
	return *this;
}

bool ColorRGB::operator==(const ColorRGB& c) const
{
	return (r==c.r)&&(g==c.g)&&(b==c.b);
}

bool ColorRGB::operator!=(const ColorRGB& c) const
{
	return (r!=c.r)||(g!=c.g)||(b!=c.b);
}

ColorRGB::value_type ColorRGB::magnitude(void) const
{
	return sqrt(r*r+g*g+b*b);
}

ColorRGB::value_type ColorRGB::squared_magnitude(void) const
{
	return r*r+g*g+b*b;
}

ColorRGB::value_type ColorRGB::difference(const ColorRGB& c) const
{
	ColorRGB diff=(*this)-c;
	return diff.magnitude();
}

ColorRGB::value_type ColorRGB::squared_difference(const ColorRGB& c) const
{
	ColorRGB diff=(*this)-c;
	return diff.squared_magnitude();
}

ColorRGB& ColorRGB::clamp(const_reference lower,const_reference upper)
{
	std::for_each(begin(),end(),[&](reference v)
			{
		             if(v<lower)
			     {
			         v=lower;
			     }
			     else if(v>upper)
			     {
			         v=upper;
			     }
			});
	return *this;
}

void ColorRGB::_assign(const ColorRGB& c)
{
	if(&c==this)
	{
		return;
	}
	r=c.r;
	g=c.g;
	b=c.b;
}

void ColorRGB::_swap(ColorRGB& c)
{
	std::swap(r,c.r);
	std::swap(g,c.g);
	std::swap(b,c.b);
}
