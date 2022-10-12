#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	//instantiate variables 
	int start;
	int end;

	// TODO(student): print prompt for input
	cout<<"Enter numbers 10 <= a <= b < 10000: ";

	// TODO(student): read the numbers from standard input
	cin>>start;
	cin>>end;

	// TODO(student): validate input (and reprompt on invalid input)
	while (!(is_valid_range(start,end))){
		cout<<"Invalid Input"<<endl;
		cout<<"Enter numbers 10 <= a <= b < 10000: ";
		cin>>start;
		cin>>end;
	}

	// TODO(student): compute and display solution
	count_valid_mv_numbers(start,end);


	return 0;
}