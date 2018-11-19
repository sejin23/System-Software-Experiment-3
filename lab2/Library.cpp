#include <string>
#include <fstream>
#include <iostream>
#include "Library.h"
using namespace std;

Library::Library(int fl, int room_n, int seat_n){
    int i, j;
    floor_m = fl;
    room_m = room_n;
    seat_m = seat_n;
    string rsrcType, rsrcName;
    book = new Book*[100];
    rstd_mem = NULL;
	ifstream fin("resource.dat");
	fin >> rsrcType >> rsrcName;
    i = 0;
	while(1){
		fin >> rsrcType >> rsrcName;
		if(fin.eof()) break;
        if(!rsrcType.compare("Book")){
            book[i] = new Book(rsrcName);
            i++;
        }
	}
    rsc_m = i;
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
    for(i=0;i<rsc_m;i++) delete book[i];
    delete[] book;
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
                    set[sp_n-1][i] = NULL;
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
        if((fl == 2 && (d[3] < 9 || d[3] >= 21)) || (fl == 3 && (d[3] < 9 || d[3] >= 18))) return 0;
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
                if(set[i][j] != NULL){
                    if(!mem_name.compare(set[i][j]->getusrname())){
                        if(set[i][j]->validate(d, op)) return 1;
                    }
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

int Library::searchRsc(string src_name){
    int i;
    for(i=0;i<rsc_m;i++){
        if(!src_name.compare(book[i]->getsrcname())) return 1;
    }
    return 0;
}

int Library::execresrc(string mem_name, string mem_type, char op, int* d){
    int i, sum = 1;
    if(op != 'B') return 0;
    for(i=0;i<rsc_m;i++){
        if(book[i]->getrscstate() == 'B' && !mem_name.compare(book[i]->getusername())) sum++;
    }
    if(!mem_type.compare("Undergraduate") && sum > 1) return 1;
    return 0;
}

int Library::isBorrowed(string mem_name, string mem_type, string rsc_type, string rsc_name, char op){
    int i;
    if(op == 'R'){
        for(i=0;i<rsc_m;i++){
            if(!rsc_name.compare(book[i]->getsrcname())){
                if(mem_name.compare(book[i]->getusername())) return 1;
                break;
            }
        }
        return 0;
    }else if(op == 'B'){
        for(i=0;i<rsc_m;i++){
            if(!rsc_name.compare(book[i]->getsrcname())){
                if(book[i]->getrscstate() == 'B') {
                    if(!mem_name.compare(book[i]->getusername())) return 1;
                    else return 2;
                }
                break;
            }
        }
        return 0;
    }
}

int* Library::borroweddate(string mem_name, string mem_type, string rsc_name, string rsc_type){
    int i, j;
    for(i=0;i<rsc_m;i++){
        if(!rsc_name.compare(book[i]->getsrcname()))
            return book[i]->getdelay();
    }
}

int Library::isDelayedMem(string mem_name, string mem_type, char op, int* d){
    rsted* temp = rstd_mem;
    if(rstd_mem == NULL || op != 'B') return 0;
    while(temp != NULL){
        if(!mem_type.compare("Undergraduate")){
            if(!mem_name.compare(temp->und->getUserName())){
                if(temp->und->comparedate(d)) return 1;
                break;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int* Library::delayeddate(string mem_name, string mem_type){
    rsted* temp = rstd_mem;
    while(temp != NULL){
        if(!mem_type.compare("Undergraduate")){
            if(!mem_name.compare(temp->und->getUserName()))
                return temp->und->getdelayed();
        }
        temp = temp->next;
    }
}

int Library::setBorrow(string mem_name, string mem_type, string rsc_name, string rsc_type, char op, int* d){
    int i, res;
    int* delay;
    rsted* temp = rstd_mem;
    rsted* resr;
    for(i=0;i<rsc_m;i++){
        if(!rsc_name.compare(book[i]->getsrcname())) break;
    }
    if(i == rsc_m) return -1;
    if(op == 'B'){
        book[i]->borrowresrc(mem_name, mem_type, d);
        return 1;
    }else if(op == 'R'){
        res = book[i]->returnresrc(mem_name, mem_type, d);
        if(res == 2){
            delay = book[i]->getdelay();
            if(temp == NULL){
                resr = new rsted();
                resr->und = new Undergraduate();
                resr->und->setmember(mem_name);
                resr->und->setdelayed(d, delay);
                resr->next = NULL;
                rstd_mem = resr;
            }else{
                while(temp->next != NULL){
                    if(!mem_name.compare(temp->und->getUserName())){
                        temp->und->setdelayed(d, delay);
                        break;
                    }
                    temp = temp->next;
                }
                if(temp->next == NULL && mem_name.compare(temp->und->getUserName())){
                    resr = new rsted();
                    resr->und = new Undergraduate();
                    resr->und->setmember(mem_name);
                    resr->und->setdelayed(d, delay);
                    resr->next = NULL;
                    temp->next = resr;
                }
            }
            delete[] delay;
            return 2;
        }else if(res == 1) return 1;
    }
}