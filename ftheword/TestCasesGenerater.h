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

#include <atomic>
#include <mutex>
#include <thread>

#include <functional> 
#include "MyTime.h"
using namespace std;
class TestCasesGenerater
{
private:
	std::mutex casePushMutex;//用于同步case vector的操作
	static const int  SIZEBATH = 500;
	static const int  THREAD = 1;
	int ONEBATCHSIZE;
	Markov markov;
	vector<vector<int>> testPaths;
	vector<vector<string>> testCases;
public:
	TestCasesGenerater(string filename);//初始化，读取链
	TestCasesGenerater();//初始化，读取链
	int generateTestCase();//遍历，产生用例。
	/*使用链， 赌轮算法，产生用例和路径集合*/

	int parallelGenerateTestCase();//并行，产生用例。
	//void paralleProcess();
	//void paralleProcess(int threadnumber);
	void paralleProcess(int threadnumber, int startSize);

	void traverse();//遍历  无法处理循环
	void TestCasesGenerater::coutCaseAndPath(vector<string> onecase, vector<int> onepath);
	//输出测试的用例和路径

	bool isSufficient();//是否充分

	double statistic();//对产生的结果统计
	vector<double> cuculatePI();//计算平稳分布

	double TestCasesGenerater::caculateDiscrimination(
		double ** PP, int PProw, int PPlist,
		double ** SS, int SSrow, int SSlist,
		double * EEs, int  EEslen,
		double ** EEt, int EEtrow, int EEtlist);//计算模型差

	int process();//是核心

	~TestCasesGenerater();

private:
	//工具函数
	void initfun();
};

