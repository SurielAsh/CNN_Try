//
// Created by nagi on 19-3-1.
//

#ifndef CNNTRY_STRUCT_TOOLS_H
#define CNNTRY_STRUCT_TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include "othertools.h"
using std::vector;

struct conslv{
	vector<vector<double>> self;
	vector<double> fulink;
	int d;
	void ini();
	void ex(int ex);
	void max_pooling(int pstep,int pdim);
	void arg_pooling(int pstep,int pdim);
	void disnega_relu();
	void fulic();
};

void conslv::ini()
{
	vini(self,d);
}

void conslv::ex(int ex)
{
	vector<vector<double>> tmp;
	vini(tmp,d+ex);
	for(int i=0;i<d;i++)
	{
		for(int k=0;k<d;k++)
			tmp[i][k]=self[i][k];
	}
	self=tmp;
}

void conslv::max_pooling(int pstep,int pdim)
{
	if((d-pdim)%pstep!=0)
		ex((d-pdim)%pstep);
	int tim=(d-pdim)/pstep+1;
	conslv tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<tim;ix+=pstep,kx++)
	{
		for(int iy=0,ky=0;iy<tim;iy+=pstep,ky++)
		{
			double max = 0;
			for (int x = 0; x < pdim; x++)
			{
				for (int y = 0; y < pdim; y++)
				{
					if (self[ix + x][iy + y] > max)
						max = self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=max;

		}
	}
	self=tmp.self;
	d=tmp.d;
}

void conslv::arg_pooling(int pstep,int pdim)
{
	if((d-pdim)%pstep!=0)
		ex((d-pdim)%pstep);
	int tim=(d-pdim)/pstep+1;
	conslv tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<tim;ix+=pstep,kx++)
	{
		for(int iy=0,ky=0;iy<tim;iy+=pstep,ky++)
		{
			double sum = 0;
			for (int x = 0; x < pdim; x++)
			{
				for (int y = 0; y < pdim; y++)
				{
					sum += self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=sum/(pdim^2);

		}
	}
	self=tmp.self;
	d=tmp.d;
}


void conslv::disnega_relu()
{
	for(auto &a:self)
	{
		for(auto &k:a) {
			if (k < 0)
				k = 0;
		}
	}
}

void conslv::fulic()
{
	for(auto &a:self)
	{
		for(auto &k:a) {
			fulink.push_back(k);
		}
	}
}

struct cslcore{
	vector<vector<double>> self;
	int d,pow;
	void ini();
};

void cslcore::ini()
{
	vini(self,d);
	for(auto &a:self)
	{
		for(auto &k:a) {
			int tmp;
			tmp=rand()%10;
			tmp>4 ? k=0:k=1;
		}
	}
}

#endif //CNNTRY_STRUCT_TOOLS_H
