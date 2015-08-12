#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std; 

struct MarkovAdjacentTableNode//��ڵ㣺ת��״̬�����ʣ�������������һ�����ţ�
{
	int indexOfStates;
	double probability;
	string stimulate;
	int times;
};

struct MarkovAdjacentTableHeadNode//�ڽӾ���ͷ
{
	int indexOfStates;
	vector< MarkovAdjacentTableNode> tableNode;
};

class Markov
{
public:
	int numberOfStates;//״̬��
	vector<string> nodeName;//�ڵ���
	int startIndex;
	int endIndex;

	vector <string > stimulates;//������
	double ** ptrPmatrix;

	double **ptrStatesToStimulates;
	
	vector<MarkovAdjacentTableHeadNode> adjacentTable;//�ڽӾ���

	Markov ReaderMarkov();//���ļ���



};