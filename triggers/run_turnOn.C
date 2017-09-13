#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
int main(int argc, char* argv[]){
	char cmd[50];
	sprintf(cmd,".x turnOnN_1.C(\"%s\",\"%s\", \"%s\", \"%s\")",argv[1],argv[2], argv[3], argv[4], argv[5]);	
	gROOT->ProcessLine(cmd);
	return 0;
}
