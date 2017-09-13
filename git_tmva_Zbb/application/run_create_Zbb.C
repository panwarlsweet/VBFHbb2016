#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "CreateTree_Zbb.h"
#include "CreateTree_Zbb.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
		TString input_filename = std::string(argv[1]);
		TString filename = std::string(argv[2]);
		
		TFile *f = TFile::Open(input_filename);
		if (f!=0){	
			CreateTree_Zbb	*c = new CreateTree_Zbb(0,input_filename);
			c->Loop(input_filename, filename);
		}
	return 0;
}
