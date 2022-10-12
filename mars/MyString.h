// TODO: Implement this header file
#ifndef MyString_H
#define MyString_H

#include <iostream>
#include <fstream>

using std::cout,std::endl,std::ostream,std::fstream;

class MyString {
	private:
		size_t sizeVal; 
		size_t capacityVal;
		char* cRay;
	public:
		// constructors
		//deafult constructor
		MyString();
		//parameterized constructor / c-string
		//MyString(const char* charArray,size_t n);
		MyString(const char* charArray);
		//copy constuctor
		MyString(const MyString& mStr);
	
		// MyString functions that will be implemented in .cpp
		//resize
		void resize(size_t n);
		//capacity
		size_t capacity()const;
		//size
		size_t size()const;
		//length
		size_t length();
		//data
		const char* data()const;
		//empty
		bool empty(); 
		//front
		const char& front()const;
		//at
		char at(size_t index)const;
		//clear
		void clear();
		//find
		size_t find(const MyString& str, size_t pos = 0)const;
		//operator =
		MyString& operator=(const MyString& str);
		//operator +=
		MyString& operator+=(const MyString& str);

		//destructor
		~MyString();


};
//operator <<
ostream& operator<<(ostream& os,const MyString& str);
//extra credit operators
bool operator== (const MyString& lhs, const MyString& rhs);
//MyString operator+ (const MyString& lhs, const MyString& rhs);
#endif