#include <iostream>
#include <string>
#include <fstream>
#include "Library.h"
using namespace std;

int main(int argc, char** argv){
    Library* lib;
    lib = new Library(3, 10, 50);
    delete lib;
}