#include <iostream>
#include <string>
#include <sstream>

#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList():head(nullptr),tail(nullptr) {
	// Implement this function
}

LinkedList::~LinkedList(){
	// Implement this function
	clear();
}

LinkedList::LinkedList(const LinkedList& source) {
	// Implement this function
	//set head 
	Node * curr = source.getHead();
	//use insert to add to list
	while(curr!=nullptr){
		//get values from source
		std::string ID = curr->data.id;
		int yr = curr->data.year;
		int m = curr->data.month;
		double tmp = curr->data.temperature;
		//use insert to add to linked list
		this->insert(ID,yr,m,tmp);
		curr= curr->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function
	//set head 
	Node * curr = source.getHead();
	//use insert to add to list
	while(curr!=nullptr){
		//get values from source
		std::string ID = curr->data.id;
		int yr = curr->data.year;
		int m = curr->data.month;
		double tmp = curr->data.temperature;
		//use insert to add to linked list
		this->insert(ID,yr,m,tmp);
		curr= curr->next;
	}
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	// Implement this function
	Node* add = new Node(location,year,month,temperature);
	//insert to empty
	if(head==nullptr){
		head= add;
		tail=add;
	}else{
		Node* curr = head;
		Node* previous = nullptr;
		while(curr!=nullptr){
			if(*add<*curr){
				break;
			}
			previous = curr;
			curr = curr->next;
		}
		//curr=head add new node before and reset head
		if(curr==head){
			add->next = curr;
			head = add;
		}
		//curr == nullptr add to end resets tail 
		else if(curr ==nullptr){
			previous->next = add;
			tail = add;
		}
		//middle of list prev->add->curr
		else{
			previous->next = add;
			add->next= curr;
		}
	}
}



void LinkedList::clear() {
	// Implement this function
	//test if already empty _headptr is null
    while(head!=nullptr){
        Node* n = head->next;
        delete head;
        head = n;
    }
    tail = nullptr;
	
}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	string outputString="";
	//string line;
	std::ostringstream oss;
	
	// Implement this function
	Node* n = head;
	while(n!=nullptr){
		oss<<n->data.id<<" ";
		oss<<n->data.year<<" ";
		oss<<n->data.month<<" ";
		oss<<n->data.temperature<<"\n";
		
		n =n->next;
    }
    outputString = oss.str();
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
