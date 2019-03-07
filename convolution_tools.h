//
// Created by nagi on 19-3-1.
//

#ifndef CNNTRY_STRUCT_TOOLS_H
#define CNNTRY_STRUCT_TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include "toolbox.h"
using std::vector;

struct convolution{
	int d;
	convolution()= default;
	vector<vector<double>> self;
	vector<double> fulcnet;
	vector<double> weight;
	void ini();
	void ex(int ex);
	void max_pooling(int step,int dim);
	void arg_pooling(int step,int dim);
	void relu();
	double fulc();
	void pre_fulc();
	int size()
	{
		return self.size();
	}
};

void convolution::ini()
{
	if(self.size()==0)
		vini(self,d);
	else
		d=self.size();
}

void convolution::ex(int ex)
{
	vector<vector<double>> tmp;
	vini(tmp,d+ex);
	for(int i=0;i<d;i++)
	{
		for(int k=0;k<d;k++)
			tmp[i+(ex/2)][k+(ex/2)]=self[i][k];
	}
	self=tmp;
}

void convolution::max_pooling(int step,int dim)
{
	if((d-dim)%step!=0)
		ex((d-dim)%step);
	int tim=(d-dim)/step+1;
	convolution tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<=d-dim;ix+=step,kx++)
	{
		for(int iy=0,ky=0;iy<=d-dim;iy+=step,ky++)
		{
			int max = 0;
			for (int x = 0; x < dim; x++)
			{
				for (int y = 0; y < dim; y++)
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

void convolution::arg_pooling(int step,int dim)
{
	if((d-dim)%step!=0)
		ex((d-dim)%step);
	int tim=(d-dim)/step+1;
	convolution tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<=d-dim;ix+=step,kx++)
	{
		for(int iy=0,ky=0;iy<=d-dim;iy+=step,ky++)
		{
			int sum = 0;
			for (int x = 0; x < dim; x++)
			{
				for (int y = 0; y < dim; y++)
				{
					sum += self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=sum/(dim*dim);

		}
	}
	self=tmp.self;
	d=tmp.d;
}

void convolution::relu()
{
	for(auto &a:self)
	{
		for(auto &k:a) {
			if (k < 0)
				k = 0;
		}
	}
}

double convolution::fulc()
{
	double sum;
	for(auto &a:self)
	{
		for(auto &k:a) {
			fulcnet.push_back(k);
		}
	}
	for(int i;i<fulcnet.size();i++)
	{
		sum+=fulcnet[i]*weight[i];
	}
	return sum;
}

void convolution::pre_fulc()
{
	vini(weight,fulcnet.size());
}

struct convlcore{
	convlcore ()= default;
	vector<vector<double>> self;
	int d,bias;
	void ini();
};

void convlcore::ini()
{
	InitRand();
	vini(self,d);
	for(auto &a:self)
	{
		for(auto &k:a) {
			k=rand()%3-1;
		}
	}
}

convolution max_pooling(convolution tar,int pstep,int pdim)
{
	if((tar.d-pdim)%pstep!=0)
		tar.ex((tar.d-pdim)%pstep);
	int tim=(tar.d-pdim)/pstep+1;
	convolution tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<=tar.d-pdim;ix+=pstep,kx++)
	{
		for(int iy=0,ky=0;iy<=tar.d-pdim;iy+=pstep,ky++)
		{
			int max = 0;
			for (int x = 0; x < pdim; x++)
			{
				for (int y = 0; y < pdim; y++)
				{
					if (tar.self[ix + x][iy + y] > max)
						max = tar.self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=max;

		}
	}
	return tmp;
}

convolution arg_pooling(convolution tar,int step,int dim)
{
	if((tar.d-dim)%step!=0)
		tar.ex((tar.d-dim)%step);
	int tim=(tar.d-dim)/step+1;
	convolution tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<=tar.d-dim;ix+=step,kx++)
	{
		for(int iy=0,ky=0;iy<=tar.d-dim;iy+=step,ky++)
		{
			int sum = 0;
			for (int x = 0; x < dim; x++)
			{
				for (int y = 0; y < dim; y++)
				{
					sum += tar.self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=sum/(dim*dim);

		}
	}
	return tmp;
}

convolution single_convoluting(convolution target, convlcore core, int step)
{
	if((target.d-core.d)%step!=0)
		target.ex((target.d-core.d)%step);
	int tim=(target.d-core.d)/step+1;
	convolution result;
	vini(result.self,tim);
	for(int ix=0,kx=0;ix<=target.d-core.d;ix+=step,kx++)
	{
		for(int iy=0,ky=0;iy<=target.d-core.d;iy+=step,ky++)
		{
			int sum=0;
			for (int x = 0; x < core.d; x++)
			{
				for (int y = 0; y < core.d; y++)
				{
					sum += (target.self[ix + x][iy + y]*core.self[x][y]+core.bias);
				}
			}
			result.self[kx][ky]=sum;
		}
	}
	return result;
}

vector<convolution> convoluting(convolution target,vector<convlcore> corelist,int step)
{
	vector<convolution> result;
	for(int i=0;i<corelist.size();i++)
	{
		result.push_back(single_convoluting(target,corelist[i],step));
	}
	return result;
}

inline double loss(double result,double thr_value)
{
	return 0.5*(thr_value-result)*(thr_value-result);
}


#endif //CNNTRY_STRUCT_TOOLS_H
