#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "markov.h"
#include <time.h>
#include <iostream>
#include "mclmcrrt.h"
#include "myget_discrimination.h"

using namespace std;
class TestCasesGenerater
{
public:
	static const int  SIZEBATH=50;
	 int ONEBATCHSIZE;
	Markov markov;
	vector<vector<int>> testPaths;
	vector<vector<string>> testCases;


	TestCasesGenerater();//��ʼ������ȡ��

	int generateTestCase();//����������������
	/*ʹ������ �����㷨������������·������*/
	void traverse();//����  �޷�����ѭ��
	void TestCasesGenerater::coutCaseAndPath(vector<string> onecase, vector<int> onepath);
	//������Ե�������·��

	bool isSufficient();//�Ƿ���


	double statistic();//�Բ����Ľ��ͳ��
	vector<double> cuculatePI();//����ƽ�ȷֲ�

	double TestCasesGenerater::caculateDiscrimination(
		double ** PP, int PProw, int PPlist,
		double ** SS, int SSrow, int SSlist,
		double * EEs, int  EEslen,
		double ** EEt, int EEtrow, int EEtlist);//����ģ�Ͳ�

	int process();//�Ǻ���

	~TestCasesGenerater();
};

