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
#include "Tag.h"
#include <iostream>

using std::string;
using std::vector;

Tag::Tag(string tagName):tagName(tagName),tagPosts() /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks
	//std::cout<<tagName;
	if(tagName.length()<2){
		throw std::invalid_argument("tag:Too short");
	}
	if(tagName.at(0)!='#'){
		throw std::invalid_argument("tagt:No #");
	}
	int len = tagName.length();
	for(int i =1;i<len;i++){
		if(tagName.at(i)<'a'||tagName.at(i)>'z'){
			throw std::invalid_argument("tag:Not lowercase");
		}
	}
}

string Tag::getTagName() {
  // TODO(student): implement getter
	return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
	return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts
	if(post==nullptr){
		throw std::invalid_argument("post:null pointer");
	}
	else{tagPosts.push_back(post);}
}
