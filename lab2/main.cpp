#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int cmpdate(int* in, int* sp){
    if(in[0] != sp[0]%100){
        if(in[0] > sp[0]%100) return 2;
        else return 1;
    }
    if(in[1] != sp[1]){
        if(in[1] > sp[1]) return 2;
        else return 1;
    }
    if(in[2] != sp[2]){
        if(in[2] > sp[2]) return 2;
        else return 1;
    }
    return 1;
}

int main(int argc, char** argv){
    string sp_type, rsc_type, rsc_name, mem_type, mem_name, inmem_type, inmem_name;
    int sp_num, num_of_mem, rsv_time;
    int i = 1, j, avt, k = 0, inbreak = 0, spbreak = 0;
    char op, inop, sl;
    int* date = new int[4];
    int* indate = new int[3];
    int* res;
    Library* lib;
    ifstream fin("input.dat");
    ifstream fsp("space.dat");
    ofstream fout("output.dat");
    getline(fin, sp_type);
    getline(fsp, sp_type);
    lib = new Library(3, 10, 50);
    fout << "Op_#\tReturn_code\tDescription";
    while(1){
        if(k == 0){
            fin >> indate[0] >> sl >> indate[1] >> sl >> indate[2];
            fin >> rsc_type >> rsc_name >> inop >> inmem_type >> inmem_name;
            fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
            fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
            if(op == 'B') fsp >> num_of_mem >> rsv_time;
        }else if(k == 1){
            fin >> indate[0] >> sl >> indate[1] >> sl >> indate[2];
            if(fin.eof()) inbreak = 1;
            fin >> rsc_type >> rsc_name >> inop >> inmem_type >> inmem_name;
        }else{
            fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
            if(fsp.eof()) spbreak = 1;
            fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
            if(op == 'B') fsp >> num_of_mem >> rsv_time;
        }
        if(!inbreak && !spbreak)
            k = cmpdate(indate, date);
        else if(inbreak && spbreak)
            break;
        else{
            if(inbreak) k = 2;
            else if(spbreak) k = 1;
        }
        fout << endl;
        if(k == 1){
            if(!lib->searchRsc(rsc_name)) fout << i << "\t1\tNon exist resource.";
            else if(lib->execresrc(inmem_name, inmem_type, inop, indate)) fout << i << "\t2\tExceeds your possible number of borrow. Possible # of borrows: 1";
            else if(inop == 'R' && lib->isBorrowed(inmem_name, inmem_type, rsc_type, rsc_name, inop)) fout << i << "\t3\tYou did not borrow this book.";
            else if(inop == 'B' && lib->isBorrowed(inmem_name, inmem_type, rsc_type, rsc_name, inop) == 1){
                fout << i << "\t4\tYou already borrowed this book at ";
                res = lib->borroweddate(inmem_name, inmem_type, rsc_name, rsc_type);
                for(j=0;j<3;j++){
                    if(j>0) fout << "/";
                    if(res[j] < 10) fout << "0";
                    fout << res[j];
                }
                delete[] res;
            }else if(inop == 'B' && lib->isBorrowed(inmem_name, inmem_type, rsc_type, rsc_name, inop) == 2){
                fout << i << "\t5\tOther member already borrowed this book. This book will be returned at ";
                res = lib->borroweddate(inmem_name, inmem_type, rsc_name, rsc_type);
                for(j=0;j<3;j++){
                    if(j>0) fout << "/";
                    if(res[j] < 10) fout << "0";
                    fout << res[j];
                }
                delete[] res;
            }else if(lib->isDelayedMem(inmem_name, inmem_type, inop, indate)){
                fout << i << "\t6\tRestricted member until ";
                res = lib->delayeddate(inmem_name, inmem_type);
                for(j=0;j<3;j++){
                    if(j>0) fout << "/";
                    if(res[j] < 10) fout << "0";
                    fout << res[j];
                }
                delete[] res;
            }else {
                avt = lib->setBorrow(inmem_name, inmem_type, rsc_name, rsc_type, inop, indate);
                if(avt == 2){
                    fout << i << "\t7\tDelayed return. You'll be restricted until ";
                    res = lib->delayeddate(inmem_name, inmem_type);
                    for(j=0;j<3;j++){
                        if(j>0) fout << "/";
                        if(res[j] < 10) fout << "0";
                        fout << res[j];
                    }
                    delete[] res;
                }else fout << i << "\t0\tSuccess.";
            }
        }else{
            //cout << i << date[0] << date[1] << date[2] << date[3] << sp_type << sp_num << op << mem_type << mem_name << endl;
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
        }
        i++;
    }
    delete lib;
    delete[] date;
    delete[] indate;
}