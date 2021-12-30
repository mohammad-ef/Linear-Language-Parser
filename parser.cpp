#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "grammarProcessing.h"
using namespace std;
int main() {
	grammarProcessing g;
	string * raw_grammar;
	raw_grammar = g.ReadGrammar();
	g.non_terminal_Counter(raw_grammar);
	string ** grammar2D;
	grammar2D=g.processGrammar(raw_grammar);
	cout<<'\n'<<"prossecced grammar"<<'\n';
	for(int i=0;i<g.num_non_terminals;i++){
		cout<<grammar2D[i][0]<<"->";
		for(int j=1;j<g.non_terminal_with_max_rules+1;j++){
			if(grammar2D[i][j]!="Null"){
				if(j!=1)
					cout<<"|"<<grammar2D[i][j];
				else
					cout<<grammar2D[i][j];
				if(grammar2D[i][j]=="")
					cout<<"λ";	
			}else 
			    break;		
		}
		cout<<'\n';
	}
	////////////////////////////////// get a input String And Remove the Blank and give it to the parser function///////////////////////////
	int time=0;
	string non_terminal="S";
	cout<<'\n'<<"inter you string Sq : ";
	getline(cin,g.input_string);
	int passed;
	if(g.input_string!=""){
		for(int i=0 ; i<=g.input_string.length()-1 ; i++)
			if(g.input_string[i]==' ')
				g.input_string.erase(i,1);
		cout<<"This is your input string :"<<g.input_string<<endl<<'\n';		
		passed=g.parser("S", "", "S");	
	}else{
		cout<<"This is your input string :"<<g.input_string<<endl<<'\n';		
		passed=g.parser("S", "", "S");
	}
	if (passed)
		cout<<"parsed";
	else
		cout<<"failed";

	return 0;
}