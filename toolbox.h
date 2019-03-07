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
	srand(time(0)+rand());
	//std::cout<<rand()<<std::endl;
}

double rdm(int N)
{
	InitRand();
	return rand()%(N)/(double)(N);
}

template <typename T>
void vini(vector<T> &v,int n,T par)
{
	for(int i=0;i<n;i++)
		v.push_back(par);
}

template <typename T>
void vini(vector<T> &v,int n)
{
	T par;
	for(int i=0;i<n;i++)
		v.push_back(par);
}

template <typename T>
void vini(vector<vector<T>> &v,vector<T> &t,int n)
{
	for(int i=0;i<n;i++)
		v.push_back(t);
}

template <typename T>
void vini(vector<vector<T>> &v,int n)
{
	vector<T> t;
	vini(t,n);
	for(int i=0;i<n;i++)
		v.push_back(t);
}

inline double derevition (double(*fun)(double,double),double rslt,double thr)
{
	return (fun(rslt+0.000000000001,thr)-fun(rslt,thr))/0.000000000001;
}
/*void vini(std::vector<int> &v,int n)
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
}*/


#endif //CNNTRY_TOOLBOX_H
