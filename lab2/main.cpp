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
    string sp_type, mem_type, mem_name;
    string rsc_type, rsc_name, inmem_type, inmem_name;
    int sp_num, num_of_mem, rsv_time;
    int i = 1, j, avt, k = 0, inbreak = 0, spbreak = 0;
    char op, inop, sl;
    int* date = new int[4];
    int* indate = new int[3];
    int* res;
    Library* lib;
    ifstream fin("input.dat");
    ifstream fsp("space.dat");
    getline(fin, sp_type);
    getline(fsp, sp_type);
    lib = new Library(3, 10, 50);
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
        if(k == 1) lib->BorrowResource(i, indate, rsc_type, rsc_name, inmem_type, inmem_name, inop);
        else if(k == 2) lib->BorrowSpace(i, date, sp_type, sp_num, mem_type, mem_name, op, num_of_mem, rsv_time);
        i++;
    }
    fin.close();
    fsp.close();
    delete lib;
    delete[] indate;
    delete[] date;
}