#include "markov_model.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
    Markov_model Mmodels[argc];
    string model_names[argc];
    unsigned int order = atoi(argv[1]);
    
    int separation_index;
    int nb_models = 0;
    string tsets[argc];
    string line;
    int k = 0;

    for(int x = 2;  string(argv[x]) != "---"; x++){
        ifstream Tdata(argv[x]);
        if(!Tdata.is_open()) {
            cerr << "Cannot open file\n";
            
        }
        else{
            getline(Tdata,line);
            model_names[k] = line;
            while (getline(Tdata, line)) {
                tsets[k] += line + '\n';
            }
        }
        
        for (int x=0; x < int(tsets[k].length()); x++){
            tolower(tsets[k][x]);
        }
        markov_model(Mmodels[k], order, tsets[k]);
        separation_index = x+1;
        nb_models++;
        k++;
        Tdata.close();
    }
    string current_test;
    int j = separation_index+1;
    string tests[argc-j];
    int b = 0;
    while(j < argc){
        ifstream testfile(argv[j]);
        if(testfile.is_open()) {
            while (getline(testfile, line)) {
                tests[b] += line + '\n';
            }
            current_test = tests[b];
            
            for (int x=0; x < int(current_test.length()); x++){
                tolower(current_test[x]);
            }
            cout << argv[j] << " :" << endl;
            
            
            double likely;
            try {

                size_t pos = current_test.find_first_of("\r\n");

                while (pos != string::npos) {
                    current_test.erase(pos, 1);
                    pos = current_test.find_first_of("\r\n", pos);
                }
                
                likely = likelihood(Mmodels[0], current_test);
            }
            catch (const exception& e) {
                
                likely = 0;
            }
            double max = likely;
            cout << model_names[0] + ": ";
                
            if(likely == 0){
                cout << '-' << endl;
                }
            else{
                cout << likely << endl;
            }

            for(int c = 1; c < nb_models; c++){
                
                try {

                    size_t pos = current_test.find_first_of("\r\n");

                    while (pos != string::npos) {
                        current_test.erase(pos, 1);
                        pos = current_test.find_first_of("\r\n", pos);
                    }

                    likely = likelihood(Mmodels[c], current_test);

                }
                catch (const exception& e) {
                    
                    likely = 0;
                }
                cout << model_names[c] + ":";

                if(likely == 0){
                    cout << '-' << endl;
                }
                else{
                    cout << likely << endl;
                }
                if(max < likely && likely != 0){
                    max = likely;
                }
            }
            if(max == 0){
                cout << argv[j] << " Highest likelihood : " << '-' << endl;
            }
            else{
                cout << argv[j] << " Highest likelihood : " << max << endl; 
            }
            testfile.close();
        }
        else{
            
            cerr << "Cannot open file\n";
            return 0;
        }
        j++;
        b++;
        cout << endl;
    }   

    
}
