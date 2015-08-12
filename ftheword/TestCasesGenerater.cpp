#include "TestCasesGenerater.h"

 
 

vector<double> cuculatePI();//计算平稳分布

void   TestCasesGenerater::traverse() //遍历
{
	testPaths.clear();
	testCases.clear();

	vector<int > pathone;
	vector<string> caseone;

	pathone.push_back(0);
	caseone.push_back(markov.adjacentTable[0].nodeName);
 //循环的话 深度广度都无效了
 
}


//赌轮
MarkovAdjacentTableNode& RouletteWheels(vector< MarkovAdjacentTableNode> &tableNode)
{//对后续的节点，直接赌轮选一个，返回这个节点：包含激励和和序号，
	vector<double> probvec;
	for (MarkovAdjacentTableNode &node:tableNode)
	{
		//double tempd = node.probability;
		probvec.push_back(node.probability);
	}
	double sum = 0.0;
	for (double &temp : probvec)
	{
		sum += temp;
		temp = sum;
	}
	for (double &temp : probvec)
	{//防止和不是1
		temp = temp/sum;
	}

	
	//double randvalue2 = rand();
	//double randvalue= rand() /(double)RAND_MAX*sum;
	//double randvalue = rand() %1000 /1000.0*sum;//buxing 

	double randvalue = rand() % 97 / 97.0*sum;
	int indexOfChoice = 0;
	for (int i = 0; i < probvec.size(); i++)
	{

		if (randvalue <= probvec[i])
		{
			indexOfChoice = i; break;
		}
	}
	MarkovAdjacentTableNode &node = tableNode[indexOfChoice];
	return node;

}



void TestCasesGenerater::paralleProcess(int threadnumber, int startSize)
{
	//std::unique_lock<std::mutex> lck(this->casePushMutex);

	//int startSize = testCases.size();//两个线程进来， 第二个来的时候，就产生新的了，此时 startsize=1了。
	//lck.unlock();

	//testCases.size()
	std::unique_lock<std::mutex> lck(this->casePushMutex, std::defer_lock);
	while (testCases.size() - startSize < ONEBATCHSIZE)
	{
		vector<int > pathone;
		vector<string> caseone;
		pathone.push_back(markov.startIndex);//第一个节点，入口点 都要处理：节点序号
		caseone.push_back(markov.adjacentTable[0].nodeName);//激励的路径，第一个 是用节点当做激励的

		int currentIndex = markov.startIndex;
		
		lck.lock();
		markov.adjacentTable[currentIndex].times++;//统计次数
		lck.unlock();


		while (currentIndex != markov.endIndex)
		{
			MarkovAdjacentTableNode &nextnode = RouletteWheels(markov.adjacentTable[currentIndex].tableNode);
			//不只 index 还有激励

			lck.lock();
			nextnode.times++;//统计转移 的次数
			lck.unlock();

			pathone.push_back(nextnode.indexOfStates);
			caseone.push_back(nextnode.stimulate);
			currentIndex = nextnode.indexOfStates;//继续下一个

			lck.lock();
			markov.adjacentTable[currentIndex].times++;//统计节点次数
			lck.unlock();
		}

		//std::lock_guard<std::mutex> lck(this->casePushMutex );这个lock guard 是锁定后整个区域都有效。

		lck.lock();
		//再次判断一下，是否 size满了

		 if (testCases.size()- startSize < ONEBATCHSIZE)
		 {
			//对testcase的操作要同步化： mutex
			//将完整的一条测试保存
			testCases.push_back(caseone);
			testPaths.push_back(pathone);
			lck.unlock();
		 }
		 else{
		
			 lck.unlock();
			 std::cout << "@@多余";
			 break;
		 }
		//lck.unlock();
		//test

		 //lck.lock();
		//std::cout << "线程 threadnumber：" << threadnumber<<endl;
		//coutCaseAndPath(caseone, pathone);
		//lck.unlock();
	}
}


int TestCasesGenerater::parallelGenerateTestCase()//并行，产生用例。
{
	MyTime ti;
	ti.Start();
	std::vector<std::thread> threads;
	int startSize = testCases.size();
	for (int i = 0; i <this->THREAD; i++)
	{
		//std::function<void(int)> fpi; bind无法绑定重载函数
		//fpi = std::bind(&(TestCasesGenerater::paralleProcess), this, i);

		std::function< void(int,int)> lamedafun = [this](int i,int startSize){
			this->paralleProcess(i, startSize);
		};
		threads.push_back(
			std::thread(lamedafun, i, startSize)
			);

	}

	for (auto & th:threads)
	{
		th.join();
	}
	ti.End();

	cout << "总共耗时："<<ti.costTime << endl;

	/*int startSize = testCases.size();
	while (testPaths.size() - startSize < ONEBATCHSIZE)
	{
		vector<int > pathone;
		vector<string> caseone;
		pathone.push_back(markov.startIndex);//第一个节点，入口点 都要处理：节点序号
		caseone.push_back(markov.adjacentTable[0].nodeName);//激励的路径，第一个 是用节点当做激励的

		int currentIndex = markov.startIndex;
		markov.adjacentTable[currentIndex].times++;//统计次数

		while (currentIndex != markov.endIndex)
		{
			MarkovAdjacentTableNode &nextnode = RouletteWheels(markov.adjacentTable[currentIndex].tableNode);
			//不只 index 还有激励
			nextnode.times++;//统计转移 的次数

			pathone.push_back(nextnode.indexOfStates);
			caseone.push_back(nextnode.stimulate);
			currentIndex = nextnode.indexOfStates;//继续下一个
			markov.adjacentTable[currentIndex].times++;//统计节点次数
		}

		//将完整的一条测试保存
		testCases.push_back(caseone);
		testPaths.push_back(pathone);

		//test
		coutCaseAndPath(caseone, pathone);
	}	*/
	return testPaths.size();
}


int TestCasesGenerater::generateTestCase()//遍历，产生用例。
{
	//	testPaths.clear();
	//	testCases.clear();

	int startSize = testCases.size();
	while (testPaths.size() - startSize < ONEBATCHSIZE)
	{
		vector<int > pathone;
		vector<string> caseone;
		pathone.push_back(markov.startIndex);//第一个节点，入口点 都要处理：节点序号
		caseone.push_back(markov.adjacentTable[0].nodeName);//激励的路径，第一个 是用节点当做激励的

		int currentIndex = markov.startIndex;
		markov.adjacentTable[currentIndex].times++;//统计次数

		while (currentIndex != markov.endIndex)
		{
			MarkovAdjacentTableNode &nextnode = RouletteWheels(markov.adjacentTable[currentIndex].tableNode);
			//不只 index 还有激励
			nextnode.times++;//统计转移 的次数

			pathone.push_back(nextnode.indexOfStates);
			caseone.push_back(nextnode.stimulate);
			currentIndex = nextnode.indexOfStates;//继续下一个
			markov.adjacentTable[currentIndex].times++;//统计节点次数
		}

		//将完整的一条测试保存
		testCases.push_back(caseone);
		testPaths.push_back(pathone);

		//test
		coutCaseAndPath(caseone, pathone);
	}


	return testPaths.size();

}

bool   TestCasesGenerater:: isSufficient()//对产生的结果统计
{
	//bool issuff = false;
	for (MarkovAdjacentTableHeadNode headnode: this->markov.adjacentTable)
	{
		for (MarkovAdjacentTableNode tablenode:headnode.tableNode)
		{
			int ti = static_cast<int>( tablenode.times );
			if (ti <=0 )
			{
				return false;
			}			 
		}
	}
	return true;

}



double  TestCasesGenerater::statistic()//对产生的结果统计
{
	//要传入 P S 矩阵 ，ES ，Et
	double * Es = new double[this->markov.numberOfStates];
	int i = 0;
	for (MarkovAdjacentTableHeadNode headnode : this->markov.adjacentTable)
	{
		 
		Es[i] = static_cast<int>(headnode.times);
		i++;
	}

	cout << " Es@@@@@@@@@@@@@" << endl;
	for (int i = 0; i < this->markov.numberOfStates;i++)
	{
		cout << Es[i]<<"  ";
	}
	cout << endl;

	double **Et = new double*[this->markov.numberOfStates];
	for (int i = 0; i < this->markov.numberOfStates;i++)
	{
		Et[i] = new double[this->markov.numberOfStimulates];
		for (int j = 0; j < this->markov.numberOfStimulates;j++)
		{
			Et[i][j] = 0;
		}
	}

	i = 0;
	for (MarkovAdjacentTableHeadNode headnode : this->markov.adjacentTable)
	{
		
		for (MarkovAdjacentTableNode tablenode : headnode.tableNode)
		{
			Et[i][tablenode.stimulateIndex] = static_cast<int>(tablenode.times);
		}
		i++;
	}
	cout << " Et@@@@@@@@@@@@@"<<endl;
	//注意 这里 Et矩阵中，状态个数应该去掉最后的一个结束节点。
	for (int i = 0; i < this->markov.numberOfStates; i++)
	{
	
		for (int j = 0; j < this->markov.numberOfStimulates; j++)
		{
			cout<< Et[i][j] <<"   " ;
		}
		cout << endl;
	}
	cout << endl;

	//准备空间
	 
	double  resultdiscri = caculateDiscrimination(
		this->markov.ptrPmatrix, this->markov.numberOfStates, this->markov.numberOfStates,
		this->markov.ptrStatesToStimulates,this->markov.numberOfStates-1,this->markov.numberOfStimulates,
		Es, this->markov.numberOfStates,
		Et, this->markov.numberOfStates-1, this->markov.numberOfStimulates
		);
	//开始调用

	return resultdiscri;
}


void copyvectorTomwArray(mwArray * arra,double ** p,int row,int list){
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < list; j++)
		{
			(*arra)(i+1, j+1) = p[i][j];
		}
	}
}
double TestCasesGenerater::caculateDiscrimination(
	double ** PP, int PProw, int PPlist,
	double ** SS, int SSrow, int SSlist,
	double * EEs, int  EEslen,
	double ** EEt, int EEtrow, int EEtlist)//计算模型差
{
	double resutlk = 999999.9;
	// 初始化MCR
	/*if (!mclInitializeApplication(NULL, 0))
	{
		std::cout << "Could not initialize the application!" << std::endl;
		return 99999.0;
	}


	// 初始化引用
	if (!myget_discriminationInitialize())
	{
		std::cout << "Could not initialize libmyadd2!" << std::endl;
		return  99999.0;
	}
	*/

	try
	{
		mwArray P(PProw, PPlist, mxDOUBLE_CLASS);
		mwArray S(SSrow, SSlist, mxDOUBLE_CLASS);
		mwArray Es(EEslen, 1, mxDOUBLE_CLASS);
		mwArray Et(EEtrow, EEtlist, mxDOUBLE_CLASS);

		mwArray K(1, 1, mxDOUBLE_CLASS);		//定义输出  k
		mwArray pi(1, EEslen, mxDOUBLE_CLASS);
		mwArray N(SSrow, SSrow, mxDOUBLE_CLASS);

		for (int i = 0; i < SSrow;i++)
		{
			Es(i+1, 1) = EEs[i];
		}
		copyvectorTomwArray(&P, PP, PProw, PPlist);
		copyvectorTomwArray(&S, SS, SSrow, SSlist);
		copyvectorTomwArray(&Et, EEt, EEtrow, EEtlist);

		int nargout = 3;

		/* 
		double EsData[] = { 4, 5, 7, 3, 4 };
		Es.SetData(EsData, 5);

		Et(1, 1) = 4; Et(1, 2) = 0; Et(1, 3) = 0; Et(1, 4) = 0; Et(1, 5) = 0;
		Et(2, 1) = 0; Et(2, 2) = 3; Et(2, 3) = 2; Et(2, 4) = 0; Et(2, 5) = 0;
		Et(3, 1) = 0; Et(3, 2) = 4; Et(3, 3) = 1; Et(3, 4) = 2; Et(4, 5) = 0;
		Et(4, 1) = 1; Et(4, 2) = 0; Et(4, 3) = 0; Et(4, 4) = 1; Et(4, 5) = 1;
		*/
		//	mwArray *restultProcess;
		// 调用dll
		myget_discrimination(nargout, K, pi, N, P, S, Es, Et);
		 resutlk = K.Get(1, 1);

		cout << "结果:::" << resutlk<<endl;// [0];

		double * piData;
		piData = new double[5];
		pi.GetData(piData, 5);
		for (int i = 0; i < 5; i++)
		{
			cout << "\t" << piData[i];
		}
		cout << endl;

		double * Ndata;
		Ndata = new double[16];
		N.GetData(Ndata, 16);
		for (int i = 0; i < 16; i++)
		{
			if (i % 4 == 0)
			{
				cout << endl;
			}
			cout << "\t" << Ndata[i];
		}

	}
	catch (const mwException& e)
	{
		std::cerr << e.what() << std::endl;

	}

	/* 
	// 结束 lib
	myget_discriminationTerminate();

	// terminate MCR
	mclTerminateApplication();
*/
	return  resutlk;

}



int   TestCasesGenerater::process() //遍历，产生用例。
{/*
 1 产生测试用例，
 2判断是否都有一个了，
 3统计出ES，ET
 4求相识度，
 5判断相识度《？ 循环第一步
 6 退出
 */

	double scriminate = 999991;
	do 
	{
		//int numberoftestcase = generateTestCase();
		//8-5修改为并行
		int numberoftestcase= parallelGenerateTestCase();

		//判断 每一段都有了
		bool isSuffi = isSufficient();
		if (!isSuffi)
		{
			continue;
		}

		scriminate = statistic();

 
	} while (scriminate > 0.001);// do while 的continue之后会执行while中的条件
	return 1;
}

void TestCasesGenerater::coutCaseAndPath(vector<string> onecase,vector<int> onepath) //输出测试的用例和路径
{
	cout << "测试路径 :";
	for (int i = 0; i < onecase.size();i++)
	{
		if (i != onecase.size()-1)
		{	
			cout << onecase[i] << "-->";
		}
		else
		{
			cout << onecase[i] << endl;
		}
	
	}

	cout << "测试用例 :";
	for (int i = 0; i < onepath.size();i++)
	{
		if (i!= onepath.size()-1)
		{
			cout << onepath[i] << "-->";
		}
		else{
			cout << onepath[i] << endl;
		}
	}
	/*for (string &one :onecase)
	{
		cout << one << "-->";
	}
	cout << "结束"<<endl;

	cout << "测试用例 :";
	for (int &path: onepath)
	{
		cout << path << "-->";
	}
	cout << "结束" << endl << endl;
	*/
}
void TestCasesGenerater::initfun()
{
	//初始化matlab
	if (!mclInitializeApplication(NULL, 0))
	{
		std::cout << "Could not initialize the application!" << std::endl;
		throw  "mclInitializeApplication failed";
		return;
	}
	// 初始化引用
	if (!myget_discriminationInitialize())
	{
		std::cout << "Could not initialize libmyadd2!" << std::endl;
		throw "myget_discriminationInitialize failed";
		return;
	}
}

TestCasesGenerater::TestCasesGenerater(string name) :markov()
{
	srand((unsigned)time(NULL));//初始一次
	//markov = new Markov();指针
	this->markov.ReaderMarkov(name);

	ONEBATCHSIZE = this->markov.numberOfStates*SIZEBATH;

	initfun();
}
TestCasesGenerater::TestCasesGenerater() :markov()
{
	srand((unsigned)time(NULL));//初始一次
	//markov = new Markov();指针
	this->markov.ReaderMarkov("test.txt");

	ONEBATCHSIZE = this->markov.numberOfStates*SIZEBATH;

	initfun();

}


TestCasesGenerater::~TestCasesGenerater()
{

	// 结束 lib
	myget_discriminationTerminate();

	// terminate MCR
	mclTerminateApplication();
}
