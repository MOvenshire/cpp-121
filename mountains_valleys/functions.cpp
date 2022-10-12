#include <iostream>
#include "functions.h"


using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if(a <= b && a >= 10 && b <= 10000){
		return true;
	}
	else{
		return false;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int R;
	int L;
	int numDigits=0;
	char key='a';

	while(number>=10){
		//find the right most digit
		R=number%10;
		//divide the number by 10 to get rid of right digit
		number/=10;
		//find new right most digit which is to the left of the previous
		L=number%10;

		//handle the first run through the loop 
		if (key=='a'){
			if(L<R){
				key='u';
				//cout<<"/";
			}
			else if(L>R){
				key='d';
				//cout<<"\\";
			}
			else{
				return 'N';
			}
		}
		//handle all other runs throught the loop
		else{
			if(L<R && key =='d'){
				key='u';
				//cout<<"/";
			}
			else if(L>R && key=='u'){
				key='d';
				//cout<<"\\";
			}
			else{
				return 'N';
			}
		}
		numDigits+=1;
	}

	//even number of digits 
	if(numDigits%2==0&&key=='u'){
		return 'M';
	}
	if(numDigits%2==0&&key=='d'){
		return 'V';
	}
	//odd number of digits
	if (numDigits%2==1&&key=='u'){
		return 'M';
	}
	if (numDigits%2==1&&key=='d'){
		return 'V';
	}
	return 'N';
}	

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	char mv;
	int mountainCount=0;
	int valleyCount=0;

	for(int i=a;i<=b;i+=1){
		mv=classify_mv_range_type(i);
		if (mv=='M'){
			mountainCount+=1;
		}
		if (mv== 'V'){
			valleyCount+=1;
		}
	}
	cout<<"There are "<<mountainCount<<" mountain ranges and "
	<<valleyCount<<" valley ranges between "<<a<<" and "<<b<<"."<<endl;

}


