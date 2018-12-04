#include "Space.h"
using namespace std;

Space::Space(){
    int i;
    state = 'N';
    for(i=0;i<4;i++){
        emptytime[i] = 0;
        returntime[i] = 0;
    }
}

string Space::getusername(){
    return username;
}

char Space::getstate(){
    return state;
}

void Space::setuserborrow(string mem_name, int* nowd, int rsvtime){
    int i;
    username = mem_name;
    state = 'B';
    for(i=0;i<4;i++) returntime[i] = nowd[i];
    returntime[3] += 3;
    if(returntime[3] >= 24){
        returntime[3] -= 24;
        returntime[2]++;
    }
    if(returntime[2] > 30){
        returntime[2] -= 30;
        returntime[1]++;
    }
    if(returntime[1] > 12){
        returntime[1] -= 12;
        returntime[0]++;
    }
}

void Space::setuserreturn(){
    int i;
    for(i=0;i<4;i++)
        returntime[i] = 0;
    state = 'N';
}

void Space::setempty(int* d){
    int i;
    state = 'E';
    for(i=0;i<4;i++) emptytime[i] = d[i];
    emptytime[3] += 1;
    if(emptytime[3] >= 24){
        emptytime[3] -= 24;
        emptytime[2]++;
    }
    if(emptytime[2] > 30){
        emptytime[2] -= 30;
        emptytime[1]++;
    }
    if(emptytime[1] > 12){
        emptytime[1] -= 12;
        emptytime[0]++;
    }
}

void Space::setstate(){
    int i;
    state = 'B';
    for(i=0;i<4;i++) emptytime[i] = 0;
}

int Space::isavailable(int* nowd){
    int i;
    if(state == 'B'){
        for(i=0;i<3;i++){
            if(nowd[i] != returntime[i]){
                state = 'N';
                return 1;
            }
        }
        if(nowd[3] < returntime[3]) return 0;
        state = 'N';
        return 1;
    }else if(state == 'E'){
        for(i=0;i<3;i++){
            if(nowd[i] != emptytime[i]){
                state = 'N';
                return 1;
            }
        }
        if(nowd[3] < emptytime[3]) return 0;
        state = 'N';
        return 1;
    }else
        return 1;
}

int Space::getremaintime(int* d){
    return returntime[3] - d[3];
}

Study_Room::Study_Room():Space(){
}

Seat::Seat():Space(){
}