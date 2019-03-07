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
	int core_num=1;
	int layers=1;
	int learn_time=50;
	double rslt=0;
	double e_1o=100000000;
	string name="clion";
	string imagepath="clion.png";
	convolution ori;
	vector<vector<convlcore>> vcore;
	vector<vector<convolution>> cvl;

	double e_1;
	vector<double> e_2;
	vector<convlcore> e_3;
	vector<convolution> e_4;

	vector<double> weight;

	vini(vcore,1);

	for(auto &core:vcore) {
		//vini(core, core_num);
		for(auto &c:core) {
			c.d=5;
			c.bias=0;
			c.ini();
		}
	}
	vini(cvl,1);

	//cout<<"请输入要检测特征的名称：";
	//cin>>name;
	head:
	time++;
	inierr:
	if(time==0)
		e_1o=100000000;
	//cout<<"请输入参考图像的路径：";
	//cin>>imagepth;
	ori.self=getimg_grayscale(imagepath.data());
	ori.ini();
	cvl[0]=convoluting(ori,vcore[0],3);
	if(time!=0)
		cvl[0][0].weight=weight;
	cvl[0][0].relu();
	cvl[0][0].max_pooling(2,2);
	rslt=cvl[0][0].fulc();

	e_1 = derevition(loss, rslt, 99);
	//if((e_1*e_1)>(e_1o*e_1o)) {
	//	time=0;
	//	goto inierr;
	//}
	e_1o=e_1;
	//e_1=loss(rslt+0.00000000001,99)-/
	if(time==0) {
		vini(e_2, cvl[0][0].weight.size(), 0.);
	}
	for(int i=0;i<e_2.size();i++)
	{
		e_2[i]=e_1*(cvl[0][0].fulcnet[i]/cvl[0][0].fulcnet.size());
		if(e_2[i]<-100)
			e_2[i]=-5;
		cvl[0][0].weight[i]-=e_1*(cvl[0][0].fulcnet[i]/cvl[0][0].fulcnet.size());
	}
	weight=cvl[0][0].weight;
	cvl[0][0].repool(2,2,e_2);
	if(time==0) {
		vini(e_3, 1);
		vini(e_3[0].self,cvl[0][0].epool.size());
	}
	for(int x;x<cvl[0][0].epool.size();x++)
	{
		for(int y;y<cvl[0][0].epool.size();y++)
		{
			e_3[0].self[x][y]=cvl[0][0].epool[cvl[0][0].epool.size()-1-x][cvl[0][0].epool.size()-1-y];
		}
	}
	//e_3[0].self=cvl[0][0].epool;
	e_3[0].d=cvl[0][0].epool.size();
	int bps=ori.self.size()/vcore[0][0].self.size();
	e_4=convoluting(ori,e_3,bps);
	for(int x;x<vcore[0][0].self.size();x++)
	{
		for(int y;y<vcore[0][0].self.size();y++)
		{
			vcore[0][0].self[x][y]-=(e_4[0].self[x][y]);
		}
	}

	if(time<learn_time)
		goto head;

	//cout<<"训练已完成，请输入要验证的图片路径";
	//cin>>imagepath;
	imagepath="pycharm.png";
	ori.self=getimg_grayscale(imagepath.data());
	ori.ini();
	cvl[0]=convoluting(ori,vcore[0],3);
	cvl[0][0].weight=weight;
	cvl[0][0].relu();
	cvl[0][0].max_pooling(2,2);
	rslt=cvl[0][0].fulc();
	cout<<"该图片中含有 "<<name<<" 特征的概率是："<<rslt<<"%";
	return 0;
}