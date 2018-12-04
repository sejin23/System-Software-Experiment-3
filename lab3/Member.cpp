#include <string>
#include "Member.h"
using namespace std;

Member::Member(string mem_name, int usablersc){
	int i;
	e_storage = 0;
	username = mem_name;
	srcnum = 0;
	srcmax = usablersc;
	for(i=0;i<3;i++) delay[i] = 0;
}

Member::~Member(){
}

string Member::getusername(){
	return username;
}

int* Member::getdelayeddate(){
	int* newdelay = new int[3];
	int i;
	for(i=0;i<3;i++) newdelay[i] = delay[i];
	return newdelay;
}

int Member::notborrowmore(){
	if(srcnum >= srcmax) return srcmax;
	else return 0;
}

int Member::isdelayedMem(int* d){
	int i;
	for(i=0;i<3;i++){
		if(delay[i] != 0) break;
	}
	if(i != 3){
		for(i=0;i<3;i++){
			if(delay[i] < d[i]) return 0;
		}
		return 1;
	}else return 0;
}

int Member::setborrow(){
	srcnum++;
}

void Member::setreturn(){
	srcnum--;
}

int* Member::setdelayreturn(int* retd, int* nowd){
	int i, temp = 0;
	int* newdelay = new int[3];
	srcnum--;
	for(i=0;i<3;i++) newdelay[i] = 2*nowd[i] - retd[i];
	if(newdelay[2] < 0){
		newdelay[2] += 30;
		newdelay[1]--;
	}else if(newdelay[2] > 30){
		newdelay[2] -= 30;
		newdelay[1]++;
	}
	if(newdelay[1] < 0){
		newdelay[1] += 12;
		newdelay[0]--;
	}else if(newdelay[1] > 12){
		newdelay[1] -= 12;
		newdelay[0]++;
	}
	for(i=0;i<3;i++){
		if(delay[i] < newdelay[i]){
			temp = 1;
			break;
		}else if(delay[i] > newdelay[i]){
			temp = 2;
			break;
		}
	}
	if(temp == 1){
		for(i=0;i<3;i++) delay[i] = newdelay[i];
	}else{
		for(i=0;i<3;i++) newdelay[i] = delay[i];
	}
	return newdelay;
}

int Member::canmoreEbook(int cap, string src, string mem_type, int* d){
	int newd[3];
	int i, a = 0;
	Ebkin temp;
	temp.rscname = src;
	temp.cap = cap;
	for(i=0;i<3;i++) temp.retd[i] = d[i];
	if(!mem_type.compare("Undergraduate")) temp.retd[2] += 13;
	else temp.retd[2] += 29;
	if(temp.retd[2] > 30){
		temp.retd[2] -= 30;
		temp.retd[1]++;
	}
	if(temp.retd[1] > 12){
		temp.retd[1] -= 12;
		temp.retd[0]++;
	}
	vector<Ebkin>::iterator iter;
	iter = ebk.begin();
	for(;iter!=ebk.end();){
		for(i=0;i<3;i++){
			if(d[i] < iter->retd[i]){
				a = 1;
				break;
			}
			if(d[i] > iter->retd[i]){
				a = 2;
				break;
			}
		}
		if(a == 2){
			e_storage -= iter->cap;
			iter = ebk.erase(iter);
		}else
			++iter;
	}
	if(cap + e_storage > max_storage)
		return 0;
	else{
		e_storage += cap;
		ebk.push_back(temp);
		return 1;
	}
}

int Member::checkEbook(string src, int* d){
	int i, a = 0;
	vector<Ebkin>::iterator iter;
	for(iter=ebk.begin();iter!=ebk.end();++iter){
		if(!src.compare(iter->rscname)){
			for(i=0;i<3;i++){
				if(d[i] < iter->retd[i]){
					a = 1;
					break;
				}else if(d[i] > iter->retd[i]){
					a = 2;
					break;
				}
			}
			if(a == 2) return 0;
			return 1;
		}
	}
	return 0;
}

void Member::deleteEbook(int cap, string src_name){
	vector<Ebkin>::iterator iter;
	for(iter=ebk.begin();iter!=ebk.end();++iter){
		if(!src_name.compare(iter->rscname)){
			e_storage -= iter->cap;
			ebk.erase(iter);
			return;
		}
	}
}

Undergraduate::Undergraduate(string name):Member(name, 1){
	max_storage = 100;
}

Graduate::Graduate(string name):Member(name, 5){
	max_storage = 500;
}

Faculty::Faculty(string name):Member(name, 10){
	max_storage = 1000;
}