#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    string sp_type, rsc_type, rsc_name, mem_type, mem_name;
    int sp_num, num_of_mem, rsv_time;
    int i = 1, j, avt;
    char op, sl;
    int* date = new int[4];
    int* res;
    Library* lib;
    ifstream fin("input.dat");
    ifstream fsp("space.dat");
    ofstream fout("output.dat");
    getline(fin, sp_type);
    lib = new Library(3, 10, 50);
    fout << "Op_#\tReturn_code\tDescription";
    while(1){
        fin >> date[0] >> sl >> date[1] >> sl >> date[2];
        if(fin.eof()) break;
        fin >> rsc_type >> rsc_name >> op >> mem_type >> mem_name;
        fout << endl;
        if(!lib->searchRsc(rsc_name)) fout << i << "\t1\tNon exist resource.";
        else if(lib->execresrc(mem_name, mem_type, op, date)) fout << i << "\t2\tExceeds your possible number of borrow. Possible # of borrows: 1";
        else if(op == 'R' && lib->isBorrowed(mem_name, mem_type, rsc_type, rsc_name, op)) fout << i << "\t3\tYou did not borrow this book.";
        else if(op == 'B' && lib->isBorrowed(mem_name, mem_type, rsc_type, rsc_name, op) == 1){
            fout << i << "\t4\tYou already borrowed this book at ";
            res = lib->borroweddate(mem_name, mem_type, rsc_name, rsc_type);
            for(j=0;j<3;j++){
                if(j>0) fout << "/";
                if(res[j] < 10) fout << "0";
                fout << res[j];
            }
            delete[] res;
        }else if(op == 'B' && lib->isBorrowed(mem_name, mem_type, rsc_type, rsc_name, op) == 2){
            fout << i << "\t5\tOther member already borrowed this book. This book will be returned at ";
            res = lib->borroweddate(mem_name, mem_type, rsc_name, rsc_type);
            for(j=0;j<3;j++){
                if(j>0) fout << "/";
                if(res[j] < 10) fout << "0";
                fout << res[j];
            }
            delete[] res;
        }else if(lib->isDelayedMem(mem_name, mem_type, op, date)){
            fout << i << "\t6\tRestricted member until ";
            res = lib->delayeddate(mem_name, mem_type);
            for(j=0;j<3;j++){
                if(j>0) fout << "/";
                if(res[j] < 10) fout << "0";
                fout << res[j];
            }
            delete[] res;
        }else {
            avt = lib->setBorrow(mem_name, mem_type, rsc_name, rsc_type, op, date);
            if(avt == 2){
                fout << i << "\t7\tDelayed return. You'll be restricted until ";
                res = lib->delayeddate(mem_name, mem_type);
                for(j=0;j<3;j++){
                    if(j>0) fout << "/";
                    if(res[j] < 10) fout << "0";
                    fout << res[j];
                }
                delete[] res;
            }else fout << i << "\t0\tSuccess.";
        }
        i++;
    }
    getline(fsp, sp_type);
    while(1){
        fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
        if(fsp.eof()) break;
        fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
        if(op == 'B') fsp >> num_of_mem >> rsv_time;
        fout << endl;
        if(!lib->validID(sp_type, sp_num)) fout << i << "\t8\tInvalid space id.";
        else if(!lib->executable(date, rsv_time, sp_type, sp_num)){
            fout << i << "\t9\tThis space is not available now. Available from ";
            if(!sp_type.compare("StudyRoom")) fout << "09 to 18.";
            else if(!sp_type.compare("Seat")){
                if(sp_num == 2) fout << "09 to 21.";
                else if(sp_num == 3) fout << "09 to 18.";
            }
        }else if(op == 'R' && !lib->borrowed(mem_name, sp_type, op, date)) fout << i << "\t10\tYou did not borrow this space.";
        else if(op == 'B' && lib->borrowed(mem_name, sp_type, op, date)) fout << i << "\t11\tYou already borrowed this kind of space.";
        else if(op == 'B' && !lib->execmem(sp_type, num_of_mem)) fout << i << "\t12\tExceed available number.";
        else if(lib->exectime(sp_type, mem_name, date, op, rsv_time)) fout << i << "\t13\tExceed available time.";
        else if((avt = lib->fullspace(sp_type, op, sp_num, date)) > 0){
            fout << i << "\t14\tThere is no remain space. This space is available after ";
            if(avt < 10) fout << "0";
            fout << avt << ".";
        } else {
            lib->exeReserve(date, sp_type, sp_num, op, mem_name, mem_type, num_of_mem, rsv_time);
            fout << i << "\t0\tSuccess.";
        }
        i++;
    }
    delete lib;
    delete[] date;
}