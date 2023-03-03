#include <iostream>
#include <fstream>
#include "markov_model.hpp"


void markov_model(Markov_model& Mmodel, unsigned int order, const std::string& Tset){

    if(order > Tset.length()){
        throw length_error("The order is not compatible with the Training set");
    }

    string Tset_circular = Tset + Tset.substr(0,order);

    Mmodel.order = order;
    
    
    

    for(unsigned int i = 0; i < Tset.length(); i++){
        Mmodel.alphabet.insert(Tset[i]);
    }


    for(unsigned int i = 0; i < Tset.length(); i++){
        
        Mmodel.model[Tset_circular.substr(i,order+1)]++;
        
    }
    for(unsigned int i = 0; i < Tset.length(); i++){
        
        Mmodel.model[Tset_circular.substr(i,order)]++;
        
    }
}

double laplace(const Markov_model& Mmodel, const std::string& word){
    //Missig exception
    //CHECKING THE DOMAIN
    for(char c : word){
        if(Mmodel.alphabet.count(c) == 0){
            throw domain_error("The input data contains symbols not present in the alphabet of the Markov model.");
        }
    }
    string s = word.substr(0,word.length()-1);
    char c = word[word.length()-1];
    auto iterWord = Mmodel.model.find(word);
    int countWord = iterWord->second;
    auto iterS = Mmodel.model.find(s);
    // size_t pos = word.find(s);
    // int count = 0;
    // while (pos != string::npos) {
    //     count++;
    //     pos = word.find(s, pos + s.length());
    // }
    // unsigned int countS = count;
    int countS = iterS->second;
    
    return double(countWord + 1) / double(countS + word.length());
}

double likelihood(Markov_model &Mmodel, const std::string &word){
    // aaba -> aabaaa = aab aba baa aaa

    string word_circular = word + word.substr(0,Mmodel.order);

    double sumLog = 0.0;

    for(int i = 0; i < word.length(); i++){
        cout << word_circular.substr(i, Mmodel.order+1)<<endl;
        cout << laplace(Mmodel, word_circular.substr(i, Mmodel.order+1)) << endl;
        sumLog += log(laplace(Mmodel, word_circular.substr(i, Mmodel.order+1)));
        
    }

    return sumLog;
}

int main(){
    Markov_model Mmodel;
    unsigned int order = 2;
    string Tset = "abccbaabacba";

    markov_model(Mmodel, order, Tset);


    cout << likelihood(Mmodel, "aaba") <<endl;

    for (char element : Mmodel.alphabet) {
        std::cout << element << ' ';
    }
}