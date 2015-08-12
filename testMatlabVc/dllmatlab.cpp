#include <iostream>
#include "mclmcrrt.h"
#include "libmyadd2.h"

int main(int argc, char* argv[])
{
	std::cout << " function [y,z] = myadd2(a, b) " << std::endl;
	std::cout << " y = a+b; " << std::endl;
	std::cout << " z = a+2*b; " << '\n' << std::endl;

	// ��ʼ��MCR
	if (!mclInitializeApplication(NULL, 0))
	{
		std::cout << "Could not initialize the application!" << std::endl;
		return -1;
	}


	// ��ʼ������
	if (!libmyadd2Initialize())
	{
		std::cout << "Could not initialize libmyadd2!" << std::endl;
		return -1;
	}

	try
	{
		//��ʼ�� a
		mwArray a(2, 2, mxDOUBLE_CLASS);
		double *aData, *bData;
		aData = new double[4];
		bData = new double[4];

		for (int i = 0; i < 4; ++i)
		{
			aData[i] = 1.0*i;
		}

		std::cout << "a = " << std::endl;
		std::cout << aData[0] << "," << aData[1] << std::endl;
		std::cout << aData[2] << "," << aData[3] << '\n' << std::endl;

		a.SetData(aData, 4);

		//��ʼ�� b
		mwArray b(2, 2, mxDOUBLE_CLASS);
		b(1, 1) = 11.;
		b(1, 2) = 12.;
		b(2, 1) = 21.;
		b(2, 2) = 22.;

		b.GetData(bData, 4);
		std::cout << "b = " << std::endl;
		std::cout << bData[0] << "," << bData[1] << std::endl;
		std::cout << bData[2] << "," << bData[3] << '\n' << std::endl;

		//������� y z
		mwArray y(2, 2, mxDOUBLE_CLASS);
		mwArray z(2, 2, mxDOUBLE_CLASS);

		// ����dll
		myadd2(2, y, z, a, b);

		double *yData, *zData;
		yData = new double[4];
		zData = new double[4];

		// �������ݵ� C++
		y.GetData(yData, 4);
		z.GetData(zData, 4);

		// ������
		std::cout << "y = " << std::endl;
		std::cout << yData[0] << "," << yData[1] << std::endl;
		std::cout << yData[2] << "," << yData[3] << '\n' << std::endl;

		std::cout << "z = " << std::endl;
		std::cout << zData[0] << "," << zData[1] << std::endl;
		std::cout << zData[2] << "," << zData[3] << std::endl;

		// �ͷ��ڴ�
		delete[] aData;
		delete[] zData;
		delete[] yData;
	}
	catch (const mwException& e)
	{
		std::cerr << e.what() << std::endl;

	}

	// ���� lib
	libmyadd2Terminate();

	// terminate MCR
	mclTerminateApplication();


	return 0;
}