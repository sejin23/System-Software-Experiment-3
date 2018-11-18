#include <string>
#include "Member.h"

Member::Member(){
	rsvhead = NULL;
}

Undergraduate::Undergraduate():Member(){
	maxRST = 3;
	numOfBorrow = 1;
}

string Undergraduate::getUserName(){
	return memname;
}
