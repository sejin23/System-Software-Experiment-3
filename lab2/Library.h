#include <string>
#include <vector>
#include "Space.h"
#include "Resource.h"
using namespace std;
typedef struct _restrict{
    Undergraduate* und;
    struct _restrict* next;
}rsted;
class Library{
    private:
        int floor_m, room_m, room_status, seat_m, rsc_m;
        int* seat_status;
        Study_Room** str;
        Seat*** set;
        rsted* rstd_mem;
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
        int searchRsc(string src_name);
        int execresrc(string mem_name, string mem_type, char op, int* d);
        int isBorrowed(string mem_name, string mem_type, string rsc_type, string rsc_name, char op);
        int* borroweddate(string mem_name, string mem_type, string rsc_name, string rsc_type);
        int isDelayedMem(string mem_name, string mem_type, char op, int* d);
        int* delayeddate(string mem_name, string mem_type);
        int setBorrow(string mem_name, string mem_type, string rsc_name, string rsc_type, char op, int* d);
};