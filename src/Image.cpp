/*************************************************************************************************************/
/*                             The Frame is based on Pieter Peers's framework                                */
/*Date:06/13/2016                                                                                            */
/*Change:None                                                                                                */
/*Changed By: Xiaodan Zhu                                                                                    */
/*************************************************************************************************************/
#include <cassert>
#include <algorithm>
#include "Image.h"
#include "Matrix.h"
Image::Image(Image::size_type width,Image::size_type height):_width(width),_height(height),_data()
{
	_data.reset(new value_type[width*height]);
}

Image::Image(Image::size_type width,Image::size_type height,Image::const_reference col):
	Image(width,height)
{
	std::fill(begin(),end(),col);
}

Image::Image(const Image& img):Image(img.width(),img.height())
{
	std::copy(img.begin(),img.end(),begin());
}

Image::Image(Image&& img)
{
	_swap(img);
}

Image& Image::operator=(const Image& img)
{
	_assign(img);
	return *this;
}

Image& Image::operator=(Image&& img)
{
	_swap(img);
	return *this;
}

Image Image::copy(void) const
{
	Image img(_width,_height);
	img.setHead(_head.get(),_head_size);
	std::copy(begin()->begin(),end()->begin(),img.begin()->begin());
	return img;
}
Image Image::convolution(const float* kernel,int dim) const
{
	Image img(_width,_height,ColorRGB(0.0,0.0,0.0));
	img.setHead(_head.get(),_head_size);
	int c=(dim-1)/2;
	for(int i=0;i<_width;i++)
		for(int j=0;j<_height;j++)
			for(int p=0;p<dim;p++)
				for(int q=0;q<dim;q++)
				{
					int idx=i+c-p;
					int idy=j+c-q;
					if(idx>=0&&idx<_width&&idy>=0&&idy<_height)
					{
						img(i,j)+=(*this)(idx,idy)*kernel[q*dim+p];
					}
				}
	return img;
}
Image Image::merge(const Image& src,int s_top,int s_left,int s_wid,int s_hei,int d_top,int d_left) const
{
	Vecnd b(s_wid*s_hei,0.0f);
	Matrix A(s_wid*s_hei,s_wid*s_hei,0.0f);
	Image img=this->copy();
	/*-----------------------------------------------*/
	for(int i=0;i<_width;i++)
		for(int j=0;j<_height;j++)
		{
			img(i,j)=ColorRGB((*this)(i,j).g);
		}
	/*-----------------------------------------------*/
	for(int i=1;i<s_wid-1&&i<_width-d_left;i++)
		for(int j=1;j<s_hei-1&&j<_height-d_top;j++)
		{
			int p=d_left+i,sp=s_left+i;
			int q=d_top+j,sq=s_top+j;
			ColorRGB vpq(0.0f,0.0f,0.0f);
			if(sq-1>=0)
			{
				vpq+=src(sp,sq)-src(sp,sq-1);
			}
			if(sp-1>=0)
			{
				vpq+=src(sp,sq)-src(sp-1,sq);
			}
			if(sp+1<src.width())
			{
				vpq+=src(sp,sq)-src(sp+1,sq);
			}
			if(sq+1<src.height())
			{
				vpq+=src(sp,sq)-src(sp,sq+1);
			}
			b[j*s_wid+i]=vpq.g;

			if(q-1>=0)
			{
				A[j*s_wid+i][(j-1)*s_wid+i]=-1;
				A[j*s_wid+i][j*s_wid+i]+=1;
			}
			if(p-1>=0)
			{
				A[j*s_wid+i][j*s_wid+i-1]=-1;
				A[j*s_wid+i][j*s_wid+i]+=1;
			}
			if(p+1<_width)
			{
				A[j*s_wid+i][j*s_wid+i+1]=-1;
				A[j*s_wid+i][j*s_wid+i]+=1;
			}
			if(q+1<_height)
			{
				A[j*s_wid+i][(j+1)*s_wid+i]=-1;
				A[j*s_wid+i][j*s_wid+i]+=1;
			}

		}
	for(int i=0;i<s_wid&&i<_width-d_left;i++)
	{
		b[i]=(*this)(d_left+i,d_top).g;
		A[i][i]=1;
		if(d_top+s_hei-1<_height)
		{
			b[(s_hei-1)*s_wid+i]=(*this)(d_left+i,d_top+s_hei-1).g;
			A[(s_hei-1)*s_wid+i][(s_hei-1)*s_wid+i]=1;
		}
	}
	for(int i=0;i<s_hei&&i<_height-d_top;i++)
	{
		b[i*s_wid]=(*this)(d_left,d_top+i).g;
		A[i*s_wid][i*s_wid]=1;
		if(d_left+s_wid-1<_width)
		{
			b[i*s_wid+s_wid-1]=(*this)(d_left+s_wid-1,d_top+i).g;
			A[i*s_wid+s_wid-1][i*s_wid+s_wid-1]=1;
		}
	}

	Vecnd x=A.Jacobian(b);
	for(int i=0;i<s_wid&&i<_width-d_left;i++)
		for(int j=0;j<s_hei&&j<_height-d_top;j++)
		{
			img(d_left+i,d_top+j)=ColorRGB(x[j*s_wid+i]);
		}
	return img;
}
Image::iterator Image::begin(void)
{
	return _data.get();
}

Image::const_iterator Image::begin(void) const
{
	return _data.get();
}

Image::iterator Image::end(void)
{
	return _data.get()+size();
}

Image::const_iterator Image::end(void) const
{
	return _data.get()+size();
}

Image::size_type Image::width(void) const
{
	return _width;
}

Image::size_type Image::height(void) const
{
	return _height;
}

Image::size_type Image::size(void) const
{
	return _width*_height;
}

Image::reference Image::operator()(Image::size_type x,Image::size_type y)
{
	assert(x>=0&&x<_width);
	assert(y>=0&&y<_height);

	return _data[y*_width+x];
}

Image::const_reference Image::operator()(Image::size_type x,Image::size_type y) const
{
	assert(x>=0&&x<_width);
	assert(y>=0&&y<_height);

	return _data[y*_width+x];
}

void Image::_assign(const Image& img)
{
	if(&img==this) return;
	Image temp(img);
	_swap(temp);
}

void Image::_swap(Image& img)
{
	std::swap(_width,img._width);
	std::swap(_height,img._height);
	std::swap(_data,img._data);
	std::swap(_head_size,img._head_size);
	std::swap(_head,img._head);
}
