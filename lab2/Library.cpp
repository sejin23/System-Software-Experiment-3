#include <string>
#include <iostream>
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
    int i, j;
    delete[] seat_status;
    for(i=0;i<10;i++) delete str[i];
    delete[] str;
    for(i=0;i<3;i++){
        for(j=0;j<50;j++) delete set[i][j];
    }
    for(i=0;i<3;i++) delete[] set[i];

    delete[] set;
}

void Library::exeReserve(int* d, string sp_type, int sp_n, char op, string mem_name, string mem_type, int mem_n, int rsv_time){
    int i;
    if(!sp_type.compare("StudyRoom")){
        if(op == 'B'){
            if(str[sp_n-1] == NULL) str[sp_n-1] = new Study_Room();
            str[sp_n-1]->setResrv(mem_name, rsv_time, mem_n, d);
            room_status++;
        }else if(op == 'R'){
            delete str[sp_n-1];
            str[sp_n-1] = NULL;
            room_status--;
        }else if(op == 'E')
            str[sp_n-1]->setstate(op);
        else if(op == 'C')
            str[sp_n-1]->setstate('B');
    }else if(!sp_type.compare("Seat")){
        for(i=0;i<seat_m;i++){
            if(op == 'B'){
                if(set[sp_n-1][i]==NULL || set[sp_n-1][i]->validate(d, op)){
                    if(set[sp_n-1][i] == NULL) set[sp_n-1][i] = new Seat();
                    set[sp_n-1][i]->borrResrv(mem_name, d, rsv_time, sp_n);
                    seat_status[sp_n-1]++;
                    break;
                }
            }else if(op == 'R'){
                if(set[sp_n-1][i]!=NULL && !mem_name.compare(set[sp_n-1][i]->getusrname()) && set[sp_n-1][i]->validate(d, op)){
                    delete set[sp_n-1][i];
                    set[sp_n][i] = NULL;
                    seat_status[sp_n-1]--;
                    break;
                }
            }else if(op == 'E'){
                if(set[sp_n-1][i]!=NULL && !mem_name.compare(set[sp_n-1][i]->getusrname()) && set[sp_n-1][i]->validate(d, op)){
                    set[sp_n][i]->emtResrv();
                    break;
                }
            }else if(op == 'C'){
                if(set[sp_n-1][i]!=NULL && !mem_name.compare(set[sp_n-1][i]->getusrname()) && set[sp_n-1][i]->validate(d, op)){
                    set[sp_n][i]->emtResrv();
                    break;
                }
            }
        }
        
    }
}

int Library::validID(string sp_type, int sp_n){
    if(!sp_type.compare("StudyRoom")){
        if(sp_n < 1 || sp_n > room_m) return 0;
    }else if(!sp_type.compare("Seat")){
        if(sp_n < 1 || sp_n > floor_m) return 0;
    }
    return 1;    
}

int Library::executable(int* d, int rsv_time, string sp_type, int fl){
    if(!sp_type.compare("StudyRoom") && (d[3] < 9 || d[3] > 18)) return 0;
    else if(!sp_type.compare("Seat")){
        if((fl == 2 && (d[3] < 9 || d[3] > 21)) || (fl == 3 && (d[3] < 9 || d[3] > 18))) return 0;
    }
    return 1;
}

int Library::borrowed(string mem_name, string sp_type, char op, int* d){
    int i, j;
    if(!sp_type.compare("StudyRoom")){
        for(i=0;i<room_m;i++){
            if(str[i] == NULL) continue;
            else if(!mem_name.compare(str[i]->getusrname())){
                if(str[i]->validate(d, op)) return 1;
            }
        }
    }else if(!sp_type.compare("Seat")){
        for(i=0;i<floor_m;i++){
            for(j=0;j<room_m;j++){
                if(set[i][j] == NULL) continue;
                else if(!mem_name.compare(set[i][j]->getusrname())){
                    if(set[i][j]->validate(d, op)) return 1;
                }
            }
        }
    }
    return 0;
}

int Library::execmem(string sp_type, int mem_n){
    if(!sp_type.compare("StudyRoom")){
        if(mem_n < 1 || mem_n > 6) return 0;
    }else if(!sp_type.compare("Seat")){
        if(mem_n != 1) return 0;
    }
    return 1;
}

int Library::exectime(string sp_type, string mem_name, int* d, char op, int rsv_time){
    if(op != 'B') return 0;
    int i, j, sum = rsv_time;
    if(!sp_type.compare("StudyRoom")){
        for(i=0;i<room_m;i++){
            if(str[i] != NULL && str[i]->validate(d, op)){
                if(!mem_name.compare(str[i]->getusrname()))
                    sum += str[i]->getrsvtime();
            }
        }
    }else{
        for(i=0;i<floor_m;i++){
            for(j=0;j<seat_m;j++){
                if(set[i][j] != NULL && set[i][j]->validate(d, op)){
                    if(!mem_name.compare(set[i][j]->getusrname()))
                        sum += set[i][j]->getrsvtime();
                }
            }
        }
    }
    if(sum > 3) return 1;
    return 0;
}

int Library::fullspace(string sp_type, char op, int sp_n, int* d){
    int i, j, tem, min = 24;
    int* std;
    if(op != 'B') return 0;
    if(!sp_type.compare("StudyRoom")){
        if(str[sp_n-1] != NULL && str[sp_n-1]->validate(d, op)){
            std = str[sp_n-1]->getstartdate();
            return std[3] + str[sp_n-1]->getrsvtime();
        }
    }else if(!sp_type.compare("Seat")){
        if(seat_status[sp_n-1] >= room_m){
            for(j=0;j<seat_m;j++){
                if(set[sp_n-1][j] != NULL && set[sp_n-1][j]->validate(d, op)){
                    std = set[sp_n-1][j]->getstartdate();
                    tem = set[sp_n-1][j]->getrsvtime();
                    if(min > std[3] + tem) min = std[3] + tem;
                }
            }
            return min;
        }
    }
    return 0;
}