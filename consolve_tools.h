//
// Created by nagi on 19-3-1.
//

#ifndef CNNTRY_CONSOLVE_TOOLS_H
#define CNNTRY_CONSOLVE_TOOLS_H

#include <iostream>
#include <vector>
#include "struct_tools.h"

using std::vector;

conslv max_pooling(conslv tar,int pstep,int pdim)
{
	if((tar.d-pdim)%pstep!=0)
		tar.ex((tar.d-pdim)%pstep);
	int tim=(tar.d-pdim)/pstep+1;
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
					if (tar.self[ix + x][iy + y] > max)
						max = tar.self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=max;

		}
	}
	return tmp;
}

conslv arg_pooling(conslv tar,int pstep,int pdim)
{
	if((tar.d-pdim)%pstep!=0)
		tar.ex((tar.d-pdim)%pstep);
	int tim=(tar.d-pdim)/pstep+1;
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
						sum += tar.self[ix + x][iy + y];
				}
			}
			tmp.self[kx][ky]=sum/(pdim^2);

		}
	}
	return tmp;
}

conslv consolve(conslv tar,cslcore core,int pstep)
{
	if((tar.d-core.d)%pstep!=0)
		tar.ex((tar.d-core.d)%pstep);
	int tim=(tar.d-core.d)/pstep+1;
	conslv tmp;
	tmp.d=tim;
	tmp.ini();
	for(int ix=0,kx=0;ix<tim;ix+=pstep,kx++)
	{
		for(int iy=0,ky=0;iy<tim;iy+=pstep,ky++)
		{
			double sum=0;
			for (int x = 0; x < core.d; x++)
			{
				for (int y = 0; y < core.d; y++)
				{
					sum += (tar.self[ix + x][iy + y]*core.self[x][y]+core.pow);
				}
			}
			tmp.self[kx][ky]=sum;
		}
	}
	return tmp;
}


#endif //CNNTRY_CONSOLVE_TOOLS_H
