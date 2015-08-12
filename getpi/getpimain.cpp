#include <iostream>
#include "mclmcrrt.h"
#include "myget_discrimination.h"
using namespace std;
int test();
static int a=0;
int main(int argc, char* argv[])
{
	if (  !mclInitializeApplication(NULL, 0))
	{
		std::cout << "Could not initialize the application!" << std::endl;
		return -1;

	}
	// 初始化引用
	if (!myget_discriminationInitialize())
	{
		std::cout << "Could not initialize libmyadd2!" << std::endl;
		return -1;
	}
	test();
	//test();

	mclTerminateApplication();
	 myget_discriminationTerminate();
	a++;
}
int test()
{

	a++;
	// 初始化MCR

	try
	{

		//1数据类型，2 行列不对，3输出问题
		//初始化 转移矩阵
		mwArray P(5, 5, mxDOUBLE_CLASS);		
		mwArray S(4, 5, mxDOUBLE_CLASS);
		mwArray Es(5, 1, mxDOUBLE_CLASS);
		mwArray Et(4, 5, mxDOUBLE_CLASS);

		mwArray K(1, 1, mxDOUBLE_CLASS);		//定义输出  k
		K(1, 1) = 1.0;
		mwArray pi(1,5, mxDOUBLE_CLASS);
		
		/*mwArray pi2(1, 5, mxDOUBLE_CLASS);
		double piData2[] = { 0.1857, 0.2286, 0.2286, 0.1714, 0.1857};
		pi2.SetData(piData2, 5);
		*/

		mwArray N(4,4,mxDOUBLE_CLASS);
		//double *pData;
		//pData = new double[25];	
		/*double pData[] = {
		0, 1, 0, 0, 0,
		0, 0, 0.5, 0.5, 0,
		0 ,0 ,0.5 ,0.25, 0.25,
		0 ,0.25, 0 ,0 ,0.75,
		1 ,0 ,0 ,0 , 0 };*/

		double pData[] = {
			0, 0, 0, 0, 1,
			1, 0, 0, 0.25, 0,
			0, 0.5, 0.5, 0, 0,
			0, 0.5, 0.25, 0, 0,
			0, 0, 0.25, 0.75, 0 };

		P.SetData(pData, 25);

		double  sData[] = { 
		1,  0,  0 , 0.25 ,
		0,0.5,  0.5 , 0 , 
		0 , 0.5 ,0.25 ,0,
		0 ,0, 0.25 , 0.5,
		0, 0, 0,  0.25 };
		S.SetData(sData,20);/**/
		


		cout << "     testset "  << endl;
		for (int i = 1; i <= 4;i++)
		{
			for (int j = 1; j <= 5;j++)
			{
				cout << "    " << S(i, j);
			}
			cout <<   endl;
		}
	
	
		double EsData[] = { 4, 5, 7, 3, 4 };
		Es.SetData(EsData, 5);

		/* 
		double EtData[] = { 
		4 ,0 ,0 ,1 ,
		0 ,3, 4, 0 ,
		0 ,2 ,1,  0,
		0,0, 2,  1 ,
		0 ,0, 0,1 };
		Et.SetData(EtData, 20);*/
	//采用设置卡看
		Et(1, 1) = 4; Et(1, 2) = 0; Et(1, 3) = 0; Et(1, 4) = 0; Et(1, 5) = 0;
		Et(2, 1) = 0; Et(2, 2) = 3; Et(2, 3) = 2; Et(2, 4) = 0; Et(2, 5) = 0;
		Et(3, 1) = 0; Et(3, 2) = 4; Et(3, 3) = 1; Et(3, 4) = 2; Et(4, 5) = 0;
		Et(4, 1) = 1; Et(4, 2) = 0; Et(4, 3) = 0; Et(4, 4) = 1; Et(4, 5) = 1;
		/*  
		//初始化 b
		mwArray b(2, 2, mxDOUBLE_CLASS);
		b(1, 1) = 11.;
		b(1, 2) = 12.;
		b(2, 1) = 21.;
		b(2, 2) = 22.;
		double *aData, *bData;
		bData = new double[4];
		b.GetData(bData, 4);
		*/
 
		int nargout=3;

	//	mwArray *restultProcess;
		// 调用dll
		//myget_discrimination(nargout, K,pi,N, P, S, Es, Et);
		myget_discrimination(nargout, K,pi,  N, P,S,  Es, Et);
		
	//	double kData[1] = { 0.1 };
		// 拷贝数据到 C++
		//K.GetData(kData, 1);
		

		//cout << mxIsDouble(&K);
		double resutlk = K.Get(1, 1);
		cout << K;
		double *kda  = new double[1];
		K.GetData(kda, 1);
		cout << kda[0];
	//	K.
	 
		
		cout << "结果:::" << resutlk;// [0];

		cout << "  "<<pi.Get(1, 1) <<"   "<< pi.Get(1, 2) <<"  "<< pi.Get(1, 3)
			<< "   " << pi.Get(1, 4) << "   " << pi.Get(1, 5);
		cout << endl;

		double * piData;
		piData = new double[5];
		pi.GetData(piData, 5);
		for (int i = 0; i < 5; i++)
		{			
			cout << "__" << piData[i];
		}
		cout << endl;
		

		cout << "  " << N.Get(1, 1) << "   " << N.Get(1, 2) << "  " << N.Get(1, 3)<< "   " << N.Get(1, 4) << "   " << endl;
		cout << "  " << N.Get(2, 1) << "   " << N.Get(2, 2) << "  " << N.Get(2, 3) << "   " << N.Get(2, 4) << "   " << endl;
		cout << "  " << N.Get(3, 1) << "   " << N.Get(3, 2) << "  " << N.Get(3, 3) << "   " << N.Get(3, 4) << "   " << endl;
	/* 	*/// 输出结果

		double * Ndata;
		Ndata = new double[16];
		N.GetData(Ndata, 16);
		for (int i = 0; i < 16;i++)
		{
			if (i%4 ==0)
			{
				cout << endl;
			}
			cout << "__" << Ndata[i];
		}
		// 释放内存
		/* 
		delete[] pData;
		delete[] sData;
		delete[] EtData;
		delete[] EsData;*/
	}
	catch (const mwException& e)
	{
		std::cerr << e.what() << std::endl;

	}

	// 结束 lib
	//myget_discriminationTerminate();

	// terminate MCR
	if (a <= 1 )
	{	
	//	mclTerminateApplication();
	}



	return 0;
}