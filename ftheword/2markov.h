#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std; 

struct MarkovAdjacentTableNode//表节点：转移状态，概率，激励，次数（一阶特优）
{
	int indexOfStates;
	double probability;
	string stimulate;
	int times;
};

struct MarkovAdjacentTableHeadNode//邻接矩阵头
{
	int indexOfStates;
	vector< MarkovAdjacentTableNode> tableNode;
};

class Markov
{
public:
	int numberOfStates;//状态数
	vector<string> nodeName;//节点名
	int startIndex;
	int endIndex;

	vector <string > stimulates;//激励名
	double ** ptrPmatrix;

	double **ptrStatesToStimulates;
	
	vector<MarkovAdjacentTableHeadNode> adjacentTable;//邻接矩阵

	Markov ReaderMarkov();//从文件读



};