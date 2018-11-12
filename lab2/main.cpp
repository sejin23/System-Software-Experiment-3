#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    string sp_type, mem_type, mem_name;
    int sp_num, num_of_mem, rsv_time;
    int i = 1, res;
    char op, sl;
    int* date = new int[4];
    Library* lib;
    ifstream fin("space.dat");
    ofstream fout("output.dat");
    getline(fin, sp_type);
    lib = new Library(3, 10, 50);
    cout << "Op_#\tReturn_code\tDescription\n";
    while(1){
        fin >> date[0] >> sl >> date[1] >> sl >> date[2] >> sl >> date[3];
        if(fin.eof()) break;
        fin >> sp_type >> sp_num >> op >> mem_type >> mem_name;
        if(op == 'B') fin >> num_of_mem >> rsv_time;
        if(!lib->validID(sp_type, sp_num)) cout << i << "\t" << 8 << "\t" << "Invalid space id." << endl;
        else if(!lib->executable(date, rsv_time, sp_type, sp_num)) cout << i << "\t" << 9 << "\t" << "This space is not available now. Available from " << endl;
        else if(op == 'R' && !lib->borrowed(mem_name, sp_type, op, sp_num, date)) cout << i << "\t" << 10 << "\t" << "You did not borrow this space." << endl;
        else if(op == 'B' && lib->borrowed(mem_name, sp_type, op, sp_num, date)) cout << i << "\t" << 11 << "\t" << "You already borrowed this kind of place" << endl;
        else if(!lib->execmem(sp_type, op, num_of_mem)) cout << i << "\t" << 12 << "\t" << "Exceed available number." << endl;
        else if(lib->exectime()) 
        res = lib->exeReserve(date, sp_type, sp_num, op, mem_type, mem_name, num_of_mem, rsv_time);
        cout << mem_name << " " << mem_type << " " << res << endl;
        
        //cout << i << "\t" << "\n";
        i++;
    }

    delete lib;
    delete[] date;
}