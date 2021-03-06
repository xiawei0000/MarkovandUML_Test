#pragma once
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>
#include <windows.h>

#include <atomic>
#include <mutex>
#include <thread>


using namespace std;


struct MarkovAdjacentTableNode//表节点：转移状态，概率，激励，次数（一阶特优）
{
	string nodeName;//到达节点
	int indexOfStates;
	double probability;
	string stimulate;
	int stimulateIndex;

	//8 -5 原子操作
	int times;
	//std::atomic<int> times;

public:
	MarkovAdjacentTableNode():times(0)
	{	}
};

struct MarkovAdjacentTableHeadNode//邻接矩阵头
{
	//8 -5 原子操作
	int times;//节点的访问次数
	//std::atomic<int> times;

	int indexOfStates;
	string nodeName;
	vector< MarkovAdjacentTableNode> tableNode;
	MarkovAdjacentTableHeadNode() :times(0)
	{}
};

class Markov
{
public:
	int numberOfStates;//状态数
	vector<string> nodeNames;//节点名
	//set<string> nodeNames;//节点名 set是排序的，不能用
	int startIndex;
	int endIndex;

	vector <string > stimulates;//激励名
	int numberOfStimulates;
	double ** ptrPmatrix;

	double **ptrStatesToStimulates;

	vector<MarkovAdjacentTableHeadNode> adjacentTable;//邻接矩阵


public:
	void test();//test
	Markov();
	~Markov();
	void ReaderMarkov(string filename);//从文件读
	void getnodes(ifstream &file);//读节点个数
	void buildMem();//构造矩阵

	void fromTableToMatrix();//将table转matrix
	
	void showMarkov();

};