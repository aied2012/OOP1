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

/*
***function markov_model: Takes an empty Markov_model and fills it with the necessary data;
***parameters: an empty Markov_model, the order of the mode and a string to break into data and to add to the model;
***returns: a complete Markov_model;
*/
void markov_model(Markov_model& Mmodel, unsigned int order, const std::string& Tset);

/*
***function laplace: Takes an complete Markov_model and a string to calculate the laplace probability of the string in the model;
***parameters: a complete Markov_model and a string;
***returns: a double that contains laplace probability;
*/
double laplace(const Markov_model& Mmodel, const std::string& word); 


/*
***function likelihood: Takes an complete Markov_model and a string to calculate the sum of laplace probability of each part of the string in the model and then takes the natural log of the sum;
***parameters: a complete Markov_model and a string;
***returns: a double that contains the natural log of the sum of all laplace probablities of the substrings;
*/
double likelihood(Markov_model& Mmodel, const std::string& word);
