#include <iostream>
#include <fstream>
#include "markov_model.hpp"
#include <cctype>
#include <algorithm>


using namespace std;

void markov_model(Markov_model& Mmodel, unsigned int order, const std::string& Tset){

    try{
        if(order >= Tset.length()){
            throw length_error("The order is not compatible with the Training set");
        }
    }
    catch (const length_error* e)
    {       
        
        cerr << e << endl;
    }

    string Tset_circular = Tset + Tset.substr(0,order);

    Mmodel.order = order;
    
    
    

    for(char c : Tset){
        Mmodel.alphabet.insert(c);
    }


    for(unsigned int i = 0; i < Tset.length(); i++){
        
        Mmodel.model[Tset_circular.substr(i,order+1)]++;
        Mmodel.model[Tset_circular.substr(i,order)]++;
        
    }
   
    
}



double laplace(const Markov_model& Mmodel, const std::string& test){
    
    
    try
    {
        if (Mmodel.order >= test.length()) {
            
            throw length_error("The order is not compatible with the Training set");
        }
        
        try 
        {
            for(char c : test)
            {   
                if (Mmodel.alphabet.count(c) == 0)
                {   

                   
                    throw domain_error("The input data contains symbols that are not present in the alphabet of the Markov model.");

                }
            }

            string s = test.substr(0,test.length()-1);

            auto iterWord = Mmodel.model.find(test);
            int countWord = (iterWord != Mmodel.model.end()) ? iterWord->second : 0;
            auto iterS = Mmodel.model.find(s);
            int countS = (iterS != Mmodel.model.end()) ? iterS->second : 0;

            unsigned int alphabet_size = Mmodel.alphabet.size();

            return double(countWord + 1) / double(countS + alphabet_size);
        }
        catch (const domain_error& e)
        {
            cerr << e.what() << endl;
        }
    }
    catch (const length_error& e)
    {       
        
        cerr << e.what() << endl;
    }
    
    return 0;
}

double likelihood(Markov_model &Mmodel, const std::string &test){
    // aaba -> aabaaa = aab aba baa aaa
    // aa -> aaaa -> aaaa

    string test_circular;

    if(Mmodel.order - test.length() == 1){
        
        test_circular = test + test.substr(0,Mmodel.order-2);

    }else{
        
        test_circular = test + test.substr(0,Mmodel.order);

    }
    
    cout << test_circular.length() << endl;
    cout << test_circular << endl;
    double sumLog = 0.0;
    double laplaceValue = 0.0;
    
    for(int i = 0; i < int(test.length()); i++){
        
        laplaceValue = laplace(Mmodel, test_circular.substr(i, Mmodel.order+1));
        if(laplaceValue == 0){
            return 0;
        }
        sumLog += log(laplaceValue);
        
    }
    
    return sumLog;
}

