#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "CreateTree_blike.h"
#include "CreateTree_blike.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
		TString input_filename = std::string(argv[1]);
		TString region  = std::string(argv[2]);
		
		TFile *f = TFile::Open(input_filename);
		if (f!=0){	
			CreateTree_blike	*c = new CreateTree_blike(0,input_filename);
			c->Loop(region);
		}
	return 0;
}
