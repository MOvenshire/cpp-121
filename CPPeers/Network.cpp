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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network():users(),posts(),tags() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file
	//check if file opened
	std::ifstream ifs(fileName);
	if(!ifs.is_open()){
		throw std::invalid_argument("could not open");
	}
	//get eatch line 
	string line="";
	string word="";
	string name="";
	unsigned int id=0;
	string txt ="";
	getline(ifs,line);
	while(!ifs.eof()){
		//use string stream for each line
		std::istringstream iss(line);
		iss>>word;
		//handle if starts with User
		if(word=="User"){
			iss>>name;
			if(iss.fail()&!iss.eof()){
				throw std::runtime_error("network: fail iss");
			}
			try{this->addUser(name);}
			catch(...){
				throw std::runtime_error("network:change from invalid");
			}
		}
		//handle if starts with Post
		else if(word=="Post"){
		//get id user and txt 
			iss>>id;
			iss>>name;
			int nLen = name.length();
			for(int i =0; i<nLen;i++){
				name.at(i)= tolower(name.at(i));
			}
			if(iss.fail()&!iss.eof()){
				throw std::runtime_error("network: fail iss");
			}
			getline(iss,txt);
			try{this->addPost(id,name,txt);}
			catch(...){
				throw std::runtime_error("post issue");
			}
		}
		else{
			throw std::runtime_error("network:not post of user");
		}
		iss.clear();
		getline(ifs,line);
	}
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
	//make userName lowercase
	int len = userName.length();
	for(int i =0; i<len;i++){
		userName.at(i) = tolower(userName.at(i));
	}
	//create pointer to new user object 
	User* u =new  User(userName);
	//check if the user is already in the network
	int numUsers = users.size();
	for(int i =0; i<numUsers;i++){
		if(userName == users[i]->getUserName()){
			throw std::invalid_argument("network: user already exists");
		}
	}
	users.push_back(u);
	std::cout << "Added User "<<userName<<std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
	//check id already exists
	int numPosts = posts.size();
	for(int i =0;i<numPosts;i++){
		if(posts[i]->getPostId()==postId){
			throw std::invalid_argument("network: id already exists");
		}
	}
	//convert username to lowercase
	int nLen = userName.length();
	for(int i =0; i<nLen;i++){
		userName.at(i)= tolower(userName.at(i));
	}

	//check no user with that name exists
	int numUsers = users.size();
	bool exists = false;
	for(int i =0; i<numUsers;i++){
		if(userName == users[i]->getUserName()){
			exists = true;
		}
	}
	if(!exists){
		throw std::invalid_argument("network: no user with that name exists");
	}

	//create post and add to network posts
	Post* p = new Post(postId,userName,postText);
	posts.push_back(p);
	//add post to user
	for(int i =0; i<numUsers;i++){
		if(userName == users[i]->getUserName()){
			users[i]->addUserPost(p);
		}
	}
	//extract hashtags within post
	vector<string>candTags=p->findTags();

	//for each candidate tag search network tags
	int cTagSize=candTags.size();
	exists = false;
	
	for(int i = 0; i<cTagSize;i++){
		int tSize = tags.size();
		for(int j = 0;j<tSize;j++){
			if(candTags[i]==tags[j]->getTagName()){
				exists=true;
				//add post to tag if exists
				tags[j]->addTagPost(p);
			}
		}
		//add if not exist
		if(!exists){
			try{
				//create a tag and add it to the network
				Tag *t = new Tag(candTags[i]);
				tags.push_back(t);
				//add the post to the tag posts
				tags[tSize]->addTagPost(p);
			}catch(...){}
		}

		exists =false;
	}
	std::cout << "Added Post "<<postId<<" by "<<userName<<std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
	//user empty
	if(userName==""){
		throw std::invalid_argument("network get posts: no name");
	}
	//username not found
	bool found = false;
	int uLen = users.size();
	for(int i =0;i<uLen;i++){
		if(users[i]->getUserName()==userName){
			found=true;
			return users[i]->getUserPosts();
		}
	}
	if(!found){
		throw std::invalid_argument("network get posts: user not found");
	}
	return {};
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
	//tag empty
	if(tagName==""){
		throw std::invalid_argument("network get posts w/ tag: no name");
	}
	//tag not found
	bool found = false;
	int tLen = tags.size();
	for(int i =0;i<tLen;i++){
		if(tags[i]->getTagName()==tagName){
			found=true;
			return tags[i]->getTagPosts();
		}
	}
	if(!found){
		throw std::invalid_argument("network get posts w/ tag: tag not found");
	}
	return {};

}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts
	int tLen = tags.size();
	//network has no hashtag 
	if(tLen==0){
		return {};
	}
	string tag ="";
	int max = tags[0]->getTagPosts().size();
	int s=-1;
	vector<string>hash{};
	//find tag in most posts
	for(int i =1;i<tLen;i++){
		s=tags[i]->getTagPosts().size();
		if(s>max){
			max = s;
		}
	}
	for(int i =0;i<tLen;i++){
		s=tags[i]->getTagPosts().size();
		if(s==max){
			hash.push_back(tags[i]->getTagName());
		}
	}
	//tie so return all 
	return hash;
}	

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
