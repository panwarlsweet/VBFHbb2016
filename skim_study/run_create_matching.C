#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "CreateTree_b1.h"
#include "CreateTree_b1.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
		TString input_filename = std::string(argv[1]);
		
		TFile *f = TFile::Open(input_filename);
		if (f!=0){	
			CreateTree_b1	*c = new CreateTree_b1(0,input_filename);
			c->Loop();
		}
	return 0;
}
