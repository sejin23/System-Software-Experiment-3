#include <iostream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    Library* lib;
    if(argc == 1) lib = new Library(3, 10, 50, 0);
    else lib = new Library(3, 10, 50, 1);
    delete lib;
}