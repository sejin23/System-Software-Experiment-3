#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

Date* DelayedDate(Date* condate, Date* duedate){
	int upday = 0, upmonth = 0;
	Date* delayed = new Date;
	if(condate->day < duedate->day) upday = 1;
	delayed->day = condate->day + 30*upday - duedate->day;
	if(condate->month - upday < duedate->month) upmonth = 1;
	delayed->month = condate->month - upday + 12*upmonth - duedate->month;
	delayed->year = condate->year - upmonth - duedate->year;
	
	delayed->day += condate->day;
	delayed->month += condate->month + delayed->day/30;
	delayed->year += condate->year + delayed->year/12;
	delayed->month %= 12;
	delayed->day %= 30;
	return delayed;
}

Library::Library(){
	header = NULL;
	Resrc = new Resource();
	Resrc->setResrc();
}

Library::~Library(){
	Mem* temp = header;
	Mem* prev;
	delete Resrc;
	while(temp != NULL){
		prev = temp->next;
		if(temp->user) delete temp->user;
		delete temp;
		temp = prev;
	}
}

int Library::setLib(string username, string usertype, string Src, string Srctype, char state, Date* condate){
	int res, req = 10;
	Mem* prev;
	Mem* temp = header;
	Date* resdate;
	Date* delaydate;
	if(!Resrc->findResrc(Src, Srctype)) return 1;
	if(header != NULL){
		if(state == 'B'){
			while(temp != NULL){
				prev = temp;
				if(!username.compare(temp->user->getMemName())){
					if(temp->numOfBorrow >= temp->user->getNOBbyMem(usertype)){
						req = 2;
						break;
					}
					if(Resrc->findOverlap(username, Src, Srctype, state)){
						req = 4;
						break;
					}
					if(CompareDate(condate, &temp->restricted)){
						req = 6;
						break;
					}
					temp->numOfBorrow++;
					break;
				}
				temp = temp->next;
			}
			if(temp == NULL){
				temp = new Mem;
				temp->user = new Member(username, usertype);
				temp->numOfBorrow = 1;
				temp->restricted.year = 0;
				temp->restricted.month = 0;
				temp->restricted.day = 0;
				temp->next = NULL;
				prev->next = temp;
			}
		}else{
			while(temp != NULL){		
				if(!username.compare(temp->user->getMemName())){
					temp->numOfBorrow--;
					if(temp->numOfBorrow < 0){
						delete temp->user;
						prev->next = temp->next;
						delete temp;
					}
					break;
				}
				prev = temp;
				temp = temp->next;
			}
		}
	}else{
		if(state == 'B'){
			temp = new Mem;
			temp->user = new Member(username, usertype);
			temp->numOfBorrow = 1;
			temp->restricted.year = 0;
			temp->restricted.month = 0;
			temp->restricted.day = 0;
			temp->next = NULL;
			header = temp;
		}
	}
	res = Resrc->confirmResrc(Src, Srctype, username, usertype, condate, state);
	if((res == 0 && req < 10) || (req < res && res > 0)){
		return req;
	}
	res = Resrc->searchResrc(Src, Srctype, username, usertype, condate, state);
	if(res == 7){
		resdate = Resrc->getdueDate(Src, Srctype);
		delaydate = DelayedDate(condate, resdate);
		temp = header;
		while(temp != NULL){
			prev = temp;
			if(!username.compare(temp->user->getMemName())){
				temp->restricted.year = delaydate->year;
				temp->restricted.month = delaydate->month;
				temp->restricted.day = delaydate->day;
				break;
			}
			temp = temp->next;
		}
		if(temp == NULL){
			temp = new Mem;
			temp->numOfBorrow = 0;
			temp->user = new Member(username, usertype);
			temp->restricted.year = delaydate->year;
			temp->restricted.month = delaydate->month;
			temp->restricted.day = delaydate->day;
			temp->next = NULL;
			prev->next = NULL;
		}
		delete delaydate;
	}
	return res;
}

int Library::getMemTypeMaxNOB(string memname, string memtype){
	Member mem(memname, memtype);
	return mem.getNOBbyMem(memtype);
}

Date* Library::getBorrowedDate(string src, string srctype){
	return Resrc->getdueDate(src, srctype);
}

Date* Library::getRestrictedDate(string memname){
	Mem* temp = header;
	while(temp != NULL){
		if(!memname.compare(temp->user->getMemName()))
			return &temp->restricted;
	}
}
