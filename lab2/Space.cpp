#include <string>
#include "Space.h"
using namespace std;
int diffdate(int d, int e, int t){
    if(e + t >= 24) return 0;
    if(d > e + t) return 0;
    return 1;
}

Study_Room::Study_Room(){
    personnel = 0;
}

string Study_Room::getusrname(){
    return user_name;
}

int Space::validate(int* d, char op){
    int res = diffdate(d[3], date[3], rsv_time);
    swith(op){
        case 'B':
            if(res) return 0;
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
    for(i=0;i<4;i++)
        date[i] = d[i];    
}

Seat::Seat(){
    floor = 0;
}

string Seat::getusrname(){
    return user_name;
}