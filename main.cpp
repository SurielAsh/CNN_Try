#include <iostream>
#include <string>
#include <vector>
#include "toolbox.h"
#include "consolve_tools.h"

using namespace std;

int main()
{
	int dim,cstep,core_dim,pstep,pooling_dim;
	dim=64;
	cstep=2;
	core_dim=3;
	pstep=2;
	pooling_dim=3;
	conslv ori,ori_1,ori_2;
	cslcore core_1,core_2,core_3,core_4;
	ori.d=dim;
	ori_1.d=dim;
	ori_2.d=dim;
	ori.ini();
	ori_1.ini();
	ori_2.ini();
	core_1.d=core_dim+2;
	core_2.d=core_dim+2;
	core_3.d=core_dim;
	core_4.d=core_dim;
	core_1.pow=0;
	core_2.pow=1;
	core_3.pow=0;
	core_4.pow=0;
	core_1.ini();
	core_2.ini();
	core_3.ini();
	core_4.ini();
	ori_1=consolve(ori,core_1,cstep);
	ori_2=consolve(ori,core_2,cstep);
	ori_1.disnega_relu();
	ori_2.disnega_relu();
	ori_1.max_pooling(pstep,pooling_dim);
	ori_2.max_pooling(pstep,pooling_dim);
	ori_1=consolve(ori_1,core_3,cstep);
	ori_2=consolve(ori_2,core_4,cstep);
	ori_1.disnega_relu();
	ori_2.disnega_relu();
	ori_1.max_pooling(pstep,pooling_dim);
	ori_2.max_pooling(pstep,pooling_dim);
	ori_1.fulic();
	ori_2.fulic();
	return 0;
}