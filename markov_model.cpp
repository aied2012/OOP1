#include <iostream>
#include <fstream>
#include "markov_model.hpp"
#include <cctype>
#include <algorithm>


using namespace std;

void markov_model(Markov_model& Mmodel, unsigned int order, const std::string& Tset){

    if(order > Tset.length()){
        throw length_error("The order is not compatible with the Training set");
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
    //CHECKING LENGTH
    // if(Mmodel.order > test.length()){
    //     throw length_error("The order is not compatible with the Training set");
    // }
    try {
        if (Mmodel.order > test.length()) {
            //cout << c << endl;
            throw length_error("The order is not compatible with the Training set");
            
        }
        }
    catch (const length_error& e) {
        // cerr << "Error: " << e.what() << endl;
        return 0;
        
    }
    //CHECKING THE DOMAIN
    for(char c : test){
        // if(Mmodel.alphabet.count(c) == 0){
        //     cout << "-" << endl;
        //     throw domain_error("The input data contains symbols not present in the alphabet of the Markov model.");
        // }
        
        try {
            if (Mmodel.alphabet.count(c) == 0) {
                
                throw domain_error("The input data contains symbols that are not present in the alphabet of the Markov model.");
                
            }
            }
        catch (const domain_error& e) {
            // cerr << "Error: " << e.what() << endl;
            cout << c << endl;
            return 0;
            
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

double likelihood(Markov_model &Mmodel, const std::string &test){
    // aaba -> aabaaa = aab aba baa aaa

    string test_circular = test + test.substr(0,Mmodel.order);

    double sumLog = 0.0;
    double laplaceValue = 0.0;
    //cout << int(test.length())<<endl;
    for(int i = 0; i < int(test.length()); i++){
        //cout << test_circular.substr(i, Mmodel.order+1)<<endl;
        // cout << laplace(Mmodel, word_circular.substr(i, Mmodel.order+1)) << endl;
        laplaceValue = laplace(Mmodel, test_circular.substr(i, Mmodel.order+1));
        if(laplaceValue == 0){
            return 0;
        }
        sumLog += log(laplaceValue);
        
    }
    // for (const auto& elem : Mmodel.alphabet) {
    //     std::cout << elem << " ";
    // }
    //cout << endl;
    return sumLog;
}

// int main(){
//     Markov_model Mmodels;
//     markov_model(Mmodels,2, "to sherlock holmes she is always the woman. i have seldom heard him mention her under any other name. in his eyes she eclipses and predominates the whole of her sex. it was not that he felt any emotion akin to love for irene adler. all emotions, and that one particularly, were abhorrent to his cold, precise but admirably balanced mind. he was, i take it, the most perfect reasoning and observing machine that the world has seen, but as a lover he would have placed himself in a false position. he never spoke of the softer passions, save with a gibe and a sneer. they were admirable things for the observer excellent for drawing the veil from men's motives and actions. but for the trained teasoner to admit such intrusions into his own delicate and finely adjusted temperament was to introduce a distracting factor which might throw a doubt upon all his mental results. grit in a sensitive instrument, or a crack in one of his own high-power lenses, would not be more disturbing than a strong emotion in a nature such as his. and yet there was but one woman to him, and that woman was the late irene adler, of dubious and questionable memory. i had seen little of holmes lately. my marriage had drifted us away from each other. my own complete happiness, and the home-centred interests which rise up around the man who first finds himself master of his own establishment, were sufficient to absorb all my attention, while holmes, who loathed every form of society with his whole bohemian soul, remained in our lodgings in baker street, buried among his old books, and alternating from week to week between cocaine and ambition, the drowsiness of the drug, and the fierce energy of his own keen nature. he was still, as ever, deeply attracted by the study of crime, and occupied his immense faculties and extraordinary powers of observation in following out those clews, and clearing up those mysteries which had been abandoned as hopeless by the official police. from time to time i heard some vague account of his doings. of his summons to odessa in the case of the trepoff murder, of his clearing up of the singular tragedy of the atkinson brothers at trincomalee, and finally of the mission which he had accomplished so delicately and successfully for the reigning family of holland. beyond these signs of his activity, however, which i merely shared with all the readers of the daily press, i knew little of my former friend and companion.");
    
//     //cout<< laplace(Mmodels, "aab") + laplace(Mmodels, "aba") + laplace(Mmodels, "baa") + laplace(Mmodels, "aaa")<< endl;
//     cout << likelihood(Mmodels, "sa situation etait, en effet, une epreuve et une difficulte peu communes. alors qu'elle ressentait le desir le plus ardent de penetrer le mystere dans lequel l'histoire d'oliver etait enveloppee, elle ne pouvait que garder sacree la confiance que la miserable femme avec laquelle elle venait de converser avait placee en elle, alors qu'elle etait une jeune fille sans artifice. ses paroles et ses manieres avaient touche le coeur de rose maylie . et, mele a son amour pour sa jeune protegee, et a peine moins intense dans sa verite et sa ferveur, il y avait son desir affectueux de ramener la proscrite au repentir et a l'espoir. ils avaient l'intention de ne rester a londres que trois jours, avant de partir pour quelques semaines dans une partie eloignee de la cote. il etait maintenant minuit le premier jour. quel plan d'action pouvait-elle determiner, qui pourrait etre adopte en huit heures et quarante minutes   ou comment pourrait-elle reporter le voyage sans eveiller les soupcons   m. losberne etait avec eux, et le serait pendant les deux jours suivants . mais rose connaissait trop bien l'impetuosite de l'excellent gentleman, et prevoyait trop clairement la colere avec laquelle, dans la premiere explosion de son indignation, il considererait l'instrument de la capture d'oliver, pour lui confier le secret, alors que ses representations en faveur de la jeune fille ne pouvaient etre appuyees par aucune personne experimentee. toutes ces raisons justifiaient la plus grande prudence et la plus grande circonspection dans la communication de cette information a mrs. maylie, dont la premiere impulsion serait infailliblement de tenir une conference avec le digne docteur sur ce sujet. quant au recours a un conseiller juridique, meme si elle avait su le faire, elle n'y aurait guere songe, pour la meme raison. une fois, il lui vint a l'esprit de demander l'aide de harry . mais cela reveilla le souvenir de leur derniere separation, et il lui sembla indigne d'elle de le rappeler, alors que - les larmes lui montaient aux yeux tandis qu'elle poursuivait ce train de reflexions - il aurait peut-etre appris a cette heure a l'oublier, et a etre plus heureux au loin. troublee par ces differentes reflexions, inclinant tantot vers une voie, tantot vers une autre, et reculant encore devant toutes, a mesure que chaque consideration successive se presentait a son esprit, rose passa une nuit insomniaque et anxieuse. le lendemain, apres avoir communie davantage avec elle-meme, elle arriva a la conclusion desesperee de consulter harry.");
//     }
