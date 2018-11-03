#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int main(void){
	char sl, operation;
	int result, idx = 1;
	Date* strdate = new Date;
	Date* tempdate;
	Date otherdate;
	string rsrctype, rsrcname, memtype, memname;
	Library* Lib = new Library();
	ifstream fin("input.dat");
	ofstream fout("output.dat");
	getline(fin, rsrctype);
	fout << "Op_#\tReturn_code\tDescription" << endl;
	while(1){
		fin >> strdate->year >> sl >> strdate->month >> sl >> strdate->day;
		fin >> rsrctype >> rsrcname >> operation >> memtype >> memname;
		if(fin.eof()) break;
		result = Lib->setLib(memname, memtype, rsrcname, rsrctype, operation, strdate);
		fout << idx << "\t" << result << "\t";
		switch(result){
			case 0:
				fout << "Success." << endl;
				break;
			case 1:
				fout << "Non exist resource." << endl;
				break;
			case 2:
				fout << "Exceeds your possible number of borrow. Possible # of borrows: ";
				fout << Lib->getMemTypeMaxNOB(memname, memtype) << endl;
				break;
			case 3:
				fout << "You did not borrow this book." << endl;
				break;
			case 4:
				fout << "You already borrowed this book at ";
				tempdate = Lib->getBorrowedDate(rsrcname, rsrctype);
				otherdate.day = tempdate->day - 13;
				otherdate.month = tempdate->month;
				otherdate.year = tempdate->year;
				if(otherdate.day <= 0){
					otherdate.day += 30;
					otherdate.month--;
				}
				if(otherdate.month <= 0){
					otherdate.month += 12;
					otherdate.year--;
				}
				if(otherdate.year < 10) fout << 0;
				fout << otherdate.year << "/";
				if(otherdate.month < 10) fout << 0;
				fout << otherdate.month << "/";
				if(otherdate.day < 10) fout << 0;
				fout << otherdate.day << endl;
				break;
			case 5:
				fout << "Other member already borrowed this book. This book will be returned at ";
				tempdate = Lib->getBorrowedDate(rsrcname, rsrctype);
				if(tempdate->year < 10) fout << 0;
				fout << tempdate->year << "/";
				if(tempdate->month < 10) fout << 0;
				fout << tempdate->month << "/";
				if(tempdate->day < 10) fout << 0;
				fout << tempdate->day << endl;
				break;
			case 6:
				fout << "Restricted member until ";
				tempdate = Lib->getRestrictedDate(memname);
				if(tempdate->year < 10) fout << 0;
				fout << tempdate->year << "/";
				if(tempdate->month < 10) fout << 0;
				fout << tempdate->month << "/";
				if(tempdate->day < 10) fout << 0;
				fout << tempdate->day << endl;
				break;
			case 7:
				fout << "Delayed return. You'll be restricted until ";
				tempdate = Lib->getRestrictedDate(memname);
				if(tempdate->year < 10) fout << 0;
				fout << tempdate->year << "/";
				if(tempdate->month < 10) fout << 0;
				fout << tempdate->month << "/";
				if(tempdate->day < 10) fout << 0;
				fout << tempdate->day << endl;
				break;
		}
		idx++;
	}
	delete strdate;
	delete Lib;
	return 0;
}
