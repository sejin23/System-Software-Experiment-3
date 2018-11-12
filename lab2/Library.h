#include <string>
#include <vector>
#include "Space.h"
using namespace std;
class Library{
    private:
        int floor_m, room_m, room_status, seat_m;
        int* seat_status;
        Study_Room** str;
        Seat*** set; 
    public:
        Library(int fl, int room_n, int seat_n);
        ~Library();
        int exeReserve(int* d, string sp_type, int sp_n, char op, string mem_type, string mem_name, int mem_n, int rsv_time);
        int validID(string sp_type);
        int executable(int* d, int rsv_time, string sp_type, int fl);
        int borrowed(string mem_name, string sp_type, char op, int sp_n, int* d);
        int execmem(string sp_type, char op, int mem_n);
        int exectime(string mem_name, int* d, char op, int rsv_time);
        int fullspace();
};