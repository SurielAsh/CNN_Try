#include <iostream>
#include <string>
#include <vector>
#include "toolbox.h"
#include "convolution_tools.h"
#include "image_processing.h"

using namespace std;

int main()
{
	int time=-1;
	int learn_time=10;
	double rslt=0;
	string name;
	string imagepath;
	convolution ori;
	vector<convlcore> vcore1;
	vector<vector<convlcore>> vcore2;
	vector<convolution> firstcvl;
	vector<convolution> seccvl;

	cout<<"被学习图片中的物体是：";
	cin>>name;

	head:
	rslt=0;
	time++;
	cout<<"这是第 "<<time+1<<" 次学习，距完成还需"<<9-time<<"次"<<endl;
	cin>>imagepath;
	ori.self=getimg_grayscale(imagepath.data());
	ori.ini();

	int number_of_core=5;
	if(time==0) {
		vini(vcore1,number_of_core);
		for (auto core:vcore1) {
			core.d = 7;
			core.ini();
		}
	}

	firstcvl=convoluting(ori,vcore1,5);

	for(auto cvl:firstcvl)
	{
		cvl.relu();
	}

	if(time==0) {
		vini(vcore2, number_of_core);
		for (auto vcore:vcore2) {
			for (auto core:vcore) {
				core.d = 5;
				core.ini();
			}
		}
	}

	for(int i=0;i<firstcvl.size();i++)
	{
			vector<convolution> temp=convoluting(firstcvl[i],vcore2[i],3);
			for(auto cvl:temp)
			{
				seccvl.push_back(cvl);
			}
	}

	for(auto cvl:seccvl)
	{
		cvl.max_pooling(2,3);
		vini(cvl.weight,cvl.size());
		rslt+=cvl.fulc();
	}

	int vs=seccvl.size();

	for(int i=0;i<vs;i++)
		seccvl.pop_back();

	if(time<learn_time)
		goto head;

	cout<<"学习已完成，请输入验证图片"<<endl;
	cin>>imagepath;
	ori.self=getimg_grayscale(imagepath.data());
	ori.ini();
	firstcvl=convoluting(ori,vcore1,5);
	for(auto cvl:firstcvl)
	{
		cvl.relu();
	}
	for(int i=0;i<firstcvl.size();i++)
	{
		vector<convolution> temp=convoluting(firstcvl[i],vcore2[i],3);
		for(auto cvl:temp)
		{
			seccvl.push_back(cvl);
		}
	}
	for(auto cvl:seccvl)
	{
		cvl.max_pooling(2,3);
		vini(cvl.weight,cvl.size());
		rslt+=cvl.fulc();
	}
	cout<<"该图片中物品为 "<<name<<" 的概率是"<<rslt*100<<"%"<<endl;

	return 0;
}