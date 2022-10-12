// TODO: Implement this source file
#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>

#include "MyString.h"

using std::cout,std::endl,std::ostream,std::fstream;
//default constructor
MyString::MyString():sizeVal(0),capacityVal(1),cRay(nullptr){
	cRay = new char[capacityVal];
	cRay[sizeVal]='\0';
}
//parametrized constructor
MyString::MyString(const char* charArray):sizeVal(0),capacityVal(1),cRay(nullptr){
	while(charArray[sizeVal]!='\0'){
		capacityVal++;
		sizeVal++;
	}
	cRay = new char[capacityVal];
	for (size_t i = 0; i < sizeVal; ++i) {
		cRay[i] = charArray[i];
	}
	cRay[capacityVal-1]='\0';
}
//copy constuctor
MyString::MyString(const MyString& mStr):sizeVal(0),capacityVal(1),cRay(nullptr){
	sizeVal = mStr.sizeVal;
	capacityVal = mStr.capacityVal;
	cRay = new char[capacityVal];
	for (size_t i = 0; i < sizeVal; ++i) {
		cRay[i] = mStr.cRay[i];
	}
	cRay[capacityVal-1]='\0';
}
//destructor 
MyString::~MyString(){
	delete []cRay;
}

// MyString functions that will be implemented in .cpp
//resize
void MyString::resize(size_t n){
	if(n>sizeVal){
		char* newCRay = new char[n+1];
		for (size_t i = 0; i < sizeVal; ++i) {
			newCRay[i] = cRay[i];
		}
		delete[]cRay;
		newCRay[sizeVal] = '\0';
		cRay = newCRay;
	}else{
		cRay[n]='\0';
	}

	sizeVal = n; 
	capacityVal = n+1;

	// deallocate old contents
	// set old contents to new contents
}

//capacity
size_t MyString::capacity()const{
	return capacityVal;
}

//size note that length and size are same
size_t MyString::size()const{
	return sizeVal;
}
//length
size_t MyString::length(){
	return sizeVal;
}
//data
const char* MyString::data()const{
	//return cRay 
	if(cRay != nullptr){
		return cRay;
	}
	return nullptr;

}
//empty
bool MyString::empty(){
	if(cRay==nullptr||cRay[0]=='\0'){
		return true;
	}else{
		return false;
	}
} 
//front
const char& MyString::front()const{
	return cRay[0];
}
//atS
char MyString::at(size_t index)const{
	if(index>=sizeVal){
		throw std::invalid_argument("wrong index");
	}
	return cRay[index];
}
//clear
void MyString::clear(){
	if(cRay!=nullptr){
		sizeVal = 0;
		cRay[sizeVal]='\0';
	}
}
//operator <<
ostream& operator<<(ostream& os, const MyString& str){
	
	for(size_t i = 0;i<str.size();i++){
		os<<str.data()[i];
	}

	return os;
}
//operator =
MyString& MyString::operator=(const MyString& str){
	if(this==&str){
		return *this;
	}
	this->sizeVal = str.sizeVal;
	this->capacityVal = str.capacityVal;
	if(str.cRay!=nullptr){
		delete[]cRay;
		cRay = new char[capacityVal];
		for (size_t i = 0; i < sizeVal; ++i) {
			cRay[i] = str.cRay[i];
		}
		cRay[capacityVal-1]='\0';
	}
	return *this;
}
//operator +=
MyString& MyString::operator+=(const MyString& str){
	//resize cRay
	size_t originalS = sizeVal;
	resize(sizeVal+str.sizeVal);
	//copy str.cRay over
	for(unsigned int i =0;i<str.sizeVal;i++){
		cRay[i+originalS] = str.cRay[i];
	}
	cRay[sizeVal]='\0';

	return *this;
}
//find
size_t MyString::find(const MyString& str, size_t pos)const{
	//str is the one to find
	//this is the one to search in 
	bool same = false;
	//loop through mystring (this)
	//check position not greater than size 
	if(pos>sizeVal){
		return -1;
	}
	if(sizeVal<str.sizeVal){
		return -1;
	}

	for(size_t i=pos;i<sizeVal;i++){
		same = true;
		for(size_t j= 0;j<str.sizeVal;j++){
			if(cRay[i+j]!=str.cRay[j]){
				same=false;
			}
		}
		if(same){
			return i;
		}
	}
	return -1;
}

//extra credit 

bool operator== (const MyString& lhs, const MyString& rhs){
	if (! (lhs.size() == rhs.size()
		&& lhs.capacity() == rhs.capacity())) {
		return false;
	}

	// checking sections
	for (size_t i = 0; i < lhs.size(); i++) {
		char ls = lhs.data()[i];
		char rs = rhs.data()[i];
		if (!(ls==rs)) {
			return false;
		}
	}
	return true;
}

/*
MyString operator+ (const MyString& lhs, const MyString& rhs){
	return this;
}*/