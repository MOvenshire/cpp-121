/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post
	vector<string> UniqueCandTag {};
	std::istringstream iss(postText);
	string word="";
	int len=0;
	string last="";
	int vSize = 0;
	bool repeat = false;
	while(!iss.eof()){
		//load word by spaces
		iss>>word;
		//check if tag
		if(word.at(0)=='#'){
			//remove punctuation
			len = word.length();
			last = word.at(len-1);
			while(last=="."||last=="!"||last==","||last == "?"){
				word=word.substr(0,len-1);
				len=word.length();
				last=word.at(len-1);
			}
			//convert to lowercase
			for(int i = 1;i<len;i++){
				word.at(i)=tolower(word.at(i));
			}
			//check to see if already in vector
			vSize = UniqueCandTag.size();
			if(vSize>0){
				for(int i =0;i<vSize;i++){
					if(UniqueCandTag[i]==word){
						repeat=true;
					}
				}
			}
			if(!repeat){
				UniqueCandTag.push_back(word);
			}
		}
	}
	return UniqueCandTag;
}
