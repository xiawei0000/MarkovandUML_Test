#include "Markov.h"
void Markov::test()//test
{
	Markov m;
	m.ReaderMarkov("test.txt");
	m.showMarkov();
	int a; cin >> a;
	return;
}

Markov::Markov()
{
}


Markov::~Markov()
{
}
void Markov::showMarkov(){
	//遍历邻接表，写成dot格式文件

	ofstream out("graph.txt");
	out << "digraph markow{"<<endl;

//	out << "rankdir=LR;" << endl;
	out << "size=\"300,300\"; " << endl;//bgcolor=\"#C6CFD532\";

	out << "node [style=\"filled\", color=\"black\", fillcolor=\"chartreuse\"];" << endl;
	out << nodeNames[this->startIndex] << ";" << endl;
	//设置开始点的属性
	out << "node [shape=doublecircle];" << endl;
	out << nodeNames[this->endIndex] << ";" << endl;
	//设置结束点的属性

	out << "node [shape=circle];" << endl;
	for (int i = 0; i < nodeNames.size();i++)
	{
		if (i!= endIndex && i!=startIndex)
		{
			string nodename = nodeNames[i];
			out << nodename << ";" << endl;
		}

	}
	
	

	try
	{
		for (MarkovAdjacentTableHeadNode head:adjacentTable)
		{
			string start = head.nodeName;
			for (MarkovAdjacentTableNode node:head.tableNode)
			{
				string end = node.nodeName;
				char temp[100];//转字符
				sprintf(temp, "%f", node.probability);
				string  prob =  temp;

				string  stilmulate = node.stimulate;
				out << start << "->"<<end<<"[label=\""<<stilmulate <<"  :  "<<prob<<"\"]"<<";" << endl;
			}
		}
	}	
	catch (exception* e)
	{
	}
	out << "}";
	out.close();
	WinExec("C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe   -Tpng -o MMMarkovgraph.png  graph.txt ", SW_SHOW);

	system(".\\MMMarkovgraph.png");
	//system("D:\\360\\项目\\UML\\ftheword\\Debug\\MMMarkovgraph.png");//这个可用,要用完整路径 
	//WinExec("dllhost.exe  MMMarkovgraph.png ", SW_SHOW);
	//ShellExecute(NULL, (LPWSTR)"open", (LPWSTR)".\\MMMarkovgraph.png", NULL, NULL, SW_SHOW);
	//if (WinExec("C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe   -Tpng -o MMMarkovgraph.png  graph.txt ", SW_SHOW) < 32);
	//cout << "dot error \n";

	return;
}


bool isSpicial(string input,vector<string> &nodeNames)
{//判断节点名字的唯一性
	for (string &node : nodeNames)
	{
		if (input == node )
		{
			return false;
		}
	}
	return true;
}

void Markov::getnodes(ifstream &file)
{
	const int MAXINLINE = 100;
	char line[MAXINLINE];
	int lines = 0;
	string endStates;
	string statesnameEnter;
	string statesnameEnd;
	string stimulate;
	double probility;
	try
	{
		while (!file.eof())
		{
			lines++;
			if (lines == 1)
			{

				file.getline(line, MAXINLINE);
				this->nodeNames.push_back(line);
			}
			else if (lines == 2)
			{
				file.getline(line, MAXINLINE);
				endStates = line;
			}
			else{
				file >> statesnameEnter;
				file >> statesnameEnd;
				file >> stimulate;
				file >> probility;

				bool isnew = isSpicial(statesnameEnter, this->nodeNames);
				if (isnew)
				{
					this->nodeNames.push_back(statesnameEnter);
				}
				isnew = isSpicial(statesnameEnd, this->nodeNames);
				if (isnew)
				{
					this->nodeNames.push_back(statesnameEnd);
				}
				isnew = isSpicial(stimulate, this->stimulates);
				if (isnew)
				{
					this->stimulates.push_back(stimulate);
				}
			}
		}//读取节点完毕
		this->startIndex = 0;
	//	nodeNames.push_back(endStates);

		//结束点不一定最后出现
		vector<string >::iterator result = find(nodeNames.begin(), nodeNames.end(), endStates);
		if (result == nodeNames.end())
		{
			std::cerr << "error \n";
			return;
		}
		else
		{
			this->endIndex = result - nodeNames.begin();
		}
		//this->endIndex = nodeNames.size() - 1;
		this->numberOfStates = nodeNames.size();
		this->numberOfStimulates = stimulates.size();
	}
	catch (exception* e)
	{
		cout << e;
	}

	file.clear();
	file.seekg(ios::beg);//到首
	
}


void Markov::fromTableToMatrix()//将table转matrix
{
	for (MarkovAdjacentTableHeadNode &head:this->adjacentTable)
	{
		for (MarkovAdjacentTableNode &node: head.tableNode)
		{
			ptrPmatrix[head.indexOfStates][node.indexOfStates] += node.probability;
			//+= 防止有a到b 多条弧的。
			//ptrStatesToStimulates[head.indexOfStates][node.stimulate]
		}
	}
}


void Markov::buildMem()
{
	//构造矩阵
	ptrPmatrix = new double*[numberOfStates];
	for (int i = 0; i < numberOfStates; i++)
	{
		ptrPmatrix[i] = new double[numberOfStates];
		for (int j = 0; j < numberOfStates;j++)
		{
			ptrPmatrix[i][j] = 0.0;
		}
		
	}

	ptrStatesToStimulates = new double*[numberOfStates];
	for (int i = 0; i < numberOfStates; i++)
	{
		ptrStatesToStimulates[i] = new double[numberOfStimulates];
		for (int j = 0; j < numberOfStimulates;j++)
		{
			ptrStatesToStimulates[i][j] = 0.0;
		}

	}

	//构造表
	int i = 0;
	for (string nodeName:nodeNames)
	{
		MarkovAdjacentTableHeadNode headnode;
		headnode.indexOfStates = i;
		i++;
		headnode.nodeName = nodeName;
		//headnode.times.store(0);
		headnode.times = 0;

		adjacentTable.push_back(headnode);
	}
}
void  Markov::ReaderMarkov(string filename)//从文件读
{
	ifstream file(filename);
	try
	{
		
		if (!file)
		{
			cout << "get file error!" << endl;
			throw "get file error!";
		}
		int lines = 0;
		string endStates;
		string statesnameEnter;
		string statesnameEnd;
		string stimulate;
		double probility;

		getnodes(file);
		buildMem();
		const int MAXINLINE = 100;
		char line[MAXINLINE];

		while (!file.eof())
		{
			lines++;
			if (lines == 1)
			{
		
				file.getline(line, MAXINLINE);

			}
			else if (lines == 2)
			{
				file.getline(line, MAXINLINE);
			}
			else{
				file >> statesnameEnter;
				file >> statesnameEnd;
				file >> stimulate;
				file >> probility;

				if (file.bad() ||file.fail())//只判断eof不行，还要判断《《是否读成功了
				{
					break;
				}
				int enterIndex;
				int endIndex;
				int stimulateIndex;
				vector<string >::iterator result=find(nodeNames.begin(), nodeNames.end(), statesnameEnter);
				if (result == nodeNames.end())
				{
					std::cerr << "error \n";
					return ;
				}
				else
				{
					enterIndex = result - nodeNames.begin();
				}
				result = find(nodeNames.begin(), nodeNames.end(), statesnameEnd);
				if (result == nodeNames.end())
				{
					std::cerr << "error \n";
					return;
				}
				else
				{
					endIndex = result - nodeNames.begin();
				}
				result = find(stimulates.begin(), stimulates.end(), stimulate);
				if (result == stimulates.end())
				{
					std::cerr << "error \n";
					return;
				}
				else
				{
					stimulateIndex = result - stimulates.begin();
				}

				ptrPmatrix[enterIndex][endIndex] += probility;//可能有多个弧

				ptrStatesToStimulates[enterIndex][stimulateIndex] = probility;

				MarkovAdjacentTableNode tablenode;
				tablenode.nodeName = statesnameEnd;
				tablenode.indexOfStates = endIndex;
				tablenode.probability = probility;
				tablenode.stimulate = stimulate;
				tablenode.stimulateIndex = stimulateIndex;
				//tablenode.times.store(0);
				tablenode.times = 0;//次数初始化
				adjacentTable[enterIndex].tableNode.push_back(tablenode);
				
			}

		}//构建



	}
	catch (const char message[])
	{
		cout << message << endl;
	}
	catch (exception * e)
	{
		cout << e;
	}
	file.close();

	showMarkov();
}

 