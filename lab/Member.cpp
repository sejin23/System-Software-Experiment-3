#include <string>
#include "Member.h"

Undergraduate::Undergraduate(){
	numOfBorrow = 1;
}

int Undergraduate::getNumOfBorr(){
	return numOfBorrow;
}

Member::Member(string name, string type){
	Rsrcname = name;
}

string Member::getMemName(){
	return Rsrcname;
}

int Member::getNOBbyMem(string type){
	if(!type.compare("Undergraduate")) return Undergraduate::getNumOfBorr();
}
