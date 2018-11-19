#include <iostream>
#include <fstream>
#include <string>
#include "Resource.h"
using namespace std;

int CompareDate(int* srcDate, int* dueDate){
	int i;
	for(i=0;i<3;i++){
		if(srcDate[i] > dueDate[i]) return 0;
	}
	return 1;
}

Resource::Resource(string src_name){
	int i;
	srcname = src_name;
	state = 'X';
	und = NULL;
	for(i=0;i<3;i++) duedate[i] = 0;
}

Resource::~Resource(){
	delete und;
}

Book::Book(string src_name):Resource(src_name){

}

char Book::getrscstate(){
	return state;
}

string Book::getsrcname(){
	return srcname;
}

string Book::getusername(){
	if(und != NULL) return und->getUserName();
}

void Book::borrowresrc(string mem_name, string mem_type, int* d){
	state = 'B';
	if(und != NULL) delete und;
	und = new Undergraduate();
	und->setmember(mem_name);
	duedate[2] = d[2] + 13;
	duedate[1] = d[1];
	duedate[0] = d[0];
	if(duedate[2] > 30){
		duedate[2] -= 30;
		duedate[1]++;
	}
	if(duedate[1] > 12){
		duedate[1] -= 12;
		duedate[0]++;
	}
}

int Book::returnresrc(string mem_name, string mem_type, int* d){
	state = 'X';
	delete und;
	und = NULL;
	if(CompareDate(d, duedate))
		return 1;
	else return 2;
}

int* Book::getdelay(){
	int* d = new int[3];
	int i;
	for(i=0;i<3;i++) d[i] = duedate[i];
	return d;
}