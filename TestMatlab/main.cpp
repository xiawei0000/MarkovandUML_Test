#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "engine.h"
#include "matrix.h"


int main()
{
	Engine *ep;//��������
	int i, j;

	//show how to open MATLAB engine
	//for remote ones:
	//engOpen( ADDRESS OF REMOTE SYSTEM ) ;

	if (!(ep = engOpen("\0"))){//������ û�����ú�matlab ��ʧ�ܣ�cmd����ָ�� matlab / regserver,

		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	//show how to create matrix
	//��������
	mxArray *Y = mxCreateDoubleMatrix(1, 3, mxREAL);

	//show how to put data in matrix
	//������tmp���Ƶ��ṹ��
	double tmp[3] = { 1.0, 2.0, 3.0 };
	memcpy(mxGetPr(Y), tmp, sizeof(tmp));

	//show how to put variables in the Engine
	engPutVariable(ep, "Y", Y);

	//show how to execute commands in MATLAB
	engEvalString(ep, "X = ones(5,1) * Y");

	 
	int dims[10];
	int ndims;
	ndims = mxGetNumberOfDimensions(Y);
	printf("total number of dimensions is %d\n", ndims);
	memcpy(dims, mxGetDimensions(Y), ndims * sizeof(int));
	for (i = 0; i < ndims; i++){
		printf("dimension %d : %d\n", i, dims[i]);
	}
	printf("\n");

	//show how to get variables from the Engine
	mxArray *X = engGetVariable(ep, "X");

	//show how to manipulate dimensions
	
	ndims = mxGetNumberOfDimensions(X);
	printf("total number of dimensions is %d\n", ndims);
	memcpy(dims, mxGetDimensions(X), ndims * sizeof(int));
	for (i = 0; i < ndims; i++){
		printf("dimension %d : %d\n", i, dims[i]);
	}
	printf("\n");

	//�������ά�Ȼ�ȡ���ǲ��Ե�,ֻ�����ά�����ǶԵģ�
	//show how the data is stored in the memory
	double *p = (double*)mxGetData(X);
	for (i = 0; i < dims[0]; i++){
		for (j = 0; j < 3; j++){//dims[1]//�е�ά��=0��ʵ����3
			printf("%8.2f", p[j * dims[0] + i]);
		}
		printf("\n");
	}

	//---important, to release resources
	mxDestroyArray(X);//�ͷ�
	mxDestroyArray(Y);

	//show how to hide and unhide MATLAB command window
	printf("type RETURN to hide the MATLAB command window...\n");
	getchar();
	engSetVisible(ep, false);//����matlab�Դ��Ĵ��ڵķ���
	printf("type RETURN to unhide the MATLAB command window...\n");
	getchar();
	engSetVisible(ep, true);

	printf("type RETURN to END this program...\n");
	getchar();
	//remembering to close it is important .
	//but if you are debugging your programs ,
	//annotate the following line will save you a lot of time ,
	//for you needn't to restart the Engine .
	engClose(ep);//�ر�matlab

	//when your work is accomplished , type "exit" in MATLAB command window

	return EXIT_SUCCESS;
}