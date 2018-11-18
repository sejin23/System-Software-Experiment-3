#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    string sp_type, rsc_type, rsc_name, mem_type, mem_name;
    int sp_num, num_of_mem, rsv_time;
    int i = 1, avt;
    char op, sl;
    int* date = new int[4];
    Library* lib;
    ifstream fin("input.dat");
    ifstream frsc("resource.dat");
    ifstream fsp("space.dat");
    ofstream fout("output.dat");
    getline(fsp, sp_type);
    lib = new Library(3, 10, 50);
    fout << "Op_#\tReturn_code\tDescription";
    while(1){
        fin >> date[0] >> sl >> date[1] >> sl >> date[2];
        if(fin.eof()) break;
        fin >> rsc_type >> rsc_name >> op >> mem_type << mem_name;
        if() 
    }
    while(1){
        fsp >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
        if(fsp.eof()) break;
        fsp >> sp_type >> sp_num >> op >> mem_type >> mem_name;
        if(op == 'B') fsp >> num_of_mem >> rsv_time;
        fout << endl;
        if(!lib->validID(sp_type, sp_num)) fout << i << "\t" << 8 << "\tInvalid space id.";
        else if(!lib->executable(date, rsv_time, sp_type, sp_num)){
            fout << i << "\t" << 9 << "\tThis space is not available now. Available from ";
            if(!sp_type.compare("StudyRoom")) fout << "09 to 18.";
            else if(!sp_type.compare("Seat")){
                if(sp_num == 2) fout << "09 to 21.";
                else if(sp_num == 3) fout << "09 to 18.";
            }
        }else if(op == 'R' && !lib->borrowed(mem_name, sp_type, op, date)) fout << i << "\t" << 10 << "\tYou did not borrow this space.";
        else if(op == 'B' && lib->borrowed(mem_name, sp_type, op, date)) fout << i << "\t" << 11 << "\tYou already borrowed this kind of space.";
        else if(op == 'B' && !lib->execmem(sp_type, num_of_mem)) fout << i << "\t" << 12 << "\tExceed available number.";
        else if(lib->exectime(sp_type, mem_name, date, op, rsv_time)) fout << i << "\t" << 13 << "\tExceed available time.";
        else if((avt = lib->fullspace(sp_type, op, sp_num, date)) > 0){
            fout << i << "\t" << 14 << "\tThere is no remain space. This space is available after ";
            if(avt < 10) fout << "0";
            fout << avt << ".";
        } else {
            lib->exeReserve(date, sp_type, sp_num, op, mem_name, mem_type, num_of_mem, rsv_time);
            fout << i << "\t" << 0 << "\tSuccess.";
        }
        i++;
    }
    delete lib;
    delete[] date;
}