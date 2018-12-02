#include <vector>
#include "Space.h"
#include "Member.h"
#include "Resource.h"
using namespace std;

class Library{
    private:
        int floor_m, room_m, room_state, seat_m; //층 수, 방 수, 현재 방 상태, 좌석 수
        int* seat_status;   //좌석 현재 인원
        Study_Room** str;
        Seat*** set;
        vector<Book> book;
        vector<Magazine> mgz;
        vector<E_book> ebook;
        vector<Undergraduate> und;
        vector<Graduate> grd;
        vector<Faculty> fac;
    public:
        Library(int fl, int room_n, int seat_n);
        ~Library();
        void BorrowResource(int opn, int* nowdate, string rsc_type, string rsc_name, string mem_type, string mem_name, char op);
        void BorrowSpace(int opn, int* nowdate, string sp_type, int sp_num, string mem_type, string mem_name, char op, int num_mem, int rsv_time);
};