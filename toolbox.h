//
// Created by nagi on 19-3-2.
//

#ifndef CNNTRY_TOOLBOX_H
#define CNNTRY_TOOLBOX_H
#include <iostream>
#include <vector>
#include <sys/time.h>
using std::vector;

/* 初始化随机种子 */
void InitRand()
{
	//struct timeval tv;
	//gettimeofday(&tv,NULL);
	//unsigned t=tv.tv_usec;
	//srand(t+rand());
	srand(clock()+rand());
	//std::cout<<rand()<<std::endl;
}

double rdm(int N,int i)
{
	InitRand();
	double r=rand()%(N)/(double)(N);
	return r;
}

void vini(std::vector<int> &v,int n)
{
	for(int i=0;i<n;i++)
		v.push_back(0);
}

void vini(std::vector<double> &v,int n)
{
	for(int i=0;i<n;i++)
		v.push_back(0);
}

void vini(std::vector<std::vector<int>> &v,std::vector<int> &t,int n)
{
	for(int i=0;i<n;i++)
		v.push_back(t);
}

void vini(std::vector<std::vector<double>> &v,std::vector<double> &t,int n)
{
	for(int i=0;i<n;i++)
		v.push_back(t);
}

void vini(std::vector<std::vector<int>> &v,int n)
{
	std::vector<int> t;
	vini(t,n);
	for(int i=0;i<n;i++)
		v.push_back(t);
}
void vini(std::vector<std::vector<double>> &v,int n)
{
	std::vector<double> t;
	vini(t,n);
	for(int i=0;i<n;i++)
		v.push_back(t);
}

void vini(std::vector<int> &v,int n,int par)
{
	for(int i=0;i<n;i++)
		v.push_back(par);
}

void vini(std::vector<double> &v,int n,double par)
{
	for(int i=0;i<n;i++)
		v.push_back(par);
}


#endif //CNNTRY_TOOLBOX_H
