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


struct MarkovAdjacentTableNode//��ڵ㣺ת��״̬�����ʣ�������������һ�����ţ�
{
	string nodeName;//����ڵ�
	int indexOfStates;
	double probability;
	string stimulate;
	int stimulateIndex;

	//8 -5 ԭ�Ӳ���
	int times;
	//std::atomic<int> times;

public:
	MarkovAdjacentTableNode():times(0)
	{	}
};

struct MarkovAdjacentTableHeadNode//�ڽӾ���ͷ
{
	//8 -5 ԭ�Ӳ���
	int times;//�ڵ�ķ��ʴ���
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
	int numberOfStates;//״̬��
	vector<string> nodeNames;//�ڵ���
	//set<string> nodeNames;//�ڵ��� set������ģ�������
	int startIndex;
	int endIndex;

	vector <string > stimulates;//������
	int numberOfStimulates;
	double ** ptrPmatrix;

	double **ptrStatesToStimulates;

	vector<MarkovAdjacentTableHeadNode> adjacentTable;//�ڽӾ���


public:
	void test();//test
	Markov();
	~Markov();
	void ReaderMarkov(string filename);//���ļ���
	void getnodes(ifstream &file);//���ڵ����
	void buildMem();//�������

	void fromTableToMatrix();//��tableתmatrix
	
	void showMarkov();

};