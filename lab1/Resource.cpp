#include <iostream>
#include <fstream>
#include <string>
#include "Resource.h"

int CompareDate(Date* srcDate, Date* dueDate){
	if(srcDate->year > dueDate->year) return 0;
	else if(srcDate->month > dueDate->month) return 0;
	else if(srcDate->day > dueDate->day) return 0;
	return 1;
}

Book::Book(){
	header = NULL;
}

Book::~Book(){
	Rsrcs* temp = header;
	Rsrcs* prev;
	while(temp != NULL){
		prev = temp->next;
		if(temp->Mem != NULL) delete temp->Mem;
		delete temp;
		temp = prev;
	}
}

void Book::setBook(string src){
	Rsrcs* newSrc = new Rsrcs;
	Rsrcs* temp = header;
	newSrc->Rsrcname = src;
	newSrc->next = NULL;
	newSrc->state = 'N';
	if(header == NULL) header = newSrc;
	else{
		while(temp->next != NULL) temp = temp->next;
		temp->next = newSrc;
	}
}

Date* Book::getBookdueDate(string src){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!src.compare(temp->Rsrcname)) return temp->dueDate;
		temp = temp->next;
	}
}

int Book::IsExisted(string src){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!src.compare(temp->Rsrcname)) return 1;
		temp = temp->next;
	}
	return 0;
}

int Book::IsOverlap(string name, string src){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!src.compare(temp->Rsrcname) && temp->Mem != NULL){
			if(!name.compare(temp->Mem->getMemName())) return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int Book::getBorrowBook(string src, string memname, string memtype, Date* borrowdate){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!temp->Rsrcname.compare(src)){
			if(temp->state == 'B'){
				if(!memname.compare(temp->Mem->getMemName())) return 4;
				else return 5;
			}
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int Book::setBorrowBook(string src, string memname, string memtype, Date* borrowdate){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!temp->Rsrcname.compare(src)){
			if(temp->state == 'B'){
				if(!memname.compare(temp->Mem->getMemName())) return 4;
				else return 5;
			}
			temp->Mem = new Member(memname, memtype);
			temp->dueDate = new Date;
			temp->dueDate->year = borrowdate->year + (borrowdate->month + (borrowdate->day + 13)/30)/12;
			temp->dueDate->month = (borrowdate->month + (borrowdate->day + 13)/30)%12;
			temp->dueDate->day = (borrowdate->day + 13)%30;
			temp->state = 'B';
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

int Book::setReturnBook(string src, string memname, string memtype, Date* returndate){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!temp->Rsrcname.compare(src)){
			if(temp->state == 'B' && CompareDate(returndate, temp->dueDate)){
				if(memname.compare(temp->Mem->getMemName())) return 3;
				temp->state = 'N';
				delete temp->Mem;
				temp->Mem = NULL;
				return 0;
			}else if(temp->state == 'N') return 3;
			else{
				temp->state = 'N';
				delete temp->Mem;
				temp->Mem = NULL;
				return 7;
			}
		}
		temp = temp->next;
	}
	return 1;
}

int Book::getReturnBook(string src, string memname, string memtype, Date* returndate){
	Rsrcs* temp = header;
	while(temp != NULL){
		if(!temp->Rsrcname.compare(src)){
			if(temp->state == 'B' && CompareDate(returndate, temp->dueDate)){
				if(memname.compare(temp->Mem->getMemName())) return 3;
				return 0;
			}else if(temp->state == 'N') return 3;
			else return 7;
		}
		temp = temp->next;
	}
	return 1;
}

Resource::Resource(){
}

Resource::~Resource(){
}

void Resource::setResrc(){
	string rsrcType, rsrcName;
	ifstream fin("resource.dat");
	fin >> rsrcType >> rsrcName;
	while(!fin.eof()){
		fin >> rsrcType >> rsrcName;
		if(!rsrcType.compare("Book")) Book::setBook(rsrcName);
		rsrcType = "";
		rsrcName = "";
	}
}

int Resource::findResrc(string src, string type){
	if(!type.compare("Book"))
		return Book::IsExisted(src);
}

int Resource::findOverlap(string memname, string srcname, string srctype, char state){
	if(state == 'R') return 0;
	if(!srctype.compare("Book"))
		return Book::IsOverlap(memname, srcname);
}

int Resource::searchResrc(string src, string type, string memname, string memtype, Date* strdate, char stat){
	if(!type.compare("Book")){
		if(stat == 'B') return Book::setBorrowBook(src, memname, memtype, strdate);
		else if(stat == 'R') return Book::setReturnBook(src, memname, memtype, strdate);
	}
}

int Resource::confirmResrc(string src, string type, string memname, string memtype, Date* strdate, char stat){
	if(!type.compare("Book")){
		if(stat == 'B') return Book::getBorrowBook(src, memname, memtype, strdate);
		else if(stat == 'R') return Book::getReturnBook(src, memname, memtype, strdate);
	}
}

Date* Resource::getdueDate(string src, string type){
	return Book::getBookdueDate(src);
}
