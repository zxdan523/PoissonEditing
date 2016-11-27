/*************************************************************************************************************/
/*                             The Frame is based on Pieter Peers's framework                                */
/*Date:06/13/2016                                                                                            */
/*Change:None                                                                                                */
/*Changed By: Xiaodan Zhu                                                                                    */
/*************************************************************************************************************/
#ifndef IMAGE_H
#define IMAGE_H

#include <ostream>
#include <memory>
#include <algorithm>
#include "ColorRGB.h"

class Image
{
	public:
	typedef ColorRGB value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::unique_ptr<value_type[]>::pointer iterator;
	typedef std::unique_ptr<const value_type[]>::pointer const_iterator;
	typedef size_t size_type;

	Image(size_type width=0,size_type height=0);
	Image(size_type width,size_type height,const_reference col);
	Image(const Image& img);
	Image(Image&& img);

	~Image(void)
	{
		_data.reset();
	}

	Image copy(void) const;
        iterator begin(void);
	const_iterator begin(void) const;

	iterator end(void);
	const_iterator end(void) const;

        size_type width(void) const;
	size_type height(void) const;
	size_type size(void) const;

	Image& operator=(const Image& img);
	Image& operator=(Image&& img);

	Image convolution(const float* kernel,int dim) const;
	Image merge(const Image& src,int s_top,int s_left,int s_wid,int s_hei,int d_top,int d_left) const;

	const uint8_t* getHead(){_head.get();}
	void setHead(uint8_t* head,int size)
	{
		_head_size=size;
		_head.reset(new uint8_t[size]);
		std::copy(head,head+size,_head.get());
	}
	reference operator()(size_type x,size_type y);
	const_reference operator()(size_type x,size_type y) const;

	friend void swap(Image& a,Image& b)
	{
		a._swap(b);
	}

	friend std::ostream& operator<<(std::ostream& s,const Image& img)
	{
		s<<"Image:("<<img.width()<<","<<img.height()<<")";
		return s;
	}

	protected:

	void _assign(const Image& img);
	void _swap(Image& img);

	private:
	size_type _width,_height;
	std::unique_ptr<value_type[]> _data;
	std::unique_ptr<uint8_t[]> _head;
	int _head_size;
};
#endif

