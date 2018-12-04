#include <iostream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    Library* lib;
    lib = new Library(3, 10, 50);
    delete lib;
}