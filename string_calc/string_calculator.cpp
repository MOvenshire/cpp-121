#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    //use ascii to convert from a character to a number
    int val= static_cast<int>(digit)-48;
    if (val<0||val>9){
        throw std::invalid_argument("Invalid Input Error");
    }
    return val;
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    //use ascii to convert from a number to a character
    char asciiChar=static_cast<char>(decimal+48);
    if (asciiChar<'0'||asciiChar>'9'){
        throw std::invalid_argument("Invalid Input Error");
    }
    return asciiChar;
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    string noZeros="";
    int length= num.size();
    //use a loop to see if there are any zeros and create a new string without them
    for(int i=0;i<length;i++){
        if(num.at(i)!='0' &&(noZeros==""||noZeros=="-")){
            noZeros+=num.at(i);
        }else if(noZeros!=""&&noZeros!="-"){
            noZeros+=num.at(i);
        }
    }//set a string to 0 if all the numbers are 0 
    if (noZeros==""||noZeros=="-"){
        noZeros="0";
    }
    return noZeros;
}


string add(string lhs, string rhs) {
    // TODO(student): implement
    string sumStr="";
    int sum=0;
    //trim zeros and rename stringvariables
    rhs=trim_leading_zeros(rhs);
    lhs=trim_leading_zeros(lhs);
    string right = rhs;
    string left = lhs;
    int leftLen=lhs.size();
    int rightLen=rhs.size();

    //int indexR = rightLen-1;

    string finalStr="";

    //if both strings are negative then add a negative sign to the final string and remove it for calculations
    if(right.at(0) == '-'){
        finalStr="-";
        //readjust strings to not include the negative sign
        right = right.substr(1,rightLen-1);
        rhs = rhs.substr(1,rightLen-1);
        left = left.substr(1,leftLen-1);
        lhs = lhs.substr(1,leftLen-1);
        //re count the size
        rightLen = right.size();
        leftLen = left.size();
    }

    int carry=0;
    //make both numbers the same length by filling in with zeros
    //right
    if(leftLen > rightLen){
        //redefine the string to zero
        right="";
        int difference=leftLen-rightLen;
        for (int i = 0; i < difference; i++){
            right+="0";
        }
        right+=rhs;
        rightLen=right.size();
        
    }

    //left
    if(leftLen < rightLen){
        //re-define the string to empty 
        left="";
        int difference=rightLen-leftLen;
        for (int i = 0; i < difference; i++){
            //add zeros
            left+="0";
        }
        left+=lhs;
        //update the length storage variable to now include the string with zeros
        leftLen=right.size();
    }
    //add numbers of the same length 
    if(leftLen == rightLen){
        for (int i = rightLen-1;i >= 0;i--){
            //assign corresponding place characters to int values
            int leftNum=digit_to_decimal(left.at(i));
            int rightNum=digit_to_decimal(right.at(i));
            //do the actual addition
            sum = leftNum+rightNum+carry;
            //see if the math needs to be carried over 
            if (sum >= 10){
                carry=1;
                sumStr+=decimal_to_digit(sum%10);
            }
            else{
                sumStr+=decimal_to_digit(sum);
                carry=0;
            }
        }
        //add a 1 to the next place if there is still a carry variable left over
        if (carry==1){
            sumStr+="1";
        }
    }


    //turn sumStr around
    int sumStrLen=sumStr.size();
    for(int i = sumStrLen-1; i >= 0; i--){
        finalStr+=sumStr.at(i);
    }

    return finalStr;
}
/***************************************************************/
string multiply(string lhs, string rhs) {
    // TODO(student): implement
    // ccreate empty/ 0 variables 
    string multStr="";
    string multStrForward="";
    int mult=0;
    //trim zeros and rename stringvariables
    rhs=trim_leading_zeros(rhs);
    lhs=trim_leading_zeros(lhs);
    string right = rhs;
    string left = lhs;
    int leftLen=lhs.size();
    int rightLen=rhs.size();
    //create the final output string
    string finalStr="";

    //if both strings are negative remove it for calculations
    if((right.at(0) == '-')&&(left.at(0) == '-')){
        right = right.substr(1,rightLen-1);
        rhs = rhs.substr(1,rightLen-1);
        left = left.substr(1,leftLen-1);
        lhs = lhs.substr(1,leftLen-1);
        rightLen = right.size();
        leftLen = left.size();
    }
    //handle if one is negative and one is positive
    //only right negative
    if((right.at(0) == '-')&&(left.at(0) != '-')){
        finalStr+="-";
        right = right.substr(1,rightLen-1);
        rhs = rhs.substr(1,rightLen-1);
        rightLen = right.size();
    }
    //only left negative
    if((left.at(0) == '-') && (right.at(0) != '-')){
        finalStr+="-";
        left = left.substr(1,leftLen-1);
        lhs = lhs.substr(1,leftLen-1);
        leftLen = left.size();
    }



    int tensMultiplier=0;
    int carry=0;
    string added="0";
    //start multiplication by finding out if the right is smaller than the left
    if(rightLen <= leftLen){
        for (int i = rightLen-1;i >= 0; i--){
            for (int j = leftLen-1;j >= 0; j--){
                tensMultiplier=rightLen-1-i;
                //do multiplication
                mult=digit_to_decimal(right.at(i))*digit_to_decimal(left.at(j))+carry;;
                //set a carry variable to take care of multiples over 10
                //if the calculation is over 10 make a string character by character
                if (mult >= 10){
                    carry=mult/10;
                    multStr+=decimal_to_digit(mult%10);
                }
                else{
                    multStr+=decimal_to_digit(mult);
                    carry=0;
                }
            }//close inner for loop for longer number 
            if (carry != 0){
                multStr+=decimal_to_digit(carry);
            }
            carry=0;
            int multStrLen = multStr.size();
            
            for(int a = multStrLen-1; a >= 0; a--){
                multStrForward+=multStr.at(a);
            }


            //cout<<multStrForward<<endl;
            for( int b = 0; b < tensMultiplier;b++){
                multStrForward+="0";
            }
            //cout<<multStrForward<<endl;
            mult=0;
            added=add(added,multStrForward);
            //cout<<added<<endl;
            multStrForward="";
            multStr="";
        }

    }


    if(rightLen > leftLen){
        for (int i = leftLen-1;i >= 0; i--){
            for (int j = rightLen-1;j >= 0; j--){
                tensMultiplier=leftLen-1-i;
                //do multiplication
                mult=digit_to_decimal(left.at(i))*digit_to_decimal(right.at(j))+carry;;
                //set a carry variable to take care of multiples over 10
                //if the calculation is over 10 make a string character by character
                if (mult >= 10){
                    carry=mult/10;
                    multStr+=decimal_to_digit(mult%10);
                }
                else{
                    multStr+=decimal_to_digit(mult);
                    carry=0;
                }
            }//close inner for loop for longer number 
            if (carry != 0){
                multStr+=decimal_to_digit(carry);
            }
            carry=0;
            int multStrLen = multStr.size();
            
            for(int a = multStrLen-1; a >= 0; a--){
                multStrForward+=multStr.at(a);
            }


            //cout<<multStrForward<<endl;
            for( int b = 0; b < tensMultiplier;b++){
                multStrForward+="0";
            }
            //cout<<multStrForward<<endl;
            mult=0;
            added=add(added,multStrForward);
            //cout<<added<<endl;
            multStrForward="";
            multStr="";
        }

    }
    finalStr+=added;

    return finalStr;
}
