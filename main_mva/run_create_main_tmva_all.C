#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "CreateTree_tmva_all.h"
#include "CreateTree_tmva_all.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
		TString output_dir = std::string(argv[1]);
		int data = atoi(argv[2]);
		int set_type = atoi(argv[3]);
		stringstream ss;
		ss.str(argv[4]); //list of files
		vector<string> list_of_files; //comma separated string and then parse before the loop for AddFile ;
		while( ss.good() )
		{
   		string substr;
    		getline( ss, substr, ',' );
    		list_of_files.push_back( substr );
		}
		
		TFile *f = TFile::Open(list_of_files[0].c_str());
		if (f!=0){	
			CreateTree_tmva_all	*c = new CreateTree_tmva_all(list_of_files[0]);
			for (int i=1;i<list_of_files.size();i++){
				c->AddFile(list_of_files[i]); 
			}
			c->Loop(output_dir,data,set_type);
		}
	return 0;
}
