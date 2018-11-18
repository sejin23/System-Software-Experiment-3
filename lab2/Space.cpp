#include <string>
#include <iostream>
#include "Space.h"
using namespace std;
int diffdate(int* d, int* e, int t, char st){
    int i;
    for(i=0;i<3;i++){
        //cout << d[i] << ": " << e[i] << endl;
        if(d[i] != e[i]) return 0;
    }
    //cout << d[i] << ": " << e[i] << endl;
    if(e[3] + t >= 24) return 0;
    if(st == 'E'){
        if(d[3] > e[3] + 1) return 0;
    }
    if(d[3] > e[3] + t) return 0;
    return 1;
}

Study_Room::Study_Room(){
    personnel = 0;
}

string Study_Room::getusrname(){
    return user_name;
}

int Study_Room::validate(int* d, char op){
    int res = diffdate(d, date, rsv_time, state);
    switch(op){
        case 'B':
            if(!res) return 0;
            break;
        case 'R':
            if(!res) return 0;
            break;
        case 'E':
            if(state == 'E' || !res) return 0;
            break;
        case 'C':
            if(state == 'B' || !res) return 0;
            break;
    }
    return 1;
}

void Study_Room::setResrv(string name, int time, int resv_n, int* d){
    int i;
    personnel = resv_n;
    user_name = name;
    state = 'B';
    rsv_time = time;
    for(i=0;i<4;i++) date[i] = d[i];
}

void Study_Room::setstate(char op){
    state = op;
}

int Study_Room::getrsvtime(){
    return rsv_time;
}

int* Study_Room::getstartdate(){
    return date;
}

Seat::Seat(){
    floor = 0;
}

string Seat::getusrname(){
    return user_name;
}

int Seat::validate(int* d, char op){
    int res = diffdate(d, date, rsv_time, state);
    switch(op){
        case 'B':
            if(!res) return 0;
            break;
        case 'R':
            if(!res) return 0;
            break;
        case 'E':
            if(state == 'E' || !res) return 0;
            break;
        case 'C':
            if(state == 'B' || !res) return 0;
            break;
    }
    return 1;
}

void Seat::borrResrv(string mem_name, int* d, int t, int fl){
    int i;
    floor = fl;
    user_name = mem_name;
    state = 'B';
    rsv_time = t;
    for(i=0;i<4;i++) date[i] = d[i];
}

void Seat::emtResrv(){
    state = 'E';
}

void Seat::cmbResrv(){
    state = 'B';
}

int Seat::getrsvtime(){
    return rsv_time;
}

int* Seat::getstartdate(){
    return date;
}