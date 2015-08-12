#include   <windows.h> 
#include <gvc.h>
#include <stdlib.h>
#include <iostream>


using namespace  std;

 
int main(int argc, char **argv)
{

	WinExec("C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe   -Tpng -o MMMarkovgraph.png  graph.txt ", SW_SHOW);

	system(".\\MMMarkovgraph.png");

	system("D:\\360\\项目\\UML\\ftheword\\Debug\\MMMarkovgraph.png");//这个可用
	ShellExecute(NULL, (LPWSTR)"open", (LPWSTR)"D:\\360\\项目\\UML\\ftheword\\Debug\\MMMarkovgraph.png", NULL, NULL, SW_SHOW);
	ShellExecute(NULL, (LPWSTR)"edit", (LPWSTR)"mygraph_wince.png", NULL, NULL, SW_SHOW);
	cout << "Opening   with   WinExec\n";
		
	if (WinExec("dot.exe   -Tpng -omygraph_wince.png  test1.txt ", SW_SHOW) < 32);
		
	cout << "Press   Enter\n";
 
	WinExec(" mygraph_wince.png ", SW_SHOW);


	//if (ShellExecute(NULL, (LPWSTR)"open", (LPWSTR)"mygraph_wince.png", NULL, NULL, SW_SHOW) < (HANDLE)32)
		;

	// 	system("mygraph_wince.png");

	cout<< "Opening   with   ShellExecute\n";
	STARTUPINFO StartInfo = { sizeof(StartInfo) }; // name structure
	PROCESS_INFORMATION ProcInfo; // name structure
	//memset(&ProcInfo, 0, sizeof(ProcInfo)); // Set up memory block,这个很重要


	CreateProcess(NULL, (LPWSTR)"NotePad.exe", NULL, NULL, NULL, NULL, NULL, NULL, &StartInfo, &ProcInfo);//无用

//	if (ShellExecute(NULL,"open", "readme.txt", NULL, NULL, SW_SHOW) < (HANDLE)32)
		;
		;

	/*	system("D:\\360\\项目\\UML\\ftheword\\Debug\\dot.exe   -Tpng -omygraph343.png  test1.txt ");
	Agraph_t *g, *prev = NULL;
	GVC_t *gvc;
	gvc = gvContext();
	gvParseArgs(gvc, argc, argv);
	while ((g = gvNextInputGraph(gvc))) {
		if (prev) {
			gvFreeLayout(gvc, prev);
			agclose(prev);
		}
		gvLayoutJobs(gvc, g);
		gvRenderJobs(gvc, g);
		prev = g;
	}
	return (gvFreeContext(gvc));*/


	/*	GVC_t *gvc;
	Agraph_t *g;
	FILE *fp;

	gvc = gvContext();

	if (argc > 1) {
		std::cout << "File " << argv[1] << std::endl;
		fp = fopen(argv[1], "r");
		if (fp==NULL)
		{
			cout << "error";
		}
	}
	else {
		fp = stdin;
	}


//	g = agread (fp, (Agdisc_t*)0);
	g = agread("mygraph.gv", (Agdisc_t*)0); 
	gvLayout(gvc, g, "dot");
	gvRender(gvc, g, "plain", stdout);
	gvFreeLayout(gvc, g);
	agclose(g);

	return (gvFreeContext(gvc));*/

   int a;
   cin >> a;
}