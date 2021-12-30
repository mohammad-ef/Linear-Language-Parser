#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "grammarProcessing.h"
#include <string>
#include "grammarProcessing.h"
using namespace std;
/////////////////////////////read a grammar and enumerate all rules
string* grammarProcessing :: ReadGrammar(){
	std::ifstream file("Grammar.txt");
	string * raw_grammar;
	if (file.is_open()){
		std::string file_contents;
		while (std::getline(file, file_contents))
				rules_counter++;
        file.clear();
        file.seekg(0);
		raw_grammar=new string[rules_counter];
        int i=0;
		while (std::getline(file, file_contents))
			{
			  	raw_grammar[i]=file_contents;
			  	i++;
			  	file_contents.push_back('\n');
			}
	}else{
		cout<<file.is_open();
	}
    return raw_grammar;
}
//----------------------------------------------------------------

void grammarProcessing :: non_terminal_Counter(string* raw_grammar){// determine the non_terminal with maximum rule
	string previous_non_terminal=" ";
	int num_non_terminal_rules=1;
	for(int i=0;i<rules_counter;i++){
		if(raw_grammar[i].substr (0,1).compare(previous_non_terminal)!= 0){
			num_non_terminals++;
			num_non_terminal_rules=1;
		}else
			num_non_terminal_rules++;

		if(non_terminal_with_max_rules<num_non_terminal_rules)
			non_terminal_with_max_rules=num_non_terminal_rules;

		previous_non_terminal=raw_grammar[i].substr (0,1);
	}
}

string**  grammarProcessing :: processGrammar(string* raw_grammar){// read the raw grammar and put it in a 2D array showing in terminal
    num_non_terminal_rules = new int[num_non_terminals];
    int h=0;
    int non_terminal_rules_counter=1;
    string current_non_terminal=raw_grammar[0].substr (0,1);
    for(int i=0;i<rules_counter;i++){
        while(i+1<rules_counter and raw_grammar[i+1].substr (0,1).compare(current_non_terminal)== 0){
            non_terminal_rules_counter++;
            i++;
        }
        
        num_non_terminal_rules[h]=non_terminal_rules_counter;
        h+=1;
        non_terminal_rules_counter=1;
        if(i+1<rules_counter){
            current_non_terminal=raw_grammar[i+1].substr (0,1);
        }
    }

    grammar2D = new string*[num_non_terminals];
    
    for(int i=0;i<num_non_terminals;i++){
        grammar2D[i] = new string[non_terminal_with_max_rules+1];
        for(int j=0;j<non_terminal_with_max_rules+1;j++)
            grammar2D[i][j]="Null"; 
    }
    int r=0;
    for(int i=0;i<num_non_terminals;i++){
        grammar2D[i][0]=raw_grammar[r].substr(0,1);
        for(int j=1;j<=num_non_terminal_rules[i];j++){
            grammar2D[i][j]=raw_grammar[r].substr (3,raw_grammar[r].length());
            r++;
        }
    }        
    cout<<'\n';
    return grammar2D;
}
////////////////////////////parsing the string with the grammar//////////////////////////
int grammarProcessing :: parser(string non_terminal, string rule, string current_string){
	/////////////////////////////check current generated string equals to input string or not//////////////////////////////////////
	if(current_string==input_string){
			cout<<"***"<<current_string<<"***"<<'\n';
			return answer=1;
		}
	///////////////////////////////////////////////////////////////////
	if(answer==1)		
		return answer;
	else{
		///////////////////////////// find the row in which non_termenal is presence.///////////////////////////////////
		int row=0;
		for(int i=0;i<num_non_terminals;i++)
			if(non_terminal==grammar2D[i][0]){
				row=i;	
				break;
			}
		/////////////////////////////reject the unpromising current generated string//////////////////////////////////////
		int non_terminal_index=0;
		int c1=0;
		for(;c1<current_string.length();c1++)
			if(current_string[c1]>='A' and current_string[c1]<='Z'){
				string str = current_string;
				str.erase(c1,1);
				string substring = str.substr(c1, str.length() - c1);	
				if(current_string.substr(0, c1)!=input_string.substr(0, c1) or (substring!="" and (input_string.rfind(substring)==-1 or (input_string.rfind(substring) + substring.length()) != input_string.length()))){
					cout<<current_string<<"!="<<input_string<<" !!!Return!!!"<<'\n';
					return 0;
				}else{
					non_terminal_index=c1;
					break;
				}
			}
		if(c1==current_string.length() and current_string!=input_string){
			cout<<current_string<<"!="<<input_string<<"  !!!Return!!!"<<'\n';
			return answer=0;
		}
		/////////////////////////////insert a rule in promising current generated string///////////////////////////////
		for(int j=1;j<=num_non_terminal_rules[row];j++){
			string temp=current_string;
			temp.erase(non_terminal_index,1);
			temp.insert(non_terminal_index, grammar2D[row][j]);
			if(answer==0){
				cout<<"rule: "<<grammar2D[row][0]<<"->"<<grammar2D[row][j]<<'\n';
				cout<<"current_string: "<<temp<<'\n';
			}
			for(int c2=0;c2<temp.length();c2++){
				if(temp[c2]>='A' and temp[c2]<='Z'){
					non_terminal=temp[c2];
					break;
				}/*else
					non_terminal="";*/
			}
			if(answer!=1)		
				parser(non_terminal, grammar2D[row][j], temp);
			else
				return 1;
		}
	}	
	return answer;
}
