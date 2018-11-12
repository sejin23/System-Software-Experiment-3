#include <string>
#include "Library.h"
using namespace std;

Library::Library(int fl, int room_n, int seat_n){
    int i, j;
    floor_m = fl;
    room_m = room_n;
    seat_m = seat_n;
    str = new Study_Room*[room_n];
    for(i=0;i<room_n;i++) str[i] = NULL;
    set = new Seat**[fl];
    for(i=0;i<fl;i++){
        set[i] = new Seat*[seat_n];
        for(j=0;j<seat_n;j++) set[i][j] = NULL;
    }
    seat_status = new int[fl];
    for(i=0;i<fl;i++) seat_status[i] = 0;
    room_status = 0;
}

Library::~Library(){
    int i;
    delete[] seat_status;
    delete[] str;
    for(i=0;i<3;i++) delete[] set[i];
    delete[] set;
}

int Library::exeReserve(int* d, string sp_type, int sp_n, char op, string mem_type, string mem_name, int mem_n, int rsv_time){
}

int Library::validID(string sp_type, int sp_n){
    if(!sp_type.compare("StudyRoom"))
        if(sp_n < 1 || sp_n > room_m) return 0;
    else if(!sp_type.compare("Seat"))
        if(sp_n < 1 || sp_n > floor_m) return 0;
    return 1;    
}

int Library::executable(int* d, int rsv_time, string sp_type, int fl){
    if(!sp_type.compare("StudentRoom") && (d[3] < 9 || d[3] > 18)) return 0;
    else if(!sp_type.compare("Seat"))
        if((fl == 2 && (d[3] < 9 || d[3] > 21)) || (fl == 3 && (d[3] < 9 || d[3] > 18))) return 0;
    return 1;
}

int Library::borrowed(string mem_name, string sp_type, char op, int sp_n, int* d){
    int i, j;
    if(!sp_type.compare("StudyRoom")){
        for(i=0;i<room_m;i++){
            if(str[i] == NULL) continue;
            else if(!mem_name.compare(str[i]->getusrname()))
                if(str[i]->validate(d, op)) return 1;
        }
    }else if(!sp_type.compare("Seat")){
        for(i=0;i<floor_m;i++){
            for(j=0;j<room_m;j++){
                if(set[i][j] == NULL) continue;
                else if(!mem_name.compare(set[i][j]->getusrname()))
                    if(set[i][j]->validate(d, op)) return 1;
            }
        }
    }
    return 0;
}

int Library::execmem(string sp_type, char op, int mem_n){
    if(op != 'B') return 1;
    if(!sp_type.compare("StudyRoom") && mem_n > 6) return 0;
    else if(!sp_type.compare("Seat") && mem_n > 1) return 0;
    return 1;
}

int Library::exectime(string mem_name, int* d, char op, int rsv_time){
    int i, res = 0;
    if(op != 'B') return 1;
    for(i=0;i<room_m;i++){
        if(str[i] != NULL && !mem_name.compare(str[i]->getusrname())){

        }
    }
}

int Library::fullspace(string sp_type, char op, int sp_n, int* d){
    if(op != 'B') return 0;
    if(!sp_type.compare("StudyRoom")){
        if(str[sp_n-1] != NULL && )
    }
    return 0;
}