#include <string>
#include <vector>
#include "Space.h"
#include "Member.h"
#include "Resource.h"
using namespace std;
class Library{
    private:
        int floor_m, room_m, room_status, seat_m;
        int* seat_status;
        Study_Room** str;
        Seat*** set;
        Undergraduate** und;
        Book** book;
    public:
        Library(int fl, int room_n, int seat_n);
        ~Library();
        void exeReserve(int* d, string sp_type, int sp_n, char op, string mem_name, string mem_type, int mem_n, int rsv_time);
        int validID(string sp_type, int sp_n);
        int executable(int* d, int rsv_time, string sp_type, int fl);
        int borrowed(string mem_name, string sp_type, char op, int* d);
        int execmem(string sp_type, int mem_n);
        int exectime(string sp_type, string mem_name, int* d, char op, int rsv_time);
        int fullspace(string sp_type, char op, int sp_n, int* d);
};