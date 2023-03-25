#pragma once

#include <set>
#include <map>
#include <string>
#include <cmath>



typedef std::set<char> Alphabet;
typedef std::map<std::string, unsigned int> Model;

struct Markov_model {
unsigned int order; //order of the model
Alphabet alphabet; //symbols of the model
Model model;
};


void markov_model(Markov_model& Mmodel, unsigned int order, const std::string& Tset);


double laplace(const Markov_model& Mmodel, const std::string& word); 



double likelihood(Markov_model& Mmodel, const std::string& word);
