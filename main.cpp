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
        //tsets[k].erase(std::remove_if(tsets[k].begin(), tsets[k].end(), ::isspace), tsets[k].end());
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
            //current_test.erase(std::remove_if(current_test.begin(), current_test.end(), ::isspace), current_test.end());
            for (int x=0; x < int(current_test.length()); x++){
                tolower(current_test[x]);
            }
            cout << "test " << b+1 << " :" << endl;
            
            
            double likely = likelihood(Mmodels[0], current_test);
            double max = likely;
            cout << model_names[0] + ": ";
                
            cout << likely << endl;
            for(int c = 1; c < nb_models; c++){
                
                likely = likelihood(Mmodels[j], current_test);
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

    // Markov_model Mmodel;
    // int order = 2;
    // string Tset = "to sherlock holmes she is always the woman. i have seldom heard him mention her under any other name. in his eyes she eclipses and predominates the whole of her sex. it was not that he felt any emotion akin to love for irene adler. all emotions, and that one particularly, were abhorrent to his cold, precise but admirably balanced mind. he was, i take it, the most perfect reasoning and observing machine that the world has seen, but as a lover he would have placed himself in a false position. he never spoke of the softer passions, save with a gibe and a sneer. they were admirable things for the observer excellent for drawing the veil from men's motives and actions. but for the trained teasoner to admit such intrusions into his own delicate and finely adjusted temperament was to introduce a distracting factor which might throw a doubt upon all his mental results. grit in a sensitive instrument, or a crack in one of his own high-power lenses, would not be more disturbing than a strong emotion in a nature such as his. and yet there was but one woman to him, and that woman was the late irene adler, of dubious and questionable memory. i had seen little of holmes lately. my marriage had drifted us away from each other. my own complete happiness, and the home-centred interests which rise up around the man who first finds himself master of his own establishment, were sufficient to absorb all my attention, while holmes, who loathed every form of society with his whole bohemian soul, remained in our lodgings in baker street, buried among his old books, and alternating from week to week between cocaine and ambition, the drowsiness of the drug, and the fierce energy of his own keen nature. he was still, as ever, deeply attracted by the study of crime, and occupied his immense faculties and extraordinary powers of observation in following out those clews, and clearing up those mysteries which had been abandoned as hopeless by the official police. from time to time i heard some vague account of his doings. of his summons to odessa in the case of the trepoff murder, of his clearing up of the singular tragedy of the atkinson brothers at trincomalee, and finally of the mission which he had accomplished so delicately and successfully for the reigning family of holland. beyond these signs of his activity, however, which i merely shared with all the readers of the daily press, i knew little of my former friend and companion.";
    // Tset.erase(std::remove_if(Tset.begin(), Tset.end(), ::isspace), Tset.end());
    // markov_model(Mmodel, order, Tset);

    // string test = "her situation was, indeed, one of no common trial and difficulty. while she felt the most eager and burning desire to penetrate the mystery in which oliver's history was enveloped, she could not but hold sacred the confidence which the miserable woman with whom she had just conversed, had reposed in her, as a young and guileless girl. her words and manner had touched rose maylie's heart. and, mingled with her love for her young charge, and scarcely less intense in its truth and fervour, was her fond wish to win the outcast back to repentance and hope. they purposed remaining in london only three days, prior to departing for some weeks to a distant part of the coast. it was now midnight of the first day. what course of action could she determine upon, which could be adopted in eight-and-forty hours or how could she postpone the journey without exciting suspicion mr. losberne was with them, and would be for the next two days. but rose was too well acquainted with the excellent gentleman's impetuosity, and foresaw too clearly the wrath with which, in the first explosion of his indignation, he would regard the instrument of oliver's recapture, to trust him with the secret, when her representations in the girl's behalf could be seconded by no experienced person. these were all reasons for the greatest caution and most circumspect behaviour in communicating it to mrs. maylie, whose first impulse would infallibly be to hold a conference with the worthy doctor on the subject. as to resorting to any legal adviser, even if she had known how to do so, it was scarcely to be thought of, for the same reason. once the thought occurred to her of seeking assistance from harry. but this awakened the recollection of their last parting, and it seemed unworthy of her to call him back, when,the tears rose to her eyes as she pursued this train of reflection,he might have by this time learnt to forget her, and to be happier away. disturbed by these different reflections. inclining now to one course and then to another, and again recoiling from all, as each successive consideration presented itself to her mind. rose passed a sleepless and anxious night. after more communing with herself next day, she arrived at the desperate conclusion of consulting harry.";
    // test.erase(std::remove_if(test.begin(), test.end(), ::isspace), test.end());
    // cout << likelihood(Mmodel, test) <<endl;

    // for (char element : Mmodel.alphabet) {
    //     std::cout << element << ' ';
    // }
}
