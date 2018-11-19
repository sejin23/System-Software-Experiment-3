#include <string>
#include "Member.h"
using namespace std;
Member::Member(){
}

Undergraduate::Undergraduate():Member(){
	int i;
	numOfBorrow = 1;
	for(i=0;i<3;i++) delayed[i] = 0;
}

string Undergraduate::getUserName(){
	return memname;
}

int Undergraduate::comparedate(int* d){
	int i;
	for(i=0;i<3;i++){
		if(d[i] > delayed[i]) return 0;
	}
	return 1;
}

int* Undergraduate::getdelayed(){
	int* date = new int[3];
	int i;
	for(i=0;i<3;i++) date[i] = delayed[i];
	return date;
}

void Undergraduate::setmember(string mem_name){
	memname = mem_name;
}

void Undergraduate::setdelayed(int* d, int* delay){
	int dif[3];
	int i;
	for(i=0;i<3;i++) dif[i] = d[i] - delay[i];
	if(dif[2] < 0){
		dif[1]--;
		dif[2] += 30;
	}
	if(dif[1] < 0){
		dif[0]--;
		dif[1] += 12;
	}
	delayed[2] = d[2] + dif[2];
	delayed[1] = d[1] + dif[1];
	if(delayed[2] > 30) delayed[1]++;
	delayed[0] = d[0] + dif[0];
	if(delayed[1] > 12) delayed[0]++;
}