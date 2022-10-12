/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"
#include <iostream>

using std::string;
using std::vector;

User::User(string userName):userName(userName),userPosts() /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
	//check if empty string
	if(userName==""){
		throw std::invalid_argument("User Name is empty");
	}
	int len = userName.length();
	//check if all lowercase letters
	for(int i =0;i<len;i++){
		if(userName.at(i)<'a'||userName.at(i)>'z'){
			throw std::invalid_argument("User Name is not lowercase");
		}
	}

}

string User::getUserName() {
  // TODO(student): implement getter
	return userName;
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
	return userPosts;
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts
	if(post==nullptr){
		throw std::invalid_argument("user: no post");
	}
	else{
		userPosts.push_back(post);
	}
}
