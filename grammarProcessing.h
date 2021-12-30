#ifndef grammarPROCESSING_H_   
#define grammarPROCESSING_H_
#include <string>
#include <iostream>
using namespace std;
class grammarProcessing {
    public:
        int non_terminal_with_max_rules=0; //(A->a  A->b) rules of A equals to 2
	    int num_non_terminals=0;
        int rules_counter=0;
        string* ReadGrammar();
        int parser(string non_terminal, string rule, string current_string);
        void non_terminal_Counter(string* raw_grammar);
        string**  processGrammar(string* raw_grammar);
        int* num_non_terminal_rules; //it's an array
        string** grammar2D;
        string input_string ="";
        int answer=0;
};
#endif