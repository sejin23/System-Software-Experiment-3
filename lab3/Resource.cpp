#include "Resource.h"
#include <iostream>
using namespace std;

Resource::Resource(string src){
	int i;
	for(i=0;i<3;i++){
		brwdate[i] = 0;
		retdate[i] = 0;
	}
	srcname = src;
	state = 'N';
}
string Resource::getsrcname(){
	return srcname;
}
string Resource::getusrname(){
	return usrname;
}

int Resource::isborrowed(){
	if(state == 'N') return 0;
	else if(state == 'B') return 1;
}

int* Resource::getborroweddate(){
	int* date = new int[3];
	int i;
	for(i=0;i<3;i++) date[i] = brwdate[i];
	return date;
}

int* Resource::getreturndate(){
	int* date = new int[3];
	int i;
	for(i=0;i<3;i++) date[i] = retdate[i];
	return date;
}

void Resource::setBorrow(string mem_name, string mem_type, int* nowdate){
	int i;
	usrname = mem_name;
	state = 'B';
	for(i=0;i<3;i++){
		brwdate[i] = nowdate[i];
		retdate[i] = nowdate[i];
	}
	if(!mem_type.compare("Undergraduate")) retdate[2] += 13;
	else if(!mem_type.compare("Graduate") || !mem_type.compare("Faculty")) retdate[2] += 29;
	if(retdate[2] > 30){
		retdate[2] -= 30;
		retdate[1]++;
	}
	if(retdate[1] > 12){
		retdate[1] -= 12;
		retdate[0]++;
	}
}

int Resource::returnresrc(int* d){
	int i, temp = 0;
	state = 'N';
	for(i=0;i<3;i++){
		if(d[i] > retdate[i]){
			temp = 1;
			break;
		}else if(d[i] < retdate[i]){
			temp = 2;
			break;
		}
	}
	if(temp == 0 || temp == 2) return 1;
	else if(temp == 1) return 2;
}

Book::Book(string src_name):Resource(src_name){
}

Magazine::Magazine(string src_name):Resource(src_name){
}

int Magazine::isborrowedmgz(string month){
	vector<M_User>::iterator iter;
	for(iter=muser.begin();iter!=muser.end();++iter){
		if(!month.compare(iter->month)) return 1;
	}
	return 0;
}

string Magazine::getmgzusrname(string month){
	vector<M_User>::iterator iter;
	for(iter=muser.begin();iter!=muser.end();++iter){
		if(!month.compare(iter->month)) return iter->user;
	}
}

int* Magazine::getmgzborroweddate(string month){
	int i;
	int* newdate = new int[3];
	vector<M_User>::iterator iter;
	for(iter=muser.begin();iter!=muser.end();++iter){
		if(!month.compare(iter->month)){
			for(i=0;i<3;i++) newdate[i] = iter->brwdate[i];
			return newdate;
		}
	}
}

int* Magazine::getmgzreturndate(string month){
	int i;
	int* newdate = new int[3];
	vector<M_User>::iterator iter;
	for(iter=muser.begin();iter!=muser.end();++iter){
		if(!month.compare(iter->month)){
			for(i=0;i<3;i++) newdate[i] = iter->retdate[i];
			return newdate;
		}
	}
}

void Magazine::setMgzBorrow(string mem_name, string mem_type, string month, int* nowdate){
	int i;
	M_User temp;
	temp.user = mem_name;
	temp.month = month;
	for(i=0;i<3;i++){
		temp.brwdate[i] = nowdate[i];
		temp.retdate[i] = nowdate[i];
	}
	if(!mem_type.compare("Undergraduate")) temp.retdate[2] += 13;
	else if(!mem_type.compare("Graduate") || !mem_type.compare("Faculty")) temp.retdate[2] += 29;
	if(temp.retdate[2] > 30){
		temp.retdate[2] -= 30;
		temp.retdate[1]++;
	}
	if(temp.retdate[1] > 12){
		temp.retdate[1] -= 12;
		temp.retdate[0]++;
	}
	muser.push_back(temp);
}

int Magazine::returnMgzsrc(int* d, string month){
	int i, temp = 0;
	vector<M_User>::iterator iter;
	for(iter=muser.begin();iter!=muser.end();++iter){
		if(!month.compare(iter->month)){
			for(i=0;i<3;i++){
				if(d[i] > iter->retdate[i]){
					temp = 1;
					break;
				}else if(d[i] < iter->retdate[i]){
					temp = 2;
					break;
				}
			}
			if(temp == 1) return 2;
			else return 1;
		}
	}
}

E_book::E_book(string src_name, int cap):Resource(src_name){
	capacity = cap;
}

int E_book::getcapacity(){
	return capacity;
}