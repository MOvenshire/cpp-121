#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    cout<<">> "<<endl;

    // TODO(student): implement the UI
   	string num1;
   	string plusOrMult="";
   	string num2; 
   	string wholeLn;
   	do {
   		getline(cin,wholeLn);
   		int space1=wholeLn.find(" ");
   		if(space1>0){
   			num1=wholeLn.substr(0,space1);
   			plusOrMult= wholeLn.substr(space1+1,1);
   			num2=wholeLn.substr(space1+3,wholeLn.size()-1);
   			if (plusOrMult == "+"){
   			cout<<"ans ="<<endl<<endl<<"    "<<add(num1,num2)<<endl<<endl<<">> "<<endl;
   			}
   			else{
   				cout<<"ans ="<<endl<<endl<<"    "<<multiply(num1,num2)<<endl<<endl<<">> "<<endl;
   			}
   		}
   		//cout<<space1<<endl;
   		//cout<<num1<<plusOrMult<<"."<<num2;
   		//cout<<wholeLn<<endl;
   	}while (wholeLn != "q" && wholeLn != "quit");

   	cout<<"farvel!"<<endl;


}

